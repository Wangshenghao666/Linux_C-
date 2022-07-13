#pragma once 
#include<iostream>
#include<string>
#include <jsoncpp/json/json.h>

using namespace std;
// 定制协议的过程，目前就是定制结构化数据的过程
// 我们自己定义的协议，client && server 都必须遵守! 这就叫自定义协议

//请求格式：
typedef struct request
{
    int x;
    int y;
    char op;
}request_t;

//响应格式：
typedef struct response
{
    int code;
    // server运算完毕的计算状态: code(0:success), code(-1: div 0) ...
    int result;
    // 计算结果， 能否区分是正常的计算结果，还是异常的退出结果
}response_t;




//request_t -> string
string SerializeRequest(const request_t &req)
{
    // 序列化的过程
    Json::Value root; //可以承装任何对象， json是一种kv式的序列化方案
    root["datax"] = req.x;
    root["datay"] = req.y;
    root["operator"] = req.op;

    //FastWriter, StyledWriter
    // Json::StyledWriter writer;
    Json::FastWriter writer;
    string json_string = writer.write(root);
    return json_string;
}

// string -> request_t
void DeserializeRequest(const string &json_string, request_t &out)
{
    //反序列化
    Json::Reader reader;
    Json::Value root;

    reader.parse(json_string, root);
    out.x = root["datax"].asInt();
    out.y = root["datay"].asInt();
    out.op = (char)root["operator"].asInt();
}

string SerializeResponse(const response_t &resp)
{
    Json::Value root;
    root["code"] = resp.code;
    root["result"] = resp.result;

    Json::FastWriter writer;
    string res = writer.write(root);

    return res;
}

void DeserializeResponse(const string &json_string, response_t &out)
{
        //反序列化
    Json::Reader reader;
    Json::Value root;

    reader.parse(json_string, root);
    out.code = root["code"].asInt();
    out.result = root["result"].asInt();
}