#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
int main()
{
 int sockfd,newsockfd,clilen;
 struct sockaddr_in serv_addr,cli_addr;
 char a[50];
time_t now;
struct tm present;
 sockfd=socket(AF_INET,SOCK_STREAM,0);
 if(sockfd<0)
{
printf("socket failed");
exit(1);
}
serv_addr.sin_family=AF_INET;
serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
if(serv_addr.sin_addr.s_addr<0)
{
printf("invalid ip address:unable to decode\n");
exit(1);
}
serv_addr.sin_port=htons(8888);
if(bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
{
printf("bind failed\n");
exit(1);
}
if(listen(sockfd,5)<0)
{
 printf("listen falied");
exit(1);
}
clilen=sizeof(cli_addr);
while(1)
{
	printf("waiting for clients:\n");
	newsockfd=accept(sockfd,(struct sockaddr *)&cli_addr,(socklen_t *)&clilen);
	memset(a,0,sizeof(a));
	read(newsockfd,a,50);
	time(&now);
	present=*localtime(&now);
	sprintf(a,"Time:%d-%d-%d-%d-%d-%d\n",present.tm_year+1900,present.tm_mon+1,present.tm_mday,present.tm_hour,present.tm_min,present.tm_sec);
	write(newsockfd,a,50);
	close(newsockfd);
}
return 0;
}

