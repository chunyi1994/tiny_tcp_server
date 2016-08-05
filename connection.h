/*************************************************************************
  > File Name: connection.h
  > Author: Sunfish
  > Mail: 704613309@qq.com 
  > Created Time: 2016年07月29日 星期五 14时09分49秒
 ************************************************************************/
#ifndef __CONNECTION_H__
#define __CONNECTION_H__
#include <event.h>
#include <event2/bufferevent.h>
#include "buffer.h"
namespace libevent{
	class Connection{
		public:
			Connection(bufferevent* bev):bev_(bev),buffer_(){
				
			}	
			bool readLine(std::string &line){
				return buffer_.readLine(line);
			}

			bool readLine(std::string &line, char br){
				return buffer_.readLine(line, br);
			}

			std::string read(size_t len){
				return buffer_.read(len);
			}
		
			std::string readAll(){
				return buffer_.read(buffer_.size());
			}
		
		
			void send(const std::string& msg){
				bufferevent_write(bev_, msg.c_str(), msg.length());
			}
		
			void send(const char* msg, size_t len){
				bufferevent_write(bev_, msg, len);
			}
		
			void append(const std::string& msg){
				buffer_.append(msg);	
			}

			void append(const char* msg, size_t len){
				buffer_.append(msg, len);
			}
		private:
			bufferevent* bev_;
			Buffer buffer_;
	};

}
#endif
