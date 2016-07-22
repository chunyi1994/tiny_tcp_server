out : main.o multi_thread_server.o
	g++ -o out main.o multi_thread_server.o -levent -lpthread
	
main.o : main.cc
	g++ -c main.cc -std=c++11 -levent -lpthread
	
multi_thread_server.o : multi_thread_server.cc multi_thread_server.h
	g++ -c multi_thread_server.cc -std=c++11 -levent -lpthread
	
clean:
	rm *.o
