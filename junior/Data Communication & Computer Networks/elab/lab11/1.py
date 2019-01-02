m = int(input("How many bit?: "))
print("Go-Back-N ARQ: {} frame".format(2**m-1))
print("Selective-Repeat ARQ: {} frame".format(2**(m-1)))