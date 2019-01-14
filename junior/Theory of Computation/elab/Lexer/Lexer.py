#!/usr/bin/python3.6
import string

class Lexer:
    def __init__(self):
        self.get_input()

    def get_input(self):
        self.data = []
        while True:
            try:
                temp = input().split()
                for i in temp:
                    self.data.append(i.strip())
            except EOFError:
                break

    def move(self):
        for sliced in self.data:
            fa = automata(sliced)
            fa.move()


class automata:
    def __init__(self, data):
        self.data = data
        self.state = None
        self.sliced = ""
        self.L = string.ascii_lowercase
        self.D = string.digits
        self.dot = '.'
        self.literal = '+-*/()'

    def one_move(self, state, char):
        if(state is None):
            return self.init_state(char)
        elif(state is "CONST"):
            if(char in self.D + self.dot):
                self.sliced += char
                return "CONST"
            elif(self.sliced[-1] is self.dot):
                print("ERROR\t"+self.sliced)
                return self.init_state(char)
            else:
                print("CONST\t"+self.sliced)
                return self.init_state(char)
        elif(state is "IDEN"):
            if(char in self.D + self.L):
                self.sliced += char
                return "IDEN"
            else:
                print("IDEN\t"+self.sliced)
                return self.init_state(char)

    def move(self):
        for i in self.data:
            self.state = self.one_move(self.state,i)
            if(self.state in ["ERROR", "LITERAL"]):
                print(self.state+"\t"+self.sliced)
                self.state = None
        if(self.state is not None):
            if(self.state is "CONST" and self.sliced[-1] is self.dot):
                print("ERROR\t"+self.sliced)
            else:
                print(self.state+"\t"+self.sliced)

    def init_state(self, char):
        self.sliced = str(char)
        if(char in self.D):
            return "CONST"
        if(char in self.L):
            return "IDEN"
        if(char in self.literal):
            return "LITERAL"
        return "ERROR"

if __name__ == "__main__":
    l = Lexer()
    l.move()