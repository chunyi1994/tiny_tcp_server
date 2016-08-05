/*************************************************************************
    > File Name: main.cc
    > Author: Sunfish
    > Mail: 704613309@qq.com
    > Created Time: 2016年07月21日 星期四 19时29分52秒
 ************************************************************************/
#include "tcpserver.h"
#include <iostream>
#include <string.h>
using namespace std;
using namespace libevent;

class MyTcpServer : public TcpServer{
    public:
    MyTcpServer(int port):TcpServer(port){}

    protected:
    virtual void readCallback(const ConnectionPtr& conn){
        std::string msg = conn->readAll();
        conn->send(msg);
        cout<<msg<<endl;
    }

    virtual void closeCallback(const ConnectionPtr& conn){
        log("closeCallback");
    }
    virtual void newConnectionCallback(const ConnectionPtr& conn){
         log("newConnectionCallback");
    }

    virtual void startCallback(){
         log("startCallback");
    }
};

int main(int argc, char** argv){
   // if(argc <= 1){
      //  return -1;
    //}

   // int port = atoi(argv[1]);
    int port = 23333;
    MyTcpServer server(port);
    server.start();
    return 0;
}
