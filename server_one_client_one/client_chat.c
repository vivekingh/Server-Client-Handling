#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>//definition of all datatypes used in system calls 
#include<netinet/in.h>// definition of structures needed for sockets
#include<arpa/inet.h>// constants and structures needed for domain address
#include<errno.h>


typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;


int main(){
	sockaddr_in client,server;
	int sock2,len = sizeof(sockaddr),n=0;;

	char msg[500];

	if((sock2=socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("Client socket couldn't be created");
		exit(-1);
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(4000);
	server.sin_addr.s_addr = INADDR_ANY;
	bzero(&server.sin_zero,8);

	if(connect(sock2,(sockaddr *)&server,len)){
		perror("Connection failed --\n");
		exit(-1);
	}	
	char buf[500];
	printf("This is client side\n");

	int pid = fork(),r = 1,s= 1;

	if(pid==0){
		r = 1;
		while(r>0){
			int r = recv(sock2,buf,sizeof(buf),0);
			if(r>0)
				printf("\t\t\t\t\tReceived message: %s\n", buf);
		}
	}
	else if(pid>0){
		while(s>0){
			bzero(msg,500);
			n = 0;
			while((msg[n++]=getchar())!='\n');
			s = send(sock2,msg,sizeof(msg),0);
		}
	}
	else{
		perror("Error during fork\n");
		close(sock2);
	}
	close(sock2);
	return 0;
}