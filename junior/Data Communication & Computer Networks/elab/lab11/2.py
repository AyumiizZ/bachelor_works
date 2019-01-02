import math
AU = 149598000
SIGNALSPEED = 3*10**8
es = float(input("Earth to sun (AU): "))
ps = float(input("Planet to sun (AU): ")) 
fs = int(input("Frame size (bit): "))
sp = int(input("Bandwidth (Mbps): "))
sp *= 10**6
distance = (ps+es)*AU
print("Distance between earth and planet: {} km".format(distance))
p_delay = distance*1000/SIGNALSPEED
round_trip = (2*p_delay+(fs/sp))
print("Round-trip delay: {} sec".format(round_trip))
data = round_trip*sp
frame = math.ceil(data/fs)
print("Data sent before ACK return: {} bit".format(data))
print("Frame sent before ACK return: {} frame".format(frame))
gb = math.ceil(math.log(frame+1,2))
sr = math.ceil(math.log(frame,2))+1
print("Sequence number of Go-Back-N ARQ: {} bit".format(gb))
print("Sequence number of Selective-Repeat ARQ: {} bit".format(sr))