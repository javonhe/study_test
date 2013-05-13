#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	unsetenv("LD_PRELOAD");
	return 0;
}
