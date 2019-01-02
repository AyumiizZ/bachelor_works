code = [int(i) for i in input().split(',')]
data = [int(i) for i in input().split(',')]
print(''.join(['-' if i == 0 else '1' if i == 1 else '0' for i in [sum([int(code[j])*int(data[i*len(code) + j])
                                                                        for j in range(len(code))])/len(code) for i in range(int(len(data)/len(code)))]]))
