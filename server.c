#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h> //inet_addr
int main (int argc, char *argv[])
{

	int socket_desc,mysock,rval;
	int op_val,route;
	struct sockaddr_in serv_addr;
	char buff[1024];


	//CREATE SOCKET
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
 
	if (socket_desc < 0)
	{
		printf("Failed to create socket");
		exit(1);
	}


	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port =htons(2500);

	//Bind
	if(bind(socket_desc,(struct sockaddr *)&serv_addr,sizeof (serv_addr)))
	{
		perror("bind failed");
		exit(1);	
}

//Listen
listen(socket_desc,5);
//Accept and incoming connection 
do{
mysock = accept(socket_desc,(struct sockaddr *)0,0);
if(mysock ==-1)
{
perror("accept failed");
}
else
{
memset(buff, 0, sizeof(buff));
if((rval = recv(mysock,buff,sizeof(buff),0))<0)
perror("readimg message error");
else if(rval == 0)
printf("ending connection");
else
printf("MSG : %s\n",buff);
printf("got the message (rval = %d)\n",rval);

getsockopt(socket_desc,SOL_SOCKET, SO_DONTROUTE, &op_val, &route);
if(op_val != 0)
{
	printf ("UNABLE TO GET \n");
}
printf("Get SO_DONTROUTE : %d\n", op_val);
op_val = 1;
setsockopt(socket_desc, SOL_SOCKET, SO_DONTROUTE, &op_val, sizeof(op_val));
	printf("ALREADY set \n");
getsockopt(socket_desc, SOL_SOCKET, SO_DONTROUTE, &op_val, &route);
if(op_val == 0)
	printf("UNABLE TO GET \n");
else
	printf("GET NEW SO_DONTROUTE : %d\n",op_val);


close (mysock);
}
}
while(1);

return 0;
}
