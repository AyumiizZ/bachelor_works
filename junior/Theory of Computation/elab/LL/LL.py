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
        # self.literal = '+-*/()'
        self.literal = '+-*/();=?$'
        self.output = []

    def one_move(self, state, char):
        if(state is None):
            return self.init_state(char)
        elif(state is 'CONST'):
            if(char in self.D + self.dot):
                self.sliced += char
                return 'CONST'
            elif(self.sliced[-1] is self.dot):
                self.output.append(('ERROR', self.sliced))
                return self.init_state(char)
            else:
                self.output.append(('CONST', self.sliced))
                return self.init_state(char)
        elif(state is 'IDEN'):
            if(char in self.D + self.L):
                self.sliced += char
                return 'IDEN'
            else:
                self.output.append(('IDEN', self.sliced))
                return self.init_state(char)

    def move(self):
        for i in self.data:
            self.state = self.one_move(self.state, i)
            if(self.state in ['ERROR', 'LITERAL']):
                self.output.append((self.state, self.sliced))
                self.state = None
        if(self.state is not None):
            if(self.state is 'CONST' and self.sliced[-1] is self.dot):
                self.output.append(('ERROR', self.sliced))
            else:
                self.output.append((self.state, self.sliced))
        return self.output

    def init_state(self, char):
        self.sliced = str(char)
        if(char in self.D):
            return 'CONST'
        if(char in self.L):
            return 'IDEN'
        if(char in self.literal):
            return 'LITERAL'
        return 'ERROR'


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


class LL:
    def __init__(self):
        self.lexer = Lexer()
        self.lexer.move()
        self.input = self.lexer.output[::-1]
        # print(self.lexer.output)
        self.stack = Stack()
        self.output = []
        self.temp = ''

    def move(self):
        # while len(self.input) != 0:
        #     top = self.input.pop()
        for state, data in self.lexer.output:
            # print(state,data,self.stack.stack[::-1],self.output)
            if(state is 'IDEN'):
                self.id_state()
            elif(state is 'CONST'):
                self.con_state()
            elif(state is 'LITERAL'):
                if(data in ['+', '-']):
                    self.plus_minus_state(data)
                elif(data in ['*', '/']):
                    self.mul_div_state(data)
                elif(data is '('):
                    self.open_state()
                elif(data in [')', ';', '=']):
                    self.other_state(data)
                elif(data is '?'):
                    self.ques_state()
                else:
                    self.end_state()
            else:
                self.output = ['parse errorsss']
                break

    def id_state(self):  # id
        top = ''
        while top != 'id':
            self.print_output()
            top = self.stack.pop()
            if(top is 'S'):
                self.stack.append(['id', '=', 'E', ';', 'S'])
            elif(top is 'E'):
                self.stack.append(['T', 'Ep'])
            elif(top is 'T'):
                self.stack.append(['F', 'Tp'])
            elif(top is 'F'):
                self.stack.append(['id', 'A'])
            elif(top in ['A', 'Ep', 'Tp']):
                continue
            elif(top != 'id'):
                print('parse error')
                exit(0)
        self.output.append(top)

    def con_state(self):  # con
        top = ''
        while top != 'con':
            self.print_output()
            top = self.stack.pop()
            if(top is 'E'):
                self.stack.append(['T', 'Ep'])
            elif(top is 'T'):
                self.stack.append(['F', 'Tp'])
            elif(top is 'F'):
                self.stack.append(['con'])
            elif(top in ['S', 'Ep', 'Tp', 'A']):
                continue
            elif(top != 'con'):
                print('parse error')
                exit(0)
        self.output.append(top)

    def plus_minus_state(self, data):  # + -
        top = ''
        while top not in ['+', '-']:
            self.print_output()
            top = self.stack.pop()
            if(top is 'E'):
                self.stack.append(['T', 'Ep'])
            elif(top is 'Ep'):
                self.stack.append([data, 'T', 'Ep'])
            elif(top is 'T'):
                self.stack.append(['F', 'Tp'])
            elif(top in ['S', 'Tp', 'A']):
                continue
            elif(top not in ['+', '-']):
                print('parse error')
                exit(0)
        self.output.append(top)

    def mul_div_state(self, data):  # * /
        top = ''
        while top not in ['*', '/']:
            self.print_output()
            top = self.stack.pop()
            if(top is 'E'):
                self.stack.append(['T', 'Ep'])
            elif(top is 'T'):
                self.stack.append(['F', 'Tp'])
            elif(top is 'Tp'):
                self.stack.append([data, 'F', 'Tp'])
            elif(top in ['S', 'Ep', 'A']):
                continue
            elif(top not in ['*', '/']):
                print('parse error')
                exit(0)
        self.output.append(top)

    def open_state(self):  # (
        top = ''
        while top != '(':
            # print('(' ,self.stack.stack[::-1],self.output)
            self.print_output()
            top = self.stack.pop()
            # print('top = ',top)
            if(top is 'E'):
                self.stack.append(['T', 'Ep'])
            elif(top is 'T'):
                self.stack.append(['F', 'Tp'])
            elif(top in ['F', 'A']):
                self.stack.append(['(', 'E', ')'])
            elif(top in ['S', 'Ep', 'Tp']):
                continue
            elif(top != '('):
                print('parse error')
                exit(0)
        self.output.append(top)

    def other_state(self, data):  # ) ; =
        top = ''
        while top != data:
            # print(data ,self.stack.stack[::-1],self.output)
            self.print_output()
            top = self.stack.pop()
            if(top is 'E'):
                self.stack.append(['T', 'Ep'])
            elif(top is 'T'):
                self.stack.append(['F', 'Tp'])
            elif(top in ['S', 'Ep', 'Tp', 'A']):
                continue
            elif(top != data):
                print('parse error')
                exit(0)
        self.output.append(top)

    def ques_state(self):  # ?
        top = ''
        while top != '?':
            self.print_output()
            top = self.stack.pop()
            if(top is 'S'):
                self.stack.append(['?', 'S'])
            elif(top is 'E'):
                self.stack.append(['T', 'Ep'])
            elif(top is 'T'):
                self.stack.append(['F', 'Tp'])
            elif(top in ['Ep', 'Tp', 'A']):
                continue
            elif(top != '?'):
                print('parse error')
                exit(0)
        self.output.append(top)

    def end_state(self):  # $
        top = ''
        while not self.stack.empty():
            self.print_output()
            top = self.stack.pop()
            if(top is 'E'):
                self.stack.append(['T', 'Ep'])
            elif(top is 'T'):
                self.stack.append(['F', 'Tp'])
            # elif(top in ['F']):
            #     print('parse error')
            #     exit(0)
            elif(top in ['S', 'A', 'Tp', 'Ep']):
                continue
            else:
                print('parse error')
                exit(0)
                # self.output.append(top)

    def print_output(self):
        self.curr = ('L=> ' + (' '.join(self.output).strip() +
                               ' ' if self.output != [] else '') + self.stack.data().strip()).strip()
        if(self.curr != self.temp):
            self.temp = self.curr
            print(self.curr)


if __name__ == '__main__':
    ll = LL()
    ll.move()
    ll.print_output()
