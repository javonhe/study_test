#ifndef MGR_FMETA_H_INCLUDED  
#define MGR_FMETA_H_INCLUDED  
  
#include <unistd.h>  
#include <sys/stat.h>  
#include <sys/types.h>  
#include <fcntl.h>  
#include <cstdio>  
#include <cstdlib>  
#include <cstddef>  
#include <cstring>  
#include <string>  
#include <ext/hash_map>  
#include "spfs_pack.h"  
#include <cstdint>  
#include "spfs_log.h"  
using std::string;  
using __gnu_cxx::hash_map;  
  
//��Ԫ������Ϣֱ�������ڴ���  
//����Ԫ������  
  
#define METADATAFILE "/home/javon/metadata"  
typedef unsigned int Myint;  
  
class Fmeta  
{  
public:  
explicit Fmeta(const int &n);  
~Fmeta();  
int create_fmeta(const char * pathname,Myint *inode);//�������𴴽��ļ�  
int get_fmeta(const char * pathname,Fmeta *meta); //��Ԫ����  
int set_fmeta(const char * pathname,const Fmeta * meta);//дԪ����  
  
private:  
struct str_hash  
{  
    size_t operator()(const string &str) const    
    {     
        size_t  hash=0;  
  
        for(size_t i=0;i!=str.length();++i)  
            hash=((hash<<5)+hash)+(size_t)str[i];  
  
        return hash;  
    }     
};  
void copy_fmeta(Fmeta* dst, const Fmeta * src);  
hash_map<string,Fmeta*,str_hash> fHash;  
};  
  
  
  
#endif // MGR_FMETA_H_INCLUDED 

