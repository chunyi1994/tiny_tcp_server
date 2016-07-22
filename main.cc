/*************************************************************************
    > File Name: main.cc
    > Author: Sunfish
    > Mail: 704613309@qq.com 
    > Created Time: 2016年07月21日 星期四 19时29分52秒
 ************************************************************************/
#include "multi_thread_server.h"
#include <iostream>
#include <string.h>
using namespace std;
using namespace libevent;

class MyTcpServer : public TcpServer{
	public:
	MyTcpServer(int port):TcpServer(port){}

	protected:
	virtual void readCallback(bufferevent *bev, const std::string &msg){
		cout<<msg<<endl;
		send(bev, msg);
	}
};

int main(int argc, char** argv){
	if(argc <= 1){
		return -1;
	}
	
	int port = atoi(argv[1]);
	MyTcpServer server(port);
	server.start();
	return 0;
}
