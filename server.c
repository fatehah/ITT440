#include<stdio.h>
# include<sys/socket.h>
# include<arpa/inet.h> //inet_addr
int main (int argc, char *argv[])
{

int socket_desc, new_socket,c;
struct sockaddr_in server,client;

//CREATE SOCKET
socket_desc = socket(AF_INET, SOCK_STREAM, 0);

if (socket_desc ==-1)
{
printf("Could not create socket");
}

server.sin_addr.s_addr = inet_addr("74.125.235.20");
server.sin_family = AF_INET;
server.sin_port = htons(1026);

//CONNECT TO REMOTE SERVER

if(connect(socket_desc,(struct sockaddr *)&server, sizeof(server))<0)
{
	puts("connect error");
	return 1;
}
puts("connected");

//Bind
if(bind(socket_desc,(struct sockaddr *)&server ,sizeof (server))<0)
{
	puts("bind failed");
}
puts("BIND DONE!!");


//Listen
listen(socket_desc,3);
//Accept and incoming connection 
puts("Waiting for incoming connection..");
c= sizeof (struct sockaddr_in);
new_socket=accept(socket_desc,(struct sockaddr *)&client,(socklen_t*)&c);

if(new_socket<0)
{
perror("accept failed");
}
puts("Connection accepted");


//IPv4 AF_INET sockets:
struct sockaddr_in
{
short sin_family;
unsigned short sin_port[htons(1026)];
struct in_addr sin_addr;
char sin_zero[10];
};


struct in_addr
{
unsigned long s_addr;

};

struct sockaddr
{
unsigned short sa_family;
char sa_data [14];
};


return 0;

}
