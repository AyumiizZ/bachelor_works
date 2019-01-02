import math
ans = []
frame_size = int(input("Frame size (byte): "))
Bandwidth_old = int(input("Bandwidth (Kbps): "))
frame_size *= 8
Bandwidth_old *= 10**3
frame_time = (frame_size/Bandwidth_old) * 1000
print("Frame time is {} millisecond".format(frame_time))
ans.append(frame_time)
frame_per_sec_old = 10**3/frame_time
print("Ideal can sent {} frame per second".format(frame_per_sec_old))
ans.append(frame_per_sec_old)

frame_per_sec = 100
Bandwidth = frame_per_sec*frame_size /(10**3)
frame_per_one_frame = frame_per_sec/frame_per_sec_old
G = frame_per_one_frame
S_pure = G * (math.e**(-2*G))
S_slot = G * (math.e**(-1*G))
t_pure = S_pure * Bandwidth_old / (10**3)
t_slot = S_slot * Bandwidth_old / (10**3)
print("100 fps | {} | {} | {} | {} | {} | {}".format(Bandwidth,frame_per_one_frame,S_pure,S_slot,t_pure,t_slot))
# ans.append(Bandwidth,frame_per_one_frame,S_pure,S_slot,t_pure,t_slot)

frame_per_sec = 50
Bandwidth = frame_per_sec*frame_size /(10**3)
frame_per_one_frame = frame_per_sec/frame_per_sec_old
G = frame_per_one_frame
S_pure = G * (math.e**(-2*G))
S_slot = G * (math.e**(-1*G))
t_pure = S_pure * Bandwidth_old / (10**3)
t_slot = S_slot * Bandwidth_old / (10**3)
print("50 fps | {} | {} | {} | {} | {} | {}".format(Bandwidth,frame_per_one_frame,S_pure,S_slot,t_pure,t_slot))
# ans.append(Bandwidth,frame_per_one_frame,S_pure,S_slot,t_pure,t_slot)

print("==PURE==")
frame_per_sec = frame_per_sec_old/2
print("{} {}".format(0.5,frame_per_sec))
Bandwidth = frame_per_sec*frame_size /(10**3)
frame_per_one_frame = frame_per_sec/frame_per_sec_old
G = frame_per_one_frame
S_pure = G * (math.e**(-2*G))
t_pure = S_pure * Bandwidth_old / (10**3)
print("spure")
print(G)
print(S_pure)
print("100 fps | {} | {} | {} | {}".format(S_pure,S_pure*frame_per_sec_old,S_pure*frame_per_sec_old/frame_per_sec*100,S_pure*100))


print("==slotted==")
frame_per_sec = frame_per_sec_old
print("{} {}".format(0.5,frame_per_sec))
Bandwidth = frame_per_sec*frame_size /(10**3)
frame_per_one_frame = frame_per_sec/frame_per_sec_old
G = frame_per_one_frame
S_slot = G * (math.e**(-1*G))
t_slot = S_slot * Bandwidth_old / (10**3)
print("100 fps | {} | {} | {} | {}".format(S_slot,S_slot*frame_per_sec_old,S_slot*frame_per_sec_old/frame_per_sec*100,S_slot*100))