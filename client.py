import socket
client_socket = socket.socket(1)
server_address = 'localhost'
server_port = 555
client_socket.connect((server_address,server_port))
data=client_socker.recv(1024)
print data

client_socket.close()

