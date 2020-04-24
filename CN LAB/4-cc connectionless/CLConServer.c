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
	int sockfd,n,clilen,pid;
	struct sockaddr_in serv_addr,cli_addr;
	char a[50];
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd<0)
	{
		printf("socket failed\n");
		exit(0);
	}
	serv_addr.sin_family=AF_INET;
	
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	if(serv_addr.sin_addr.s_addr<0)
	{
		printf("Invalid IP address: Unable to decode\n");
		exit(0);
	}
	serv_addr.sin_port=htons(3151);
	if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
	{
		printf("Bind failed\n");
		exit(1);
	}
	
	clilen=sizeof(cli_addr);
	printf("Waiting for clients\n");
	
	while(1)
	{
		memset(a,0,sizeof(a));
		n=recvfrom(sockfd,a,50,0,(struct sockaddr *)&cli_addr,(socklen_t *)&clilen);
		if(n>0)
		{
			pid=fork();
			if(pid==0)
			{
				printf("Instance: %d\n\tServer Received: %s\n",(int)getpid(),a);
				if(sendto(sockfd,a,50,0,(struct sockaddr *)&cli_addr,(socklen_t) clilen<0))
				{
					printf("UDP sending failed \nExiting... \n");
					close(sockfd);
					exit(1);
				}
				break;
			}
		}
		else
		{
			printf("UDP receiving failed\nExiting... \n");
			close(sockfd);
			exit(1);
		}
	}
	return 0;
}
	
