#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/uio.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
int main()
{
	int sockfd;
	char a[50],a1[50],b[50],b1[50];
	struct sockaddr_in serv_addr;
	struct iovec iov[2];
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("192.168.2.58");
	serv_addr.sin_port = htons(2151);
	connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	printf("Enter 1st msg:\n");
	scanf("%s",a);
	printf("Enter 2nd msg:\n");
	scanf("%s",a1);
	iov[0].iov_base = a;
	iov[0].iov_len = 50;
	iov[1].iov_base = a1;
	iov[1].iov_len = 50;
	writev(sockfd,&iov[0],2);
	iov[0].iov_base = b;
	iov[0].iov_len = 50;
	iov[1].iov_base = b1;
	iov[1].iov_len = 50;
	readv(sockfd,&iov[0],2);
	printf("\nClient Recieved msg %s %s",b,b1);
	close(sockfd);
	return 0;
}
