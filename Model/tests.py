import unittest
import unittest.mock
import io
from model import *

class TestNumber(unittest.TestCase):
    def test_number(self):
        scope = Scope()
        num = Number(1)
        self.assertIsInstance(num, Number)
        self.assertIsInstance(num.evaluate(scope), Number)
        self.assertIs(num, num.evaluate(scope))

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
        self.assertIsInstance(scope["b"], UnaryOperation)
        self.assertIsInstance(scope["b"].evaluate(scope), Number)
        Print(scope["b"]).evaluate(scope)
        self.assertEqual(self.mocked_out.getvalue(), "-5\n")
        self.mocked_out = self.patcher.start()
        scope["b"] = UnaryOperation('-', Number(-5))
        Print(scope["b"]).evaluate(scope)
        self.assertEqual(self.mocked_out.getvalue(), "5\n")
        self.mocked_out = self.patcher.start()
        scope["b"] = UnaryOperation('!', Number(5))
        self.assertIsInstance(scope["b"], UnaryOperation)
        self.assertIsInstance(scope["b"].evaluate(scope), Number)
        Print(scope["b"]).evaluate(scope)
        self.assertEqual(self.mocked_out.getvalue(), "0\n")
        self.mocked_out = self.patcher.start()
        scope["b"] = UnaryOperation('!', Number(0))
        Print(scope["b"]).evaluate(scope)   
        self.assertNotEqual(self.mocked_out.getvalue(), "0\n")
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
        self.assertIsInstance(scope["b"], BinaryOperation)
        self.assertIsInstance(scope["b"].evaluate(scope), Number)
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
        self.patcher.stop()
    
    def test_logic(self):
        self.patcher = unittest.mock.patch("sys.stdout", new_callable=io.StringIO)
        self.mocked_out = self.patcher.start()
        scope = Scope()
        a = Number(3)
        b = Number(4)
        scope["b"] = BinaryOperation(a, '==', b)
        Print(scope["b"]).evaluate(scope)
        self.assertEqual(self.mocked_out.getvalue(), "0\n")
        self.mocked_out = self.patcher.start()
        scope["b"] = BinaryOperation(a, '==', a)
        Print(scope["b"]).evaluate(scope)
        assert(self.mocked_out.getvalue() != "0\n")
        self.mocked_out = self.patcher.start()
        
        scope["b"] = BinaryOperation(a, '!=', b)
        Print(scope["b"]).evaluate(scope)
        assert(self.mocked_out.getvalue() != "0\n")
        self.mocked_out = self.patcher.start()
        scope["b"] = BinaryOperation(a, '!=', a)
        Print(scope["b"]).evaluate(scope)
        self.assertEqual(self.mocked_out.getvalue(), "0\n")
        self.mocked_out = self.patcher.start()
        
        scope["b"] = BinaryOperation(a, '<', b)
        Print(scope["b"]).evaluate(scope)
        assert(self.mocked_out.getvalue() != "0\n")
        self.mocked_out = self.patcher.start()
        scope["b"] = BinaryOperation(a, '<', a)
        Print(scope["b"]).evaluate(scope)
        self.assertEqual(self.mocked_out.getvalue(), "0\n")
        self.mocked_out = self.patcher.start()
        scope["b"] = BinaryOperation(b, '<', a)
        Print(scope["b"]).evaluate(scope)
        self.assertEqual(self.mocked_out.getvalue(), "0\n")
        self.mocked_out = self.patcher.start()
        
        scope["b"] = BinaryOperation(a, '>', b)
        Print(scope["b"]).evaluate(scope)
        self.assertEqual(self.mocked_out.getvalue(), "0\n")
        self.mocked_out = self.patcher.start()
        scope["b"] = BinaryOperation(a, '>', a)
        Print(scope["b"]).evaluate(scope)
        self.assertEqual(self.mocked_out.getvalue(), "0\n")
        self.mocked_out = self.patcher.start()
        scope["b"] = BinaryOperation(b, '>', a)
        Print(scope["b"]).evaluate(scope)
        assert(self.mocked_out.getvalue() != "0\n")
        self.mocked_out = self.patcher.start()
        
        scope["b"] = BinaryOperation(a, '<=', b)
        Print(scope["b"]).evaluate(scope)
        assert(self.mocked_out.getvalue() != "0\n")
        self.mocked_out = self.patcher.start()
        scope["b"] = BinaryOperation(a, '<=', a)
        Print(scope["b"]).evaluate(scope)
        assert(self.mocked_out.getvalue() != "0\n")
        self.mocked_out = self.patcher.start()
        scope["b"] = BinaryOperation(b, '<=', a)
        Print(scope["b"]).evaluate(scope)
        self.assertEqual(self.mocked_out.getvalue(), "0\n")
        self.mocked_out = self.patcher.start()
        
        scope["b"] = BinaryOperation(b, '>=', a)
        Print(scope["b"]).evaluate(scope)
        assert(self.mocked_out.getvalue() != "0\n")
        self.mocked_out = self.patcher.start()
        scope["b"] = BinaryOperation(a, '>=', a)
        Print(scope["b"]).evaluate(scope)
        assert(self.mocked_out.getvalue() != "0\n")
        self.mocked_out = self.patcher.start()
        scope["b"] = BinaryOperation(a, '>=', b)
        Print(scope["b"]).evaluate(scope)
        self.assertEqual(self.mocked_out.getvalue(), "0\n")
        self.patcher.stop()
     
     
