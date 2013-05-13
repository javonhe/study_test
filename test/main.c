#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdarg.h>

int main()
{
	char *tmp = NULL;
	char *args = NULL;

	tmp = strdup("hezhiwen:javon.he");
	args = strchr(tmp, ':');
	*args = '\0';
	args++;

	printf("tmp=%s\n", tmp);

}
