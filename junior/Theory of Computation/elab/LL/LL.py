#!/usr/bin/python3.6
import string


class Lexer:
    def __init__(self):
        self.data = []
        self.get_input()
        self.output = []

    def get_input(self):
        while True:
            try:
                temp = input().split()
                for i in temp:
                    self.data.append(i.strip())
            except EOFError:
                break
        self.data.append('$')

    def move(self):
        for sliced in self.data:
            fa = automata(sliced)
            self.output += fa.move()


class automata:
    def __init__(self, data):
        self.data = data
        self.state = None
        self.sliced = ''
        self.L = string.ascii_lowercase
        self.D = string.digits
        self.dot = '.'
        self.literal = '+-*/();=?$'
        self.output = []

    def one_move(self, state, char):
        if(state is None):
            return self.init_state(char)
        elif(state is 'con'):
            if(char in self.D + self.dot):
                self.sliced += char
                return 'con'
            else:
                self.output.append('con')
                return self.init_state(char)
        elif(state is 'id'):
            if(char in self.D + self.L):
                self.sliced += char
                return 'id'
            else:
                self.output.append('id')
                return self.init_state(char)

    def move(self):
        for i in self.data:
            self.state = self.one_move(self.state, i)
            if(self.state is 'LITERAL'):
                self.output.append(self.sliced)
                self.state = None
        if(self.state is not None):
            self.output.append(self.state)
        return self.output

    def init_state(self, char):
        self.sliced = str(char)
        if(char in self.D):
            return 'con'
        if(char in self.L):
            return 'id'
        if(char in self.literal):
            return 'LITERAL'


class Stack:
    def __init__(self):
        self.stack = ['S']

    def pop(self):
        if(self.empty()):
            print('parse error')
            exit(0)
        else:
            return self.stack.pop()

    def append(self, data):
        data = data[::-1]
        for i in data:
            self.stack.append(i)

    def empty(self):
        return len(self.stack) == 0

    def data(self):
        return (' '.join(self.stack[::-1]) if self.stack != [] else '')


class table:
    def __init__(self):
        self.gen_table()

    def gen_table(self):
        self.parse_input = ['id', 'con', '+', '-',
                            '*', '/', '(', ')', ';', '=', '?', '$']
        self.parse_stack = ['S', 'E', 'Ep', 'T', 'Tp', 'F', 'A']
        self.parser_table = {
            'S': {
                'id': ['id', '=', 'E', ';', 'S'],
                '?': ['?', 'S']
            },
            'Ep': {
                '+': ['+', 'T', 'Ep'],
                '-': ['-', 'T', 'Ep']
            },
            'Tp': {
                '*': ['*', 'F', 'Tp'],
                '/': ['/', 'F', 'Tp']
            },
            'F': {
                'id': ['id', 'A'],
                'con': ['con'],
                '(': ['(', 'E', ')']
            },
            'A': {
                '(': ['(', 'E', ')']
            }
        }

    def get_parse(self, inp, stack):
        try:
            return self.parser_table[stack][inp]
        except:
            if((stack is 'F') or (stack in self.parse_input and stack != inp)):
                print('parse error')
                exit(0)
            elif(stack is 'E'):
                return ['T', 'Ep']
            elif(stack is 'T'):
                return ['F', 'Tp']
            else:
                return ""


class LL:
    def __init__(self):
        self.lexer = Lexer()
        self.lexer.move()
        self.stack = Stack()
        self.output = []
        self.last_result = ''
        self.parser_table = table()

    def move(self):
        for state in self.lexer.output:
            topstack = ''
            while (not self.stack.empty() if state is '$' else topstack != state):
                self.print_output()
                topstack = self.stack.pop()
                res = self.parser_table.get_parse(state, topstack)
                if(res != ""):
                    self.stack.append(res)
            if(state != '$'):
                self.output.append(topstack)
        self.print_output()

    def print_output(self):
        current_result = ('L=> ' + (' '.join(self.output).strip() +
                                    ' ' if self.output != [] else '') + self.stack.data().strip()).strip()
        if(current_result != self.last_result):
            self.last_result = current_result
            print(current_result)


if __name__ == '__main__':
    ll = LL()
    ll.move()