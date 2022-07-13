#include <pthread.h>
#include "Protocol.hpp"
#include "Sock.hpp"

static void Usage(string proc)
{
    cout << " Usage : " << proc << " port " << endl;
}

// void *HandlerRequest(void *args)
// {
//     int sock = *(int *)args;
//     delete (int *)args;

//     pthread_detach(pthread_self()); //分离




//     // version1 原生方法，没有明显的序列化和反序列化的过程
//     //业务逻辑
//     // ...
//     // 业务逻辑, 做一个短服务
//     // request -> 分析处理 -> 构建response -> sent(response)->close(sock)
//     // 1. 读取请求
//     request_t req;
//     ssize_t s = read(sock, &req, sizeof(req));
//     if (s == sizeof(req))
//     {
//         // 读取到了完整的请求，待定
//         // req.x , req.y, req.op
//         // 2. 分析请求 && 3. 计算结果
//         // 4. 构建响应，并进行返回
//         response_t resp = {0, 0};
//         switch (req.op)
//         {
//         case '+':
//             resp.result = req.x + req.y;
//             break;
//         case '-':
//             resp.result = req.x - req.y;
//             break;
//         case '*':
//             resp.result = req.x * req.y;
//             break;
//         case '/':
//             if (req.y == 0)
//                 resp.code = -1; //代表除0
//             else
//                 resp.result = req.x / req.y;
//             break;
//         case '%':
//             if (req.y == 0)
//                 resp.code = -2; //代表模0
//             else
//                 resp.result = req.x % req.y;
//             break;
//         default:
//             resp.code = -3; //代表请求方法异常
//             break;
//         }
//         cout << " request : " << req.x << req.op << req.y << endl;
//         write(sock, &resp, sizeof(resp));
//         cout << "服务结束" << endl;
//     }

//     // 5. 关闭链接
//     close(sock);
// }





void *HandlerRequest(void *args)
{
    int sock = *(int *)args;
    delete (int *)args;

    pthread_detach(pthread_self()); //分离




    //使用序列化与反序列化过程
    char buffer[1024];
    request_t req;
    ssize_t s = read(sock, buffer, sizeof(buffer) - 1);
    if (s > 0)
    {
        buffer[s] = 0;
        cout << "get a new request: " << buffer << endl;
        string str = buffer;
        DeserializeRequest(str, req); //反序列化请求
        response_t resp = {0, 0};
        switch (req.op)
        {
        case '+':
            resp.result = req.x + req.y;
            break;
        case '-':
            resp.result = req.x - req.y;
            break;
        case '*':
            resp.result = req.x * req.y;
            break;
        case '/':
            if (req.y == 0)
                resp.code = -1; //代表除0
            else
                resp.result = req.x / req.y;
            break;
        case '%':
            if (req.y == 0)
                resp.code = -2; //代表模0
            else
                resp.result = req.x % req.y;
            break;
        default:
            resp.code = -3; //代表请求方法异常
            break;
        }
        cout << "request: " << req.x << req.op << req.y << endl;
        string send_string = SerializeResponse(resp);   //序列化之后的字符串
        write(sock, send_string.c_str(),send_string.size());     
        cout << "服务结束: " << send_string << endl;
    }

    // 5. 关闭链接
    close(sock);
}




int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        Usage(argv[0]);
    }
    uint16_t port = atoi(argv[1]);

    int listen_sock = Sock::Socket();
    Sock::Bind(listen_sock, port);
    Sock::Listen(listen_sock);

    for (;;)
    {
        int sock = Sock::Accept(listen_sock);
        if (sock >= 0)
        {
            cout << " get a new client ... " << endl;

            int *pram = new int(sock);
            pthread_t tid;
            pthread_create(&tid, nullptr, HandlerRequest, pram);
        }
    }
    return 0;
}