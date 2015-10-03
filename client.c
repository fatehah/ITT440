#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#define DATA "Hello My Socket"

int main(int argc, char *argv[])
{
	int sock_desc;
	struct sockaddr_in server;
	struct hostent *hp;
	char buff[1024];

	sock_desc  = socket(AF_INET,SOCK_STREAM,0);
	if(sock_desc < 0)
	{
		perror("Socket Failled");
		exit(1);
	}
	server.sin_family =AF_INET;
	hp = gethostbyname(argv[1]);
	if(hp == 0)
	{
		perror("gethostbyname FAILED");
		close(sock_desc);
		exit(1);		
	}
	memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
	server.sin_port =htons(2500);

	if(connect(sock_desc,(struct sockaddr *) &server,sizeof(server)) < 0)
	{
		perror("Connection Failed");
		close(sock_desc);
		exit(1);
	}

	if(send(sock_desc, DATA, sizeof(DATA),0) <0)
	{
		perror("send failed");
		close(sock_desc);
		exit(1);
	}

	printf("SENT %s\n",DATA);
	close(sock_desc);
	return 0;
}
