#!/usr/bin/env python3


class Scope:
    def __init__(self, parent=None):
        self.parent = parent
        self.store = {}

    def __getitem__(self, key):
        if key in self.store:
            return self.store[key]
        else:
            return self.parent[key]

    def __setitem__(self, key, value):
        self.store[key] = value


class Number:
    def __init__(self, value):
        self.value = value

    def evaluate(self, scope):
        return self


class Function:
    def __init__(self, args, body):
        self.args = args
        self.body = body

    def evaluate(self, scope):
        last = None
        for i in self.body:
            last = i.evaluate(scope)
        return last


class FunctionDefinition:
    def __init__(self, name, function):
        self.name = name
        self.function = function

    def evaluate(self, scope):
        scope[self.name] = self.function
        return self.function


class Conditional:
    def __init__(self, condition, if_true, if_false=None):
        self.condition = condition
        self.if_true = if_true
        self.if_false = if_false

    def evaluate(self, scope):
        last = None
        if self.condition.evaluate(scope).value == 0:
            a = self.if_false
        else:
            a = self.if_true
        if a:
            for i in a:
                last = i.evaluate(scope)
        return last


class Print:
    def __init__(self, expr):
        self.expr = expr

    def evaluate(self, scope):
        a = self.expr.evaluate(scope)
        print(a.value)
        return a


class Read:
    def __init__(self, name):
        self.name = name

    def evaluate(self, scope):
        a = Number(int(input()))
        scope[self.name] = a
        return a


class FunctionCall:
    def __init__(self, fun_expr, args):
        self.args = args
        self.fun_expr = fun_expr

    def evaluate(self, scope):
        function = self.fun_expr.evaluate(scope)
        scope2 = Scope(scope)
        for i, a in zip(self.args, function.args):
            scope2[a] = i.evaluate(scope)
        return function.evaluate(scope2)


class Reference:
    def __init__(self, name):
        self.name = name

    def evaluate(self, scope):
        return scope[self.name]


class BinaryOperation:
    def __init__(self, lhs, op, rhs):
        self.lhs = lhs
        self.op = op
        self.rhs = rhs
 
    d = {
        '+' : lambda lhs, rhs: lhs.value + rhs.value,
        '-' : lambda lhs, rhs: lhs.value - rhs.value,
        '*' : lambda lhs, rhs: lhs.value * rhs.value,
        '/' : lambda lhs, rhs: lhs.value // rhs.value,
        '%' : lambda lhs, rhs: lhs.value % rhs.value,
        '==' : lambda lhs, rhs: 1 if (lhs.value == rhs.value) else 0,
        '!=' : lambda lhs, rhs: 1 if (lhs.value != rhs.value) else 0,
        '>' : lambda lhs, rhs: 1 if (lhs.value > rhs.value) else 0,
        '<' : lambda lhs, rhs: 1 if (lhs.value < rhs.value) else 0,
        '>=' : lambda lhs, rhs: 1 if (lhs.value >= rhs.value) else 0,
        '<=' : lambda lhs, rhs: 1 if (lhs.value <= rhs.value) else 0,
        '&&' : lambda lhs, rhs: lhs.value and rhs.value,
        '||' : lambda lhs, rhs: lhs.value or rhs.value

    }
       
    def evaluate(self, scope):
        l = self.lhs.evaluate(scope)
        r = self.rhs.evaluate(scope)
        return Number(self.d[self.op](l,r))

class UnaryOperation:
    def __init__(self, op, expr):
        self.op = op
        self.expr = expr

    def evaluate(self, scope):
        e = self.expr.evaluate(scope).value
        if(self.op == '-'):
            return Number(-e)
        if(self.op == '!'):
            return Number(e == 0)


def example():
    parent = Scope()
    parent["foo"] = Function(('hello', 'world'),
                             [Print(BinaryOperation(Reference('hello'),
                                                    '+',
                                                    Reference('world')))])
    parent["bar"] = Number(10)
    scope = Scope(parent)
    assert 10 == scope["bar"].value
    scope["bar"] = Number(20)
    assert scope["bar"].value == 20
    print('It should print 2: ', end=' ')
    FunctionCall(FunctionDefinition('foo', parent['foo']),
                 [Number(5), UnaryOperation('-', Number(3))]).evaluate(scope)


def my_tests():
    parent = Scope()
    parent["bar"] = Number(10)
    cond = Conditional(BinaryOperation(parent["bar"], 
                       ">", Number(0)), None, [Print(Number(1))])
    cond.evaluate(parent)
    r = Read(parent["bar"])
    a = r.evaluate(parent).value
    print(a)

if __name__ == '__main__':
    example()
<<<<<<< HEAD
    my_tests()
=======
>>>>>>> 79ddeec28283f461228f7fce120b406f85c47638
