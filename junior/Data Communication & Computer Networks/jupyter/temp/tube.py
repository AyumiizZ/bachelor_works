LIGHT_SPEED = 3e8
DOG_SPEED = 4*1000/3600

def method1_time(size):
    wireless_time = (154*8)/86
    fiber_time = 103/LIGHT_SPEED
    sum_time = wireless_time + fiber_time
    return sum_time

def method2_time(size):
    write_time = size/190
    distance_time = 103/DOG_SPEED
    read_time = size/245
    sum_time = write_time + distance_time + read_time
    return(sum_time)

print(method1_time(154))
print(method2_time(154))