class TestScope(unittest.TestCase):
    def test_scope_num(self):
        parent = Scope()
        parent["num"] = 5
        self.assertIs(parent["num"], 5)
        scope = Scope(parent)
        self.assertIs(scope["num"], 5)
        parent["num"] = 1
        self.assertIs(scope["num"], 1)
        
    def test_scope_model(self):
        parent = Scope()
        scope = Scope(parent)
        a = Number(2)
        parent["a"] = a
        self.assertIs(scope["a"], a)
        f = Function(None, None)
        parent["f"] = f
        self.assertIs(scope["f"], f)
     
class TestReference(unittest.TestCase):
    def test_reference_number(self):
        parent = Scope()
        scope = Scope(parent)
        a = Number(1)
        b = Number(2)
        c = Number(3)
        parent["f1"] = a
        scope["f1"] = b
        parent["f2"] = c
        self.assertIs(Reference('f1').evaluate(parent), a)
        self.assertIs(Reference('f1').evaluate(scope), b)
        self.assertIs(Reference('f2').evaluate(parent), c)
        self.assertIs(Reference('f2').evaluate(scope), c)

    def test_reference_model(self):
        parent = Scope()
        scope = Scope(parent)
        a = Function([], [])
        parent["f"] = a
        self.assertIsInstance(Reference("f"), Reference)
        self.assertIs(Reference('f').evaluate(parent), a)
        self.assertIs(Reference('f').evaluate(scope), a)

class TestFunction(unittest.TestCase):
    def test_empty(self):
        a = Function((), [])
        self.assertIsInstance(a, Function)
        
    def test_empty_body(self):
        a = Function(('foo', 'bar'), [])
        self.assertIsInstance(a, Function)
    
    def test_function(self):
        self.patcher = unittest.mock.patch("sys.stdout", new_callable=io.StringIO)
        self.mocked_out = self.patcher.start()
        parent = Scope()
        parent["bar"] = Number(10)
        parent["foo"] = Function(('hello', 'world'),
                             [Number(1), Number(3)])
        self.assertIsInstance(parent["foo"], Function)
        self.assertIsInstance(parent["foo"].evaluate(parent), Number)
        Print(parent["foo"]).evaluate(parent)
        self.assertEqual(self.mocked_out.getvalue(), "3\n")
        self.patcher.stop()

class TestFunctionDefinition(unittest.TestCase):
    def test_function_definition(self):
        scope = Scope()
        func1 = Function([], [])
        func2 = Function(None, None)
        func3 = Function(["arg"], [Number(1)])
        def1 = FunctionDefinition('a', func1)
        def2 = FunctionDefinition('b', func2)
        def3 = FunctionDefinition('c', func3) 
        self.assertIsInstance(def1, FunctionDefinition)
        self.assertIsInstance(def2, FunctionDefinition)
        self.assertIsInstance(def3, FunctionDefinition)
        self.assertIsInstance(def1.evaluate(scope), Function)
        self.assertIsInstance(def2.evaluate(scope), Function)
        self.assertIsInstance(def3.evaluate(scope), Function)
        self.assertIs(scope["a"], func1)
        self.assertIs(scope["b"], func2)
        self.assertIs(scope["c"], func3)

