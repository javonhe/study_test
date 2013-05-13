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
  
//将元数据信息直接做在内存中  
//管理元数据类  
  
#define METADATAFILE "/home/javon/metadata"  
typedef unsigned int Myint;  
  
class Fmeta  
{  
public:  
explicit Fmeta(const int &n);  
~Fmeta();  
int create_fmeta(const char * pathname,Myint *inode);//仅仅负责创建文件  
int get_fmeta(const char * pathname,Fmeta *meta); //读元数据  
int set_fmeta(const char * pathname,const Fmeta * meta);//写元数据  
  
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

