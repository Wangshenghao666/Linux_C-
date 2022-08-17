#include <iostream>
#include <string>
#include <sys/select.h>
#include "Sock.hpp"

// 定义宏，数组最大元素
#define NUM (sizeof(fd_set) * 8)
int fd_array[NUM]; //内容>=0,合法的fd，如果是-1,该位置没有fd
static void Usage(std::string proc)
{
    std::cout << "Usage:" << proc << " "
              << "port" << std::endl;
}
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        Usage(argv[0]);
        exit(1);
    }
    uint16_t port = (uint16_t)atoi(argv[1]);
    int listen_sock = Sock::Socket();
    Sock::Bind(listen_sock, port);
    Sock::Listen(listen_sock);

    //初始化数组
    for (int i = 0; i < NUM; i++)
    {
        fd_array[i] = -1;
    }

    // accept: 不应该，accept的本质叫做通过listen_sock获取新链接
    //         前提是listen_sock上面有新链接，accept怎么知道有新链接呢？？
    //         不知道！！！accept阻塞式等待
    //         站在多路转接的视角，我们认为，链接到来，对于listen_sock,就是读事件就绪！！！
    //         对于所有的服务器，最开始的时候，只有listen_sock

    //事件循环
    fd_set rfds;
    fd_array[0] = listen_sock;
    for (;;)
    {
        FD_ZERO(&rfds); //清空
        int max_fd = fd_array[0];
        for (int i = 0; i < NUM; ++i)
        {
            if (fd_array[i] == -1)
            {
                continue;
            }
            //下面都是合法的fd
            //所有要关心读事件的fd，添加到rfds中
            FD_SET(fd_array[i], &rfds);
            // 更新最大的max_fd
            if (max_fd < fd_array[i])
            {
                max_fd = fd_array[i];
            }
        }

        //时间5s之内阻塞等待，5s之后非阻塞
        struct timeval timeout = {0, 0};

        // 我们的服务器上的所有的fd(包括listen_sock),都要交给select进行检测！！
        // recv,read,write,send,accept : 只负责自己最核心的工作：真正的读写(listen_sock:accept)

        int n = select(max_fd + 1, &rfds, nullptr, nullptr, nullptr); //暂时以阻塞方式
        switch (n)
        {
        case -1:
            std::cerr << "select error" << std::endl;
            break;
        case 0:
            std::cout << "select timeout" << std::endl;
            break;
        default:
            std::cout << "有fd对应的事件就绪了!" << std::endl;
            for (int i = 0; i < NUM; ++i)
            {
                //进行检测
                if (fd_array[i] == -1)
                {
                    continue;
                }
                //下面的fd都是合法的fd,合法的fd不一定是就绪的fd
                if (FD_ISSET(fd_array[i], &rfds))
                {
                    std::cout << "sock: " << fd_array[i] << " 上面有了读事件，可以读取了" << std::endl;
                    //这里一定是读事件就绪了！！！！！
                    //就绪的fd在fd_array[]里面保存的了
                    // read、recv时，一定不会被阻塞
                    // 读事件就绪时，就一定可以用read/recv吗？不一定
                    if (fd_array[i] == listen_sock)
                    {
                        std::cout << "listen_sock: " << listen_sock << " 有了新的链接到来" << std::endl;
                        // accpet
                        int sock = Sock::Accept(listen_sock);
                        if (sock >= 0)
                        {
                            std::cout << "listen_sock: " << listen_sock << " 获取新的链接成功" << std::endl;
                            //获取链接成功,是否可以read/recv了吗？绝对不能，因为新链接到来，并不意味着有数据到来
                            //什么时候数据到来了？--- 不知道
                            // 可是，谁可以最清楚的知道那些fd，上面可以读取了？select！
                            // 无法直接将fd设置进select，但是，好在我们有fd_array[]!
                            int pos = 1;
                            for (; pos < NUM; pos++)
                            {
                                if (fd_array[pos] == -1)
                                    break;
                            }
                            // 1. 找到了一个位置没有被使用
                            if (pos < NUM)
                            {
                                std::cout << "新链接: " << sock << " 已经被添加到了数组[" << pos << "]的位置" << std::endl;
                                fd_array[pos] = sock;
                            }
                            else
                            {
                                // 2. 找完了所有的fd_array[],都没有找到没有被使用位置
                                // 说明服务器已经满载，没法处理新的请求了
                                std::cout << "服务器已经满载了，关闭新的链接" << std::endl;
                                close(sock);
                            }
                        }
                    }
                    else
                    {
                        // 普通的sock，读事件就绪啦！
                        // 可以进行读取啦，recv，read
                        // 可是，本次读取就一定能读完吗？读完，就一定没有所谓的数据包粘包问题吗？
                        // 但是，我们今天没法解决！我们今天没有场景！仅仅用来测试
                        std::cout << "sock: " << fd_array[i] << " 上面有普通读取" << std::endl;
                        char recv_buffer[1024] = {0};
                        ssize_t s = recv(fd_array[i], recv_buffer, sizeof(recv_buffer) - 1, 0);
                        if (s > 0)
                        {
                            recv_buffer[s] = '\0';
                            std::cout << "client[ " << fd_array[i] << "]# " << recv_buffer << std::endl;
                        }
                        else if (s == 0)
                        {
                            std::cout << "sock: " << fd_array[i] << "关闭了, client退出啦!" << std::endl;
                            //对端关闭了链接
                            close(fd_array[i]);
                            std::cout << "已经在数组下标fd_array[" << i << "]"
                                      << "中,去掉了sock: " << fd_array[i] << std::endl;
                            fd_array[i] = -1;
                        }
                        else
                        {
                            //读取失败
                            close(fd_array[i]);
                            std::cout << "已经在数组下标fd_array[" << i << "]"
                                      << "中,去掉了sock: " << fd_array[i] << std::endl;
                            fd_array[i] = -1;
                        }
                    }
                }
            }
            break;
        }
    }
    return 0;
}