from struct import Struct
import time
import struct
obj = struct.pack("=LLLLLLLLLLLLLLLLLLLLLLLLL", 1,2,3,4,5,6,   1,2,3,4,5,6,7,8,9,0, 1,2,3,4,5,6,7,876,9)
obj1 = struct.pack("=LLLLLLLLLLLLLLLLLLLLLLLLL", 1,2,3,4,5,6,   1,2,3,4,5,6,7,8,9,0, 1,2,3,4,5,6,7,678,9)
import socket
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
while True:
 s.sendto(obj, ("192.168.165.124",55555))
 s.sendto(obj1, ("192.168.165.124",55556))
 time.sleep(0.01)

while False:
  s.sendto(obj, ("192.168.165.124",55555))
  s.sendto(obj1, ("192.168.165.124",55556))
  time.sleep(0.01)