class TestFunctionCall(unittest.TestCase):
    def test_empty(self):
        b = FunctionCall(FunctionDefinition(
        'a', Function((), [])), ())
        self.assertIsInstance(b, FunctionCall)
        
    def test_function_call(self):
        self.patcher = unittest.mock.patch("sys.stdout", new_callable=io.StringIO)
        self.mocked_out = self.patcher.start()
        parent = Scope()
        f1 = Function([], [])
        f2 = Function(('hello', 'world'), [Number(1), Reference("world")])
        d1 = FunctionDefinition("b1", f1)
        d2 = FunctionDefinition("b2", f2)
        c1 = FunctionCall(d1, [])
        c2 = FunctionCall(d2, [Number(1), Number(2)])
        self.assertIsInstance(c1, FunctionCall)
        self.assertIsInstance(c2, FunctionCall)
        Print(c2.evaluate(parent)).evaluate(parent)
        self.assertEqual(self.mocked_out.getvalue(), "2\n")
        self.patcher.stop()

class TestConditional(unittest.TestCase):
    def test_true_empty_none(self):
        a = Conditional(Number(1), [])
        b = Conditional(Number(1), None)
        self.assertIsInstance(a, Conditional)
        self.assertIsInstance(b, Conditional)
        
    def test_true_empty_empty(self):
        a = Conditional(Number(1), [], [])
        b = Conditional(Number(1), None, None)
        self.assertIsInstance(a, Conditional)
        self.assertIsInstance(b, Conditional)

    def test_false_empty_none(self):
        a = Conditional(Number(0), [])
        b = Conditional(Number(0), None)
        self.assertIsInstance(a, Conditional)
        self.assertIsInstance(b, Conditional)

    def test_false_empty_empty(self):
        a = Conditional(Number(0), [], [])
        b = Conditional(Number(0), None, None)
        self.assertIsInstance(a, Conditional)
        self.assertIsInstance(b, Conditional)

    def test_conditional(self):
        self.patcher = unittest.mock.patch("sys.stdout", new_callable=io.StringIO)
        self.mocked_out = self.patcher.start()
        parent = Scope()
        parent["bar"] = Number(10)
        parent["foo"] = Conditional(BinaryOperation(parent["bar"], 
                       ">", Number(0)), [Number(0)], [Number(1)])
        self.assertIsInstance(parent["foo"], Conditional)
        Print(parent["foo"]).evaluate(parent)
        self.assertEqual(self.mocked_out.getvalue(), "0\n")
        self.mocked_out = self.patcher.start()
        parent["foo"] = Conditional(BinaryOperation(parent["bar"], 
                       ">", Number(20)), [Number(0)], [Number(1)])
        self.assertIsInstance(parent["foo"], Conditional)
        Print(parent["foo"]).evaluate(parent)
        self.assertEqual(self.mocked_out.getvalue(), "1\n")
        self.patcher.stop()

    def test_conditional_2(self):
        self.patcher = unittest.mock.patch("sys.stdout", new_callable=io.StringIO)
        self.mocked_out = self.patcher.start()
        parent = Scope()
        parent["bar"] = Number(10)
        parent["foo"] = Conditional(BinaryOperation(parent["bar"], 
                       "<", Number(0)), [Number(0)], [Number(1), Number(2)])
        self.assertIsInstance(parent["foo"], Conditional)
        Print(parent["foo"]).evaluate(parent)
        self.assertEqual(self.mocked_out.getvalue(), "2\n")
        self.patcher.stop()

class TestRead(unittest.TestCase):
    def test_read(self):
        self.patcher = unittest.mock.patch("sys.stdout", new_callable=io.StringIO)
        self.mocked_out = self.patcher.start()
        scope = Scope()
        for i in range(100):
            self.patcher2 = unittest.mock.patch("sys.stdin", io.StringIO(str(i)+"\n"))
            self.mocked_in = self.patcher2.start()
            Read("num"+str(i)).evaluate(scope)
            self.assertIsInstance(scope["num"+str(i)], Number)
            Print(scope["num"+str(i)]).evaluate(scope)
            self.assertEqual(self.mocked_out.getvalue(), str(i) + "\n")
            self.mocked_out = self.patcher.start()
        self.patcher.stop()
        self.patcher2.stop()
        
if __name__ == "__main__":
    unittest.main()

