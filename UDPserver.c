#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int main ()
{
	int udpSocket, nBytes;
	char buffer[1024];
	struct sockaddr_in serverAddr,clientAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size, client_addr_size;
	int j,len,value;

//create UDP socket
	udpSocket = socket(PF_INET, SOCK_DGRAM,0);
//configure settings in address struct
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(7891);
	serverAddr.sin_addr.s_addr = inet_addr ("127.0.0.1");
	memset(serverAddr.sin_zero, '\0',sizeof serverAddr.sin_zero);

//bind socket with address
	bind(udpSocket,(struct sockaddr  *)&serverAddr,sizeof(serverAddr));

//initialize size variable to be used later on
	addr_size = sizeof serverStorage;

while(1)
{
//try to receive any incoming UDP datagram.address and port of requesting client will be stored on serverStorage variable

	nBytes = recvfrom(udpSocket,buffer,1024,0,(struct sockaddr *)&serverStorage, &addr_size);

//convert message received to uppercase
	for(j=0; j<nBytes -1;j++)
	buffer[j] = toupper(buffer[j]);

//send uppercase message back to client, using serverStorage as the address
	sendto(udpSocket,buffer,nBytes,0,(struct sockaddr *)&serverStorage,addr_size);

	getsockopt(udpSocket,SOL_SOCKET, SO_DONTROUTE, &value, &len);
	if(value==0)
	{
		printf("UNABLE TO GET %d \n",errno);
		printf("UNABLE TO GET %d \n",strerror(errno));
	}
	else 
		printf("SUCCESS!! value : %d \n",&value);
	
	
	value =32768;
	setsockopt(udpSocket,SOL_SOCKET, SO_DONTROUTE, &value, sizeof(value));
	printf("ALREADY SET \n");


	getsockopt(udpSocket,SOL_SOCKET, SO_DONTROUTE, &value, &len);
	if(value ==0)
		printf("UNABLE TO GET NEW CONNECTION %d \n");
	else
		printf("CAN GET THE NEW CONNECTION %d \n",value);		
	}
return 0;
}
