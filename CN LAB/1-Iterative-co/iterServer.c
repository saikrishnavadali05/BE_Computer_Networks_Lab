#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

int main()
{
	int sockfd,newsockfd,clilen;
	struct sockaddr_in serv_addr,cli_addr;
	char a[50];
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	
	if(sockfd<0)
	{
		printf("socket failed\n");
		exit(0);
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if(serv_addr.sin_addr.s_addr < 0)
	{
		printf("Invalid IP address : Unable to decode\n");
		exit(0);
	}
	serv_addr.sin_port = htons(3151);
	if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
	{
		printf("Bind failed\n");
		exit(1);
	}
	clilen=sizeof(cli_addr);
	printf("Waiting for clients' message (\'exit\' to close)\n");
	while(1)
	{
		newsockfd=accept(sockfd,(struct sockadd *)&cli_addr, (socklen_t *) &clilen);
		memset(a, 0, sizeof(a));
		read(newsockfd, a, 50);
		printf("Server Received: %s\n",a);
		write(newsockfd, a, 50);
		close(newsockfd);
		if(!strcmp(a,"exit"))
		{
			printf("Exiting Server\n");
			break;
		}
	}
	return 0;
}
