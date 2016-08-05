#ifndef __UTILS_H__
#define __UTILS_H__
#include <string>
#include <netdb.h>
#include <sys/socket.h>
#include <assert.h>
#include <arpa/inet.h>
#include<ctime>
namespace libevent{

static std::string getTime(){
    std::time_t t;
    std::time ( &t );
    std::string tStr = std::ctime(&t);
    //去掉回车
    tStr.erase(tStr.size() - 1, 1);
    return tStr;
}

static void log(const std::string & msg){
    std::cout<<getTime()<<" : "<<msg<<std::endl;
}


static bool beginWith(const std::string& content, size_t pos, const std::string& str){
    size_t len =  str.length();
    assert(content.length() >= len);
    for(size_t i = 0; i < len; i++, pos++){
        if(str[pos] != beginStr[i]){
            return false;
        }
    }
    return true;
}

static bool isIpAddress(std::string host){
    size_t len = host.length();
    for(size_t i = 0; i < len; i++){
        if(host[i] != '.' && (host[i] < '0' || host[i] > '9')){
            return false;
        }
    }
    return true;
}

static size_t getPathStartPosByUrl(std::string url){
    size_t left = 0;
    size_t right;
    if(beginWith(url, 0, "http://")){
        left = 7;
    }

    right = url.find("/", left);

    return right;
}

static std::string getHostByUrl(std::string url){
    size_t left = 0;
    size_t right;
    if(beginWith(url, 0, "http://")){
        left = 7;
    }

    if((right = url.find("/", left)) == std::string::npos){
        right = url.length();
    }

    return url.substr(left, right - left);
}


static std::string getIpByUrl(std::string url){
    std::string host = getHostByUrl(url);
    if(isIpAddress(host)){
        return host;
    }
    std::string ip;
    struct hostent *ht = NULL;
    ht = gethostbyname(host.c_str());
    assert(ht);
    ip = inet_ntoa(*(in_addr*)ht->h_addr_list[0]);

    return ip;
}

static std::string getPathByUrl(std::string url){
    size_t left = 0;
    size_t right;
    if(beginWith(url, 0, "http://")){
        left = 7;
    }

    if((right = url.find("/", left)) == std::string::npos){
        return std::string("/");
    }else{
        return url.substr(right, url.length() - right);
    }


}
}
#endif


#endif // UTILS

