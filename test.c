#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

// 基于fcntl,我们实现函数，将文件描述符设置为非阻塞
void SetNonBlock(int fd)
{
    int fl = fcntl(fd, F_GETFL);
    if(fl<0)
    {
        perror("fcntl");
        return;
    }

    fcntl(fd, F_SETFL, fl | O_NONBLOCK);
}

// 轮询方式读取标准输入
int main()
{
    SetNonBlock(0);
    while(1)
    {
        char buffer[10];
        //重点是read
        ssize_t s = read(0, buffer, sizeof(buffer)-1);
        if(s > 0)
        {
            buffer[s] = 0;
            write(1, buffer, strlen(buffer));
            printf("read success, s: %d, errno: %d\n", s, errno);
        }
        else{
            if(errno == EAGAIN || errno == EWOULDBLOCK) 
            {
                printf("数据没有准备好，再试试吧!\n");
                printf("read failed, s: %d, errno: %d\n", s, errno);
                
                sleep(1);
                continue;
            }
        }
    }

    return 0;
}