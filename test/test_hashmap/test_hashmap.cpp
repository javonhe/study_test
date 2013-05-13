#include "test_hashmap.h"
#include <stdio.h>


list<my_test*> my_test::get_hm(){
	hash_map<int, my_test*>::iterator it;
	list<my_test*> list_t;
	for(it=mtest_hm.begin();it!=mtest_hm.end();++it){
		list_t.push_back(it->second);
	}

	return list_t;
}


void my_test::set_hm(int key, my_test *value){
	mtest_hm[key] = value;
}


int main(){
	list<my_test*> my_list;
	my_test *value1 = new my_test;
	value1->type = 3;

	value1->set_hm(1, value1);

	my_list = value1->get_hm();

	list<my_test*>::iterator ir;

	for(ir=my_list.begin();ir!=my_list.end();++ir){
		printf("type: %d\n", (*ir)->type);
	}	


	return 1;
}