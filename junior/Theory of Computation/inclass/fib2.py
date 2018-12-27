known = {0:0,1:1}

def f(n):
    if n in known:
        return known[n]
    res = f(n-1)+f(n-2)
    known[n] = res
    return res

for i in range(1000):
    f(10*i)

print (f(999))