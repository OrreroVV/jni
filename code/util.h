#ifndef __UTIL_H__
#define __UTIL_H__

#include <execinfo.h>
#include <sys/time.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <syscall.h>

namespace hzh{

pid_t GetThreadId(){
    return syscall(SYS_gettid);
}



}


#endif