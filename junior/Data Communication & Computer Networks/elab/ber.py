# def f(p,k):
#     return ((1-p)**(k-1))*p

# frame_size = 2032
# bit_error_rate = 5*(10**-6)
# p_correct = (1 - bit_error_rate)**frame_size
# p_wrong = 1 - p_correct
# # p_wrong_given_1_digit = 1
# # p_wrong_1_digit = (frame_size*bit_error_rate)*((1-bit_error_rate)**(frame_size - 1))
# # p_wrong_1_digit_given_wrong = p_wrong_given_1_digit * p_wrong_1_digit / p_wrong
# # p_wrong_new = (1-p_wrong_1_digit_given_wrong)*p_wrong
# # print(p_wrong_new*100,p_wrong*100)
# # p_wrong = (1 - ((1 - bit_error_rate)**frame_size))*100
# # print(p_wrong*100)
# # a = []
# # l = 4
# # for i in range(l):
# #     a.append(f(p_correct,i+1))
# # print(a)
# # # print(sum(a))
# # b = []
# # s = 0
# # for i in range(l):
# #     b.append((i+1)*a[i])
# #     s+=(i+1)
# # print(b)
# # print(sum(b))
# E = bit_error_rate
# L = 6032
# B = 2*10**6
# D = 30*10**-3
# p_correct = (1-E)**L
# p_wrong = 1 - p_correct
# print(p_wrong*100)
# A4 = (1+2*p_wrong+3*p_wrong**2+4*p_wrong**3)*p_correct
# print(A4)
# A5 = (L/B+2*D)*1000*A4
# print(A5)
# A6 = L/(A5)*1000
# print(A6)
# A7 = A6/B*100
# print(A7)
# # +(3*((1-E)**L)**2)+(4*((1-E)**L)**3)

# # Ans = (L/(((L/B+2*D))*((1+2*(1-(1-E)**L)+3*(1-(1-E)**L)**2+4*(1-(1-E)**L)**3)*(1-E)**L))*100)/B
# Ans = (L+32)/((2*D+(L/B))*1/(1-E/100)**L)/B*100
# print(Ans)
# print ((1-E/100)**L)


def process(L,E,B,D):
    E*=0.01
    B*=10**6
    D*=10**-3
    print("1: {}".format(2*D*10**3))
    A2 = (L+32)/B*1000
    print("2: {:.6f}".format(A2))
    p_correct = (1-E)**(L+32)
    A3 = 1-p_correct
    print("3: {:.6f}".format(A3*100))
    A4 = (1+2*A3+3*A3**2+4*A3**3)*p_correct
    print("4: {:.6f}".format(A4))
    A5 = (L/B+2*D)*1000*A4
    print("5: {:.6f}".format(A5))
    A6 = (L+32)/A5*1000
    print("6: {:.6f}".format(A6))
    A7 = A6/B*100
    print("7: {:.6f}".format(A7))
    A8 = "(L+32)/((2*D+((L+32)/B))*1/(1-E/100)**(L+32))/B*100"
    print("8: {}".format(A8))

L = 2000
E = 5*10**-4
B = 2
D = 20
process(L,E,B,D)

