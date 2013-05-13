#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>


int main(){
	char c;
	pid_t pid;
	int status = 0;
	while((c = getchar()) != EOF){
		if(c == 's'){
			if((pid = fork()) < 0){
				printf("fork error\n");
			}
			else if(pid == 0){
				if(execl("./child", "child", (char *)0) < 0)
					printf("exec child error\n");
			}
		}

		if(c == 'e'){
			kill(pid, SIGTERM);
			while (waitpid(pid, &status, 0) == -1) {
				if (errno != EINTR) {
					printf("waitpid: %s\n", strerror(errno));
					status = -1;
					break;
				}
			}
		}
		
	}

	return 1;

}


