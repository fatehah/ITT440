
import socket
import sys
import errno
import os

#create a TCP/IP socket
sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

#Bind the socket to the port
server_address = ('localhost', 10000)
print >>sys.stderr,'starting up on %s port %s' % server_address
sock.bind(server_address)

while True:
	print >>sys.stderr, '\nwaiting to receive message'
	data, address = sock.recvfrom(4096)
		
	print >>sys.stderr, 'received %s bytes from %s' %(len(data),address) 
	print >>sys.stderr, data

	if data:
		sent = sock.sendto(data,address)
		print >>sys.stderr, 'sent %s bytes back to %s' % (sent, address)
   		
	get = sock.getsockopt(socket.SOL_SOCKET,socket.SO_KEEPALIVE)
	print "GET SOCKET KEEPALIVE :",get
        	#pitfall 1        
	if get>0:
		print "Already set"
	elif get<0:
		print "Error",errno.EALREADY
		print "Description",os.strerror(errno.EALREADY)
		
		#pitfall 2
		sock.close()
		
		#pitfall 3

	set = sock.setsockopt(socket.SOL_SOCKET,socket.SO_KEEPALIVE,1)
	print "SET SOCKET KEEPALIVE : ", sock.getsockopt(socket.SOL_SOCKET, socket.SO_KEEPALIVE)

	break
sock.close()
