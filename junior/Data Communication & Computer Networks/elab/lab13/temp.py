code = [int(i) for i in input().split(',')]
data = [int(i) for i in input().split(',')]
print('1')
for i in range(int(len(data)/len(code))):
    temp2 = [int(code[j])*int(data[i*len(code) + j]) for j in range(len(code))]
    print('temp2',temp2)
    print(sum(temp2))
    temp = [sum(temp2)/len(code)]
    print('temp',temp)
    print(''.join(['-' if i == 0 else '1' if i == 1 else '0' for i in temp]))
