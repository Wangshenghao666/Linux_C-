#include "Protocol.hpp"
#include "Sock.hpp"

void Usage(string proc)
{
    cout << "Usage: " << proc << " server_ip server_port" << endl;
}
// // ./CalClient server_ip server_port
// int main(int argc, char *argv[])
// {
//     if (argc != 3)
//     {
//         Usage(argv[0]);
//         exit(1);
//     }
//     int sock = Sock::Socket();
//     Sock::Connect(sock, argv[1], atoi(argv[2]));

//     // 业务逻辑
//     request_t req;
//     memset(&req, 0, sizeof(req));
//     cout << "Please Enter Data One# ";
//     cin >> req.x;
//     cout << "Please Enter Data Two# ";
//     cin >> req.y;
//     cout << "Please Enter operator# ";
//     cin >> req.op;

//     ssize_t s = write(sock, &req, sizeof(req));

//     response_t resp;
//     s = read(sock, &resp, sizeof(resp));
//     if (s == sizeof(resp))
//     {
//         cout << "code[0:success]: " << resp.code << endl;
//         cout << "result: " << resp.result << std::endl;
//     }
//     return 0;
// }





//使用序列化与反序列化
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        Usage(argv[0]);
        exit(1);
    }
    int sock = Sock::Socket();
    Sock::Connect(sock, argv[1], atoi(argv[2]));

   
    request_t req;
    memset(&req, 0, sizeof(req));
    cout << "Please Enter Data One# ";
    cin >> req.x;
    cout << "Please Enter Data Two# ";
    cin >> req.y;
    cout << "Please Enter operator# ";
    cin >> req.op;

    string json_string = SerializeRequest(req);

    ssize_t s = write(sock, json_string.c_str(), json_string.size());

    char buffer[1024];
    s = read(sock, buffer, sizeof(buffer) - 1);
    if (s > 0)
    {
        response_t resp;
        buffer[s] = 0;
        string str = buffer;
        DeserializeResponse(str, resp);

        cout << "code[0:success]: " << resp.code << endl;
        cout << "result: " << resp.result << endl;
    }
    return 0;
}

