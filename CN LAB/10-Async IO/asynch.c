#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>

#define BUFFSIZE 1024

int sigflag;

int main()
{
	int n;
	char buff[BUFFSIZE];
	void sigio_func();
	signal(SIGIO,(void *)sigio_func);
	if(fcntl(0,F_SETOWN,getpid())<0)
		printf("F_SETOWN Error");
	if(fcntl(0,F_SETFL,FASYNC)<0)
		printf("F_SETFL Error");
	
	for(;;)
	{
		sigblock(sigmask(SIGIO));
		while(sigflag==0)
			sigpause(0);
		if((n=read(0,buff,BUFFSIZE))>0)
		{
			if(write(1,buff,n)!=n)
				printf("Write Error");
		}
		else if(n<0)
			printf("Read Error");
		else if(n==0)
			exit(0);
		sigflag=0;
		sigsetmask(0);
	}
	return 0;
}

void sigio_func()
{
	sigflag=1;
	return;
}
