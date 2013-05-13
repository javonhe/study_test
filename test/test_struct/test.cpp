#include <memory.h>
#include <stdio.h>
#include <stdlib.h>


struct test{
    char dev_name[5];
    char ipaddr[5];
    char netmask[5];
    char route[5];
    char dns1[5];
    char dns2[5];
    char mode[5];
test(){
}

};


int main(){
	test *mytest = new test();

	memcpy(&mytest->dev_name, "123", 1);

	printf("%d\n", atoi((char *)&mytest->dev_name));


	return 0;
	
}
