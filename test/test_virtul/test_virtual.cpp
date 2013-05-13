#include<iostream>	
#include <stdio.h>
using namespace std;  
  
class A  
{  
public:  
	void foo()	
	{  
		printf("1\n");	
	}  
	virtual void fun()	
	{  
		printf("2\n");	
	}  
};	
class B : public A	
{  
public:  
	void foo()	
	{  
		printf("3\n");	
	}  
	virtual void fun()	
	{  
		printf("4\n");	
	}

	void fnn()
	{
		printf("5\n");
	}
};	
int main(void)	
{  
	A a;  
	B b;  
	A *p = &a;	
	p->foo();  
	p->fun();  
	p = (A *)&b;  
	p->foo();  
	p->fun(); 
	B *ptr = (B *)&a;
	ptr->foo();  
	ptr->fun();  
	return 0;  
}  
