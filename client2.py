import socket
s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
host = socket.gethostname()
port = 5000
s.connect((host,port))

tm = s.recv(1024)

s.close()
print("The Time Got from the server is %s" % tm.decode('ascii') )
