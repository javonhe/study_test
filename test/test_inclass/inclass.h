#ifndef INCLASS_H_
#define INCLASS_H_
#include <string>
#include <iostream>


using namespace std;

struct Inclass {
	Inclass();

    struct EnterpriseField {
		void getValue();
	private:
        string pvarName;
        string pvalue;
		//static string getclassname();
        //EnterpriseField(string varName);

    };

	EnterpriseField eap;
	EnterpriseField phase2;
	EnterpriseField identity;
 struct KeyMgmt {

	static const int NONE = 0;
	static const int WPA_PSK = 1;
	static const int WPA_EAP = 2;
	static const int IEEE8021X = 3;

	static const int WPA2_PSK = 4;
private:
	static const string varName;

	static const string strings[];
//private:
	//KeyMgmt();
};

 

};
 const string varName = "key_mgmt";
 const string strings[] = { "NONE", "WPA_PSK", "WPA_EAP", "IEEE8021X",
		"WPA2_PSK" };



#endif

