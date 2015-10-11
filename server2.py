import socket
import time

from socket import *
from time import *
serversocket = socket(AF_INET,SOCK_STREAM)

host = gethostname()
port = 5000
serversocket.bind((host,port))
serversocket.listen(5)
get = ''
while True:
	clientsocket,addr = serversocket.accept()
	print("GOT THE CONNECTION FROM	%s" % str(addr))

	get = serversocket.getsockopt(SOL_SOCKET,SO_KEEPALIVE)
	print "GET  SOCKET KEEPALIVE : ",get;
	set = serversocket.setsockopt(SOL_SOCKET,SO_KEEPALIVE,1)  
	print "SET SOCKET KEEPALIVE  : ",serversocket.getsockopt(SOL_SOCKET,SO_KEEPALIVE)

	currentTime = ctime(time()) + "\r\n"
	clientsocket.send(currentTime.encode('ascii'))
	clientsocket.close()
