#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
int main(int argc,char* argv[])
{
int sockfd,newsockfd,clilen,servlen;
struct sockaddr_in serv_addr,cli_addr,temp;
char a[50];
sockfd=socket(AF_INET,SOCK_STREAM,0);
serv_addr.sin_family=AF_INET;
if(argc==1)
{
serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
}
else
{
serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
if(serv_addr.sin_addr.s_addr==-1)
{
printf("\n invalid ip address for client\n");
printf("usage:\t%s [IPADDR] \n\n IPADDR\t:\tIP Address of client in mumbers and dots(octet) notation\n",argv[0]);
printf("\n IPADDR is not specified accepts connections from any hosts\n\n Exiting program..\n");
close(sockfd);
}
exit(1);
}
serv_addr.sin_port=htons(3153);
bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
servlen=sizeof(serv_addr);
getsockname(sockfd,(struct sockaddr*)&temp,(socklen_t*)&servlen);
printf("Server local Addr:%s\n",inet_ntoa(temp.sin_addr));
listen(sockfd,5);
clilen=sizeof(temp);
newsockfd=accept(sockfd,(struct sockaddr*)&cli_addr,(socklen_t*)&clilen);
if(newsockfd<0)
printf("connection not established\n");
else
{
printf("connection established\n");
read(newsockfd,a,30);
getpeername(newsockfd,(struct sockaddr*)&temp,(socklen_t*)&clilen);
printf("Peer Address:%s\n",inet_ntoa(temp.sin_addr));
printf("Server received msg:%s\n",a);
write(newsockfd,"Server Response",50);
close(newsockfd);
}
return 0;
}

