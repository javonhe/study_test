#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>	 
int main(int argc,char * argv[],char ** environ)
{
    pid_t pid;
    int stat_val;
	char buf[256] = {0};

	int pip_fd[2];

	//int filedes = open("dd.txt",O_RDWR|O_TRUNC);

	if(pipe(pip_fd) < 0)
	{
		printf("pipe error\n");
		return -1;
	}
 
    pid = fork();
    switch(pid)
    {
        case -1:
            perror("Process Creation failed\n");
            exit(1);
        case 0:
            printf("child process is running!\n");
            printf("My pid = %d,parentpid = %d\n",getpid(),getppid());
			close(pip_fd[0]);
			dup2(pip_fd[1], 1);
			close(pip_fd[1]);
            execve(argv[1],argv, environ);
            printf("process never go ro here!\n");
            exit(0);
        default:
            printf("Parent process is running\n");
			close(pip_fd[1]);
            break;
    }

	if(read(pip_fd[0], buf, sizeof(buf)) <0 )
		printf("read error\n");
	else
		printf("the buf read:%s\n", buf);

	
 	printf("wait for child1\n");
    wait(&stat_val);
	
	printf("wait for child2\n");
    exit(0);
}

