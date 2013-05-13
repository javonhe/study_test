#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
	 
int main(int argc,char * argv[],char ** environ)
{
    int i;
 
    printf("i am a process image!\n");
	sleep(1);
    printf("my pid = %d, parentpid = %d\n",getpid(),getppid());
	sleep(1);
    printf("my uid = %d, gid = %d\n",getuid(), getgid());
	sleep(1);
 
    for(i=0; i<argc; i++)
        printf("argv[%d]:%s\n",i,argv[i]);
}

