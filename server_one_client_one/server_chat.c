#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;


int main(){
	int sock1,cli,len,sent;
	sockaddr_in server,	client;
	char msg[500];


	if((sock1=socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("Socket couldn't be created");
		exit(-1);
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(4000);
	server.sin_addr.s_addr = INADDR_ANY;
	bzero(&server.sin_zero,8);

	len = sizeof(sockaddr_in);

	if(bind(sock1,(sockaddr *)&server,len)==-1){
		perror("Error in binding");
		exit(-1);
	}

	if(listen(sock1,5)==-1){
		perror("listen");
		exit(-1);
	}

	int pid,counter = 0,n = 0;
	char buf[500];
	fflush(stdout);
	while(1){
		if((cli = accept(sock1,(sockaddr *)&client,&len))==-1){
			perror("accept");
			exit(-1);
		}

		//sent = 


		if((pid=fork())==-1){
			close(cli);
			continue;
		}

		else if(pid>0){
			//close(cli);
			counter++;
			continue;
		}

		printf("This is server side\n");


		int pid2 = fork(),r = 1,s = 1;
		if(pid2==0){
			r = 1;
			while(r>0){
				r = recv(cli,buf,sizeof(buf),0);
				if(r>0)
					printf("\t\t\t\t\tReceived message: %s\n", buf);
			}
		}
		else if(pid2>0){
			while(s>0){
				bzero(msg,500);
				n = 0;
				while((msg[n++]=getchar())!='\n');
				s = send(cli,msg,sizeof(msg),0);
			}	
		}
		else{
			perror("Error during fork\n");
		}
		close(cli);
		break;
	}

	return 0;
}