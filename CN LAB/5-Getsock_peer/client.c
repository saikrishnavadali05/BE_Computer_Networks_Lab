#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
int main(int argc,char* argv[])
{
int sockfd;
struct sockaddr_in serv_addr;
char a[50],a1[50];
sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd<0)
{
printf("socket failed\n");
exit(0);
}
serv_addr.sin_family=AF_INET;
if(argc==1)
serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
else
{
serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
if(serv_addr.sin_addr.s_addr==-1)
{
printf("\n invalid ip address for server\n");
printf("usage:\t%sIPADDR\n\nIPADDR\t:\tIP Address of server in numbers and dots(octet) notation\n",argv[0]);
printf("\n ifIPADDR is not specified looks for server in localhost\n\nExisting program..\n");
close(sockfd);
}
exit(1);
}
serv_addr.sin_port=htons(3153);
if(connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
{
printf("connnection failed\n");
exit(0);
}
memset(a,0,sizeof(a));
printf("enter the message:\n");
scanf("%s",a);
write(sockfd,a,50);
read(sockfd,a1,50);
printf("client received the msg:%s\n",a1);
close(sockfd);
if(!strcmp(a1,"exit"))
printf("closing client program\n");
return 0;
}

