#include<iostream>
#include<string>
#include<cstring>
#include<cerrno>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>

void Usage(std::string proc)
{
    std::cout << "Usage : " << proc << "port" << std::endl;
}
int main(int argc,char* argv[])
{
    if(argc != 2)
    {
        Usage(argv[0]);
        return 1;
    }

    //1.创建套接字
    int listen_sock = socket(AF_INET,SOCK_STREAM,0);
    if(listen_sock < 0)
    {
        std::cerr << "socket error:" << errno << std::endl;
        return 2;
    }

    //2.bind
    struct sockaddr_in local;
    memset(&local,0,sizeof(local));
    local.sin_family = AF_INET;
    local.sin_port = htons(atoi(argv[1]));
    local.sin_addr.s_addr = INADDR_ANY;

    if(bind(listen_sock,(struct sockaddr*)&local,sizeof(local)) < 0)
    {
        std::cerr << " bind error " << errno << std::endl;
        return 3;
    }

    //3.因为tcp是面向连接的 a.在通信前，需要建立连接。 b.然后才能通信
    //一定会有人主动来建立（客户端，需要服务），一定有人被动接受连接（服务端，提供服务）
    //我们当前写的server需要不断的等待用户的到来，提供一个连接的功能
    //设置套接字是listen状态,本质是允许用户连接的

    const int back_log = 5;
    if(listen(listen_sock,5) < 0)
    {
        std::cerr << " listen error " << errno << std::endl;
        return 4;
    }
    for( ; ; )
    {
        struct sockaddr_in peer;
        socklen_t len = sizeof(peer);
        int new_sock = accept(listen_sock,(struct sockaddr*)&peer,&len);
        if(new_sock < 0)
        {
            continue;
        }

        //提供服务
        while(true)
        {
            char buffer[1024];
            memset(buffer,0,sizeof(buffer));
            ssize_t s = read(new_sock,buffer,sizeof(buffer)-1);
            if(s > 0)
            {
                //读取成功
                buffer[s] = 0;
                std::cout << " client#   " << buffer << std::endl;
                std::string echo_string = " >>>server<<< ";
                echo_string += buffer;

                write(new_sock,echo_string.c_str(),echo_string.size());

            }
            else if( s == 0)
            {
                std::cout << " client quit ... " << std::endl;
                break;
            }
            else
            {
                std::cerr << " read error " << std::endl;
                break;
            }
        }
    }
    return 0;
}