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
 int sockfd;
 struct sockaddr_in serv_addr;
 char a[50], a1[50];
 sockfd=socket(AF_INET,SOCK_STREAM,0);
 if(sockfd<0)
 {
  printf("socket failed\n");
  exit(0);
 }
serv_addr.sin_family = AF_INET;
 serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
 serv_addr.sin_port=htons(8888);
if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
{
 printf("connection failed");
 exit(0);
}
memset(a,0,sizeof(a));
write(sockfd,a,50);
read(sockfd,a1,50);
printf("client received %s\n",a1);
close(sockfd);
if(!strcmp(a1,"exit"))
	printf("Closing cllient program\n");
return 0;
}

