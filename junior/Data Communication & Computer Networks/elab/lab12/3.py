import math
B = int(input('Bandwidth (Mpbs): ')) * (10**6)
L = int(input('Length (m): '))
equ = "(2*B*L)/(2.4*10**8)"
print("Equation is {}".format(equ))
print("Frame size >= {} bytes".format(math.ceil(eval(equ)/8)))