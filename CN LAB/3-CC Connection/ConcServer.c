#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
int main()
{
        int sockfd,newsockfd,clilen,pid;
	struct sockaddr_in serv_addr,cli_addr;
	char a[50];
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		printf("socket failed\n");
		exit(0);
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
	{
		printf("bind failed\n");
		exit(1);
	}
	if(listen(sockfd,5)<0)
	{
		printf("listen failed\n");
		exit(0);
	}
	clilen = sizeof(cli_addr);
	printf("waiting for clients\n");
	while(1)
	{
		newsockfd = accept(sockfd,(struct sockaddr *)&cli_addr,(socklen_t *)&clilen);
		pid = fork();
		if(pid==0)
		{
			while(1)
			{
				memset(a,0,sizeof(a));
				read(newsockfd,a,50);
				printf("Instance:%d\n\tServer Received:%s\n",(int)getpid(),a);
				write(newsockfd,a,50);
				if(!strcmp(a, "exit"))
				{
					printf("closing connection : Instance-%d\n",(int)getpid());
					break;
				}
			}
			close(newsockfd);
			break;
		}
	}
	return 0;
}
