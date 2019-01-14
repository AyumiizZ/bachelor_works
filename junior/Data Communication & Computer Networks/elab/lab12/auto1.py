import pyautogui
import math
import time
ans = []
frame_size = int(input("Frame size (byte): "))
Bandwidth_old = int(input("Bandwidth (Kbps): "))
# frame_size = 180
# Bandwidth_old = 78
frame_size *= 8
Bandwidth_old *= 10**3
frame_time = (frame_size/Bandwidth_old) * 1000
ans.append(frame_time)
frame_per_sec_old = 10**3/frame_time
ans.append(frame_per_sec_old)

frame_per_sec = 100
Bandwidth = frame_per_sec*frame_size /(10**3)
frame_per_one_frame = frame_per_sec/frame_per_sec_old
G = frame_per_one_frame
S_pure = G * (math.e**(-2*G))
S_slot = G * (math.e**(-1*G))
t_pure = S_pure * Bandwidth_old / (10**3)
t_slot = S_slot * Bandwidth_old / (10**3)
ans.append(Bandwidth)
ans.append(frame_per_one_frame)
ans.append(S_pure)
ans.append(S_slot)
ans.append(t_pure)
ans.append(t_slot)


frame_per_sec = 50
Bandwidth = frame_per_sec*frame_size /(10**3)
frame_per_one_frame = frame_per_sec/frame_per_sec_old
G = frame_per_one_frame
S_pure = G * (math.e**(-2*G))
S_slot = G * (math.e**(-1*G))
t_pure = S_pure * Bandwidth_old / (10**3)
t_slot = S_slot * Bandwidth_old / (10**3)
ans.append(Bandwidth)
ans.append(frame_per_one_frame)
ans.append(S_pure)
ans.append(S_slot)
ans.append(t_pure)
ans.append(t_slot)


G = 0.5
S_pure = G * (math.e**(-2*G))
a1 = 0.5
a2 = frame_per_sec_old*a1
a3 = S_pure
a4 = a3*frame_per_sec_old
a5 = a4/a2*100
a6 = a3*100
ans.append(a1)
ans.append(a2)
ans.append(a3)
ans.append(a4)
ans.append(a5)
ans.append(a6)


G = 1
S_slot = G * (math.e**(-1*G))
a1 = 1
a2 = frame_per_sec_old*a1
a3 = S_slot
a4 = a3*frame_per_sec_old
a5 = a4/a2*100
a6 = a3*100
ans.append(a1)
ans.append(a2)
ans.append(a3)
ans.append(a4)
ans.append(a5)
ans.append(a6)

# print(ans)
time.sleep(3)
for i in ans:
    print(i)
    pyautogui.typewrite(str(i))
    pyautogui.press('tab')
# pyautogui.press('enter')