/*************************************************************************
    > File Name: buffer.h
    > Author: Sunfish
    > Mail: 704613309@qq.com 
    > Created Time: 2016年07月29日 星期五 12时29分00秒
 ************************************************************************/
#ifndef __BUFFER_H__
#define __BUFFER_H__
#include <vector>
#include <unistd.h>
#include <string>
#include <algorithm>
#include <string.h>
#include <utility>
#include <iostream>
using namespace std;
namespace libevent{
	class Buffer{
		public:
			Buffer():data_(1024), writeIndex_(0), readIndex_(0){
				data_[0] = '\0';
			}

			size_t size() const{
				return writeIndex_ - readIndex_;
			}

			
			void append(const std::string& msg){
				append(msg.c_str(), msg.length());	
			}

			void append(const char* msg, size_t len){
				if(writeableSize() < len){
					data_.resize(2 * std::max(len,data_.size()));
				}
				::memcpy(writePtr(), msg, len);
				writeIndex_ += len;
				data_[writeIndex_] = '\0';
			}

			void clear(){
				writeIndex_ = 0;
				readIndex_ = 0;
				data_[0] = '\0';
			}

			std::string read(size_t len){
				len = std::min(size(), len);
				std::string ret(readPtr(), len);
				readIndex_ += len;
				if(size() == 0){
					clear();	
				}
				return ret;
			}

			bool readLine(std::string& line){
				return readLine(line, '\n');
			}

			bool  readLine(std::string &str, char br){
				if(size() == 0){
					return false;
				}
				size_t i = readIndex_;
				while(i < writeIndex_){
					if(data_[i] == br){
						break;
					}
					i++;
				}
				str = read(i + 1 - readIndex_);
				return true;
			}

		private:
			const char* readPtr() const{
				auto iter = readIndex_ + data_.begin();	
				return static_cast<const char *>(&*iter);
			}
			
			char* writePtr(){
				auto iter = writeIndex_ + data_.begin();
				return static_cast<char *>(&*iter);
			}	

			size_t writeableSize() const{
				return data_.size() - writeIndex_;
			}
		
			std::vector<char> data_;
			size_t writeIndex_;
			size_t readIndex_;
	};

}
#endif
