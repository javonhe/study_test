#include "mgr_fmeta.h"  
#include <errno.h>  
#include <cstring>  
  
Fmeta::Fmeta(const int &n):fHash(n)  
{  
 int ret=system((string("mkdir -p  ")+string(METADATAFILE)).c_str());  
    
 if(ret==-1)  
     spfs_log(ERR,high,"create metadata dir err,%s at line %d in %s.",strerror(errno),__LINE__,__FILE__);  
}  
  
Fmeta::~Fmeta()  
{  
    hash_map<string,Fmeta*,str_hash>::iterator it;  
  
    for(it=fHash.begin();it!=fHash.end();++it)  
        delete it->second;  
  
}  
  
int Fmeta::create_fmeta(const char * pathname,Myint *inode)  
{  
    string last_name=string(METADATAFILE)+string("/")+string(pathname);  
  
   int ret=open(last_name.c_str(),O_RDWR|O_CREAT,S_IRWXU|S_IRWXG|S_IRWXO);  
  
   if(ret==-1)  
   {  
       spfs_log(ERR,high,"cann't create metadata file at %d in %s. ",__LINE__,__FILE__);   
       *inode=0;  
       return ret;  
   }  
     
   close(ret);  
    //获取元数据文件的索引节点  
    struct stat buf;  
    memset(&buf,0,sizeof(struct stat));  
  
   if(stat(last_name.c_str(),&buf)==-1)  
   {  
       spfs_log(ERR,high,"can't get inode of metadata at %d in %s.",__LINE__,__FILE__);  
       return -1;  
   }         
     
   *inode=buf.st_ino;  
     
  return 0;  
  
}  
  
  
void Fmeta::copy_fmeta(Fmeta * dst, const Fmeta* src)  
{  
   dst->u_stat.st_size=src->u_stat.st_size;  
   dst->u_stat.st_ino=src->u_stat.st_ino;  
   dst->u_stat.st_mode=src->u_stat.st_mode;  
   dst->u_stat.ver=src->u_stat.ver;  
  
   dst->p_stat.big_or_small=src->p_stat.big_or_small;  
  
   size_t k=src->p_stat.var.size();  
   var_size v;  
   memset(&v,0,sizeof(var_size));  
  
   dst->p_stat.var.clear();  
  
   for(size_t i=0;i!=k;++i)  
   {  
       v.offset=src->p_stat.var[i].offset;  
       v.size=src->p_stat.var[i].size;  
       v.index=src->p_stat.var[i].index;  
  
       dst->p_stat.var.push_back(v);  
       memset(&v,0,sizeof(var_size));  
   }  
  
}  
  
  
int Fmeta::get_fmeta(const char *pathname,Fmeta *meta)  
{  
   hash_map<string,Fmeta *,str_hash>::iterator it;  
   it=fHash.find(string(pathname));  
  
   if(it==fHash.end())  
   {  
       spfs_log(ERR,high,"cann't get metadata at line %d in %s.",__LINE__,__FILE__);  
       return -1;  
   }  
  //逐个复制成员  
   copy_fmeta(meta,it->second);  
   return 0;  
  
}  
  
  
int Fmeta::set_fmeta(const char *pathname,const Fmeta* meta)  
{  
    //首先查找，see是否已经存在  
    hash_map<string,Fmeta*,str_hash>::iterator  it;  
  
    if((it=fHash.find(string(pathname)))!=fHash.end())//是修改元数据操作  
    {  
       copy_fmeta(it->second,meta);  
  
    }  
    else//是第一次加入内存元数据  
    {  
        Fmeta *ptr=new Fmeta;  
          
        if(ptr==NULL)  
        {  
            spfs_log(ERR,high,"set metadata error at line %d in %s.",__LINE__,__FILE__);  
            return -1;  
        }  
  
        copy_fmeta(ptr,meta);  
        fHash.insert(make_pair(string(pathname),ptr));  
    }  
   return 0;  
}  

