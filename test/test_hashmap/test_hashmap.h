#ifndef TEST_HASHMAP_H_
#define TEST_HASHMAP_H_
#include <string>
#include <list> 
#include <hash_map>


using namespace std;
using namespace   __gnu_cxx;


struct my_test{
	my_test(){};
	list<my_test*> get_hm();
	void set_hm(int key, my_test *value);
	int type;
	
	private:
	hash_map<int, my_test*> mtest_hm;
	
};



#endif

