.PHONY:all
all:calserver calclient

calclient:calclient.cc 
	g++ -o $@ $^ -std=c++11 -ljsoncpp

calserver:calserver.cc 
	g++ -o $@ $^ -std=c++11 -lpthread -ljsoncpp

.PHONY:clean
clean:
	rm -rf calclient calserver
