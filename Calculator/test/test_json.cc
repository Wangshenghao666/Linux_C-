#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>

typedef struct request
{
    int x;  //10
    int y;  //0
    char op; // '/'      "+-*/%"
} request_t; //10/0


int main()
{
   

    //序列化的过程
    request_t req = {10, 20, '*'};
    Json::Value root; //可以承装任何对象， json是一种kv式的序列化方案
    root["datax"] = req.x;
    root["datay"] = req.y;
    root["operator"] = req.op;

    //FastWriter, StyledWriter
    Json::StyledWriter writer;
    //Json::FastWriter writer;
    std::string json_string = writer.write(root);

    std::cout << json_string << std::endl;




     // //反序列化
    // std::string json_string = R"({"datax":10,"datay":20,"operator":42})";
    // Json::Reader reader;
    // Json::Value root;

    // reader.parse(json_string, root);

    // request_t req;
    // req.x = root["datax"].asInt();
    // req.y = root["datay"].asInt();
    // req.op = (char)root["operator"].asInt();

    // std::cout << req.x << " " << req.op << " " << req.y << std::endl;

    return 0;
}