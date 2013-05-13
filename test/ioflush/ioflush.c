#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int glob = 6;
char buf[] = "a write to stdout\n";

int main(void)
{
	int var;
	pid_t pid;

	var = 88;

	if(write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1)
		write(STDOUT_FILENO, "worte error\n", strlen("worte error\n"));

	printf("before fork");
	fflush(stdout);

	if((pid = fork()) < 0)
	{
		write(STDOUT_FILENO, "fork error\n", strlen("fork error\n"));
	}
	else if(pid == 0)
	{
		glob++;
		var++;
		sleep(1);
		printf("1111111\n");
		
	}
	else
		{
		sleep(2);
		printf("22222222\n");
		}

	//sleep(2);
	printf("pid=%d, glob=%d, var=%d\n", getpid(), glob, var);
}
