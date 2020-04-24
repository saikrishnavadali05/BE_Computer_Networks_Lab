#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/tcp.h>
int main()
{
	int sockfd,MAXSEG,sndbuf,optlen;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	optlen = sizeof(MAXSEG);
	getsockopt(sockfd,IPPROTO_TCP,TCP_MAXSEG,&MAXSEG,(socklen_t*)&optlen);
	printf("MaxSeg = %d\n",MAXSEG);
	sndbuf = 4869;
	setsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,(char*)&sndbuf,sizeof(sndbuf));
	optlen = sizeof(sndbuf);
	getsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,(char*)&sndbuf,(socklen_t*)&optlen);
	printf("sndbuf = %d\n",sndbuf);
	return 0;
}
