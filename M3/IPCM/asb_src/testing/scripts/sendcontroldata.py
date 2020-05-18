import sys
print (sys.argv)
print (sys.argv[1])

ASB_IP_ADDRESS = "192.168.7.18"


control = int(sys.argv[1])

from struct import Struct
import time
import struct
val =0
obj = struct.pack("=lll", 1,2,val)

import socket
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)


obj = struct.pack("=LLL", 1,2,control)
s.sendto(obj, (ASB_IP_ADDRESS,12345))






while True:
  val = 24 *100000  
  obj = struct.pack("=LLL", 5,2,val)
  s.sendto(obj, (ASB_IP_ADDRESS,12345))
  time.sleep(2)
  

  val = 3300*1000
  obj = struct.pack("=LLL", 5,2,val)
  s.sendto(obj, (ASB_IP_ADDRESS,12345))
  time.sleep(2)
  

