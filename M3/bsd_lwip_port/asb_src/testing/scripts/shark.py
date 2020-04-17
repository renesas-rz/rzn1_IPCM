import pcapy
import struct
import sys
import socket
from impacket.ImpactDecoder import *
from impacket.ImpactPacket import *

#print (sys.argv[1])

port1 = sys.argv[1]
port2 = sys.argv[2]

# to install pcapy
# sudo apt-get install python-pcapy

from impacket.ImpactDecoder import *

def dump(obj):
   for attr in dir(obj):
       if hasattr( obj, attr ):
           print( "obj.%s = %s" % (attr, getattr(obj, attr)))



max_bytes = 1024
promiscuous = False
read_timeout = 500 # in milliseconds
pc = pcapy.open_live("enp0s25", max_bytes, promiscuous, read_timeout)

#print pc


# callback for received packets
def recv_pkts(hdr, data):
  #print dump(data)
  packet = EthDecoder().decode(data)
  child = packet.child()
  #print isinstance(child, IP)
  #print child.get_th_dport()

  #print dump(packet)

  #print packet.child().get_ip_p()

  if ( (packet.get_ether_type() == ImpactPacket.IP.ethertype) and (         packet.child().get_ip_p() == socket.IPPROTO_UDP)) :
    port = packet.child().child().get_uh_dport()

    if ((port == 55555) or (port == 55557)) :
      #print dump (packet.child())

      #print packet.child().child().get_uh_dport()
      format_str = "I" * (len(packet.get_data_as_string())/4)
      un = struct.unpack(format_str, packet.get_data_as_string())

      #print un[30]
      #print type(un)
      for index in range( len(un)):
          #print index
          if ((index >= 11) and (index <= 30)) :
             #print ("0x%08x" % un[index])
             print ( un[index])
    


packet_limit = -1 # infinite
pc.loop(packet_limit, recv_pkts) # capture packets
