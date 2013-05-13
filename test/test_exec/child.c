#include <stdio.h>
#include <stdlib.h>

int main(){
	while(1){
		printf("I'm child\n");
		sleep(1);
	}

	printf("child gone\n");

	return 1;
}
