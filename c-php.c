// C program to connect to the socket opened by php module

#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<malloc.h>
#include"myfunc.h"
//#include<conio.h>
//max buffer size
#define buffer_size 100




// main function
// takes port and address as arguments
int main(int argc , char *argv[])
{

	if(argc<1)
	{
		printf("Error : pass the argument <address> <port number>\n");
		exit(EXIT_FAILURE);
	}


	int listenfd=0,connfd=0;
	struct sockaddr_in serv_addr;	// creating variable of data type 'struct sockaddr_in'
	
	
	// create a memory buffer 
	char buffer[buffer_size];
	char *send_ack="your message received\n";
	// create socket
	listenfd=socket(AF_INET, SOCK_STREAM,0);
	if(!listenfd)
	{
		printf("Error : Scoket failed\n");
	///	free(buffer);
		exit(EXIT_FAILURE);
	}
	
	memset(&serv_addr, '0', sizeof(serv_addr));
   	memset(buffer, '0', sizeof(buffer)); 
	
	serv_addr.sin_family=AF_INET;

	//server address
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);	//listen to any internal address

	// set port number
	int port=atoi(argv[1]);
	serv_addr.sin_port=htons(port);
	

	//bind address
	if(bind(listenfd,(struct sockaddr*)&serv_addr, sizeof(serv_addr))<0)
	{
		printf("Error : Binding failed\n");
        //        free(buffer);
                exit(EXIT_FAILURE);
	} 

	//listen to 10 clientd
	listen(listenfd,10);
	
	while(1)
	{
		printf("Server started\n");
		connfd=accept(listenfd,(struct sockaddr *)NULL,NULL);
	
		//get the input data from php

		int byteRead=read(connfd,buffer,buffer_size);
		buffer[byteRead]='\0';


		if((strcmp(buffer,"exit"))==0)
		{
			write(connfd,"server close",sizeof("server close"));
			printf("Server shutdown\n");
			close(connfd);
			exit(EXIT_SUCCESS);
		}

		printf("Call to myfunction\n");
		
		//call to userdefined function present in myfunc.h
		myfunc(buffer);

		printf("return from myfunction\n\n");
		
		//write the computed data back to php
        	write(connfd,send_ack,strlen(send_ack)); 
		
        	close(connfd);
        	sleep(1);
	}
	
	// free allocated memory buffer
//	free(buffer);

	exit(EXIT_SUCCESS);

}
