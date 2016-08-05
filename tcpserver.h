
#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__

#include <unistd.h>
#include <iostream>
#include <event.h>
#include <vector>
#include <event2/bufferevent.h>
#include <pthread.h>
#include <memory>
#include <map>
#include <mutex>
#include "connection.h"
#include "utils.h"

namespace libevent{
	typedef std::shared_ptr<Connection> ConnectionPtr;
	const int THREADS_NUM = 4;
	const int BACKLOG = 10;
	class TcpServer;

	struct MultiThreadData{
        MultiThreadData():tid_(0), base_(NULL), server_(NULL){
            pipeFd_[0] = -1;
            pipeFd_[1] = -1;
        }
		pthread_t tid_;
		int pipeFd_[2]; //fd[0]可以读,fd[1]可以写
		struct event_base* base_;
		TcpServer *server_;
	};
	
	class TcpServer{
		friend void cbClose(bufferevent* bev, short event, void *arg);
		friend void cbAccept(int fd, short events, void*arg);
		friend void cbRead(bufferevent *bev, void* arg);
		friend void cbThreadReadyForRead(int fd, short events, void* arg);
		public:
			TcpServer(size_t port);
			~TcpServer();

			void start();
			event_base* base() const;	
			//void send(bufferevent *bev, const std::string &msg);
		
		protected:
			//在派生类中覆盖一个自己的readCallback
			virtual void readCallback(const ConnectionPtr& conn);
			virtual void closeCallback(const ConnectionPtr& conn);
			virtual void newConnectionCallback(const ConnectionPtr& conn);
            virtual void startCallback();
			size_t port_;
			struct event_base* base_;
			int listenfd_;
		private:
			int initTcpServer(int backlog);
			void handleRead(bufferevent *bev);
			void handleClose(bufferevent* bev, short event);
			void handleNewConnection(bufferevent *bev);
			void initThreads();
		
			std::vector<MultiThreadData> threadsData_;
			std::map<bufferevent *, ConnectionPtr> connections_;	
			std::mutex mutex_;

	};



}
#endif
