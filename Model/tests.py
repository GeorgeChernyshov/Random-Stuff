import unittest
import unittest.mock
import io
from model import *

class TestPrint(unittest.TestCase):
    def test_print(self):
        self.patcher = unittest.mock.patch("sys.stdout", new_callable=io.StringIO)
        self.mocked_out = self.patcher.start()
        scope = Scope()
        for i in range(-1000, 1000):
            scope["a"] = Number(i)
            Print(scope["a"]).evaluate(scope)
            self.assertEqual(self.mocked_out.getvalue(), str(i) + "\n")
            self.mocked_out = self.patcher.start()
        self.patcher.stop()
        
class TestUnary(unittest.TestCase):
    def test_unary(self):
        self.patcher = unittest.mock.patch("sys.stdout", new_callable=io.StringIO)
        self.mocked_out = self.patcher.start()
        scope = Scope()
        scope["b"] = UnaryOperation('-', Number(5))
        Print(scope["b"]).evaluate(scope)
        self.assertEqual(self.mocked_out.getvalue(), "-5\n")
        self.mocked_out = self.patcher.start()
        scope["b"] = UnaryOperation('!', Number(5))
        Print(scope["b"]).evaluate(scope)
        self.assertEqual(self.mocked_out.getvalue(), "0\n")
        self.patcher.stop()
     
     
class TestBinary(unittest.TestCase):
    def test_binary(self):
        self.patcher = unittest.mock.patch("sys.stdout", new_callable=io.StringIO)
        self.mocked_out = self.patcher.start()
        scope = Scope()
        a = Number(9)
        b = Number(4)
        scope["b"] = BinaryOperation(a, '+', b)
        Print(scope["b"]).evaluate(scope)
        self.assertEqual(self.mocked_out.getvalue(), "13\n")
        self.mocked_out = self.patcher.start()
        scope["b"] = BinaryOperation(a, '-', b)
        Print(scope["b"]).evaluate(scope)
        self.assertEqual(self.mocked_out.getvalue(), "5\n")
        self.mocked_out = self.patcher.start()
        scope["b"] = BinaryOperation(a, '*', b)
        Print(scope["b"]).evaluate(scope)
        self.assertEqual(self.mocked_out.getvalue(), "36\n")
        self.mocked_out = self.patcher.start()
        scope["b"] = BinaryOperation(a, '/', b)
        Print(scope["b"]).evaluate(scope)
        self.assertEqual(self.mocked_out.getvalue(), "2\n")
        self.mocked_out = self.patcher.start()
        scope["b"] = BinaryOperation(a, '%', b)
        Print(scope["b"]).evaluate(scope)
        self.assertEqual(self.mocked_out.getvalue(), "1\n")
        self.mocked_out = self.patcher.start()
        scope["b"] = BinaryOperation(a, '==', b)
        Print(scope["b"]).evaluate(scope)
        self.assertEqual(self.mocked_out.getvalue(), "0\n")
        self.mocked_out = self.patcher.start()
        scope["b"] = BinaryOperation(a, '!=', b)
        Print(scope["b"]).evaluate(scope)
        assert(self.mocked_out.getvalue() != "0\n")
        self.mocked_out = self.patcher.start()
        scope["b"] = BinaryOperation(a, '<', b)
        Print(scope["b"]).evaluate(scope)
        self.assertEqual(self.mocked_out.getvalue(), "0\n")
        self.mocked_out = self.patcher.start()
        scope["b"] = BinaryOperation(a, '>', b)
        Print(scope["b"]).evaluate(scope)
        assert(self.mocked_out.getvalue() != "0\n")
        self.mocked_out = self.patcher.start()
        scope["b"] = BinaryOperation(a, '<=', b)
        Print(scope["b"]).evaluate(scope)
        self.assertEqual(self.mocked_out.getvalue(), "0\n")
        self.mocked_out = self.patcher.start()
        scope["b"] = BinaryOperation(a, '>=', b)
        Print(scope["b"]).evaluate(scope)
        assert(self.mocked_out.getvalue() != "0\n")
        self.mocked_out = self.patcher.start()
        self.patcher.stop()
     
     
class TestScope(unittest.TestCase):
    def test_scope(self):
        parent = Scope()
        parent["num"] = 5
        self.assertEqual(parent["num"], 5)
        scope = Scope(parent)
        self.assertEqual(scope["num"], 5)
        parent["num"] = 1
        self.assertEqual(scope["num"], 1)
     
     
class TestReference(unittest.TestCase):
    def test_reference(self):
        parent = Scope()
        a = Number(1)
        parent["a"] = a
        self.assertEqual(Reference('a').evaluate(parent), a)

class TestFunction(unittest.TestCase):
    def test_function(self):
        self.patcher = unittest.mock.patch("sys.stdout", new_callable=io.StringIO)
        self.mocked_out = self.patcher.start()
        parent = Scope()
        parent["bar"] = Number(10)
        parent["foo"] = Function(('hello', 'world'),
                             [Number(3)])
        Print(parent["foo"]).evaluate(parent)
        self.assertEqual(self.mocked_out.getvalue(), "3\n")
        self.patcher.stop()

class TestFunctionDefinition(unittest.TestCase):
    def test_function_definition(self):
        scope = Scope()
        func = Function([], ())
        FunctionDefinition('a', func).evaluate(scope)
        self.assertEqual(scope['a'], func)

class TestFunctionCall(unittest.TestCase):
    def test_function_call(self):
        self.patcher = unittest.mock.patch("sys.stdout", new_callable=io.StringIO)
        self.mocked_out = self.patcher.start()
        parent = Scope()
        parent["bar"] = Number(10)
        parent["foo"] = Function(('hello', 'world'),
                             [Print(BinaryOperation(Reference('hello'),
                                                    '+',
                                                    Reference('world')))])
        FunctionCall(FunctionDefinition('foo', parent['foo']),
                 [Number(5), Number(3)]).evaluate(parent)
        self.assertEqual(self.mocked_out.getvalue(), "8\n")
        self.patcher.stop()

class TestConditional(unittest.TestCase):
    def test_conditional(self):
        self.patcher = unittest.mock.patch("sys.stdout", new_callable=io.StringIO)
        self.mocked_out = self.patcher.start()
        parent = Scope()
        parent["bar"] = Number(10)
        parent["foo"] = Conditional(BinaryOperation(parent["bar"], 
                       ">", Number(0)), [Number(0)], [Number(1)])
        Print(parent["foo"]).evaluate(parent)
        self.assertEqual(self.mocked_out.getvalue(), "0\n")
        self.mocked_out = self.patcher.start()
        parent["foo"] = Conditional(BinaryOperation(parent["bar"], 
                       ">", Number(20)), [Number(0)], [Number(1)])
        Print(parent["foo"]).evaluate(parent)
        self.assertEqual(self.mocked_out.getvalue(), "1\n")
        self.patcher.stop()


if __name__ == "__main__":
    unittest.main()

