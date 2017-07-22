#include "HttpServer.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "EventLoop.h"
#include "logging/Logging.h"
#include "Util.h"

#include <iostream>
#include <map>
#include <string>
using namespace std;


void onRequest(const HttpRequest& req, HttpResponse* resp)
{
    string path=Util::ConstructPath(req.path());
    string extent=Util::GetExtent(path);
    string contentType="";
    Util::GetContentType(extent,contentType);
    string content=Util::GetContent(path);
    if(content.empty())
    {
        resp->setStatusCode(HttpResponse::CODE_404);
        resp->setStatusMessage("Not Found");
    }
    else
    {
        resp->setBody(content);
        resp->setStatusCode(HttpResponse::CODE_200);
        resp->setStatusMessage("OK");
        resp->setContentType(contentType);
    } 
}

int main(int argc, char* argv[])
{
    int numThreads = 0;
    if (argc > 1)
    {
    //benchmark = true;
        muduo::Logger::setLogLevel(muduo::Logger::WARN);
        numThreads = atoi(argv[1]);
    }
    muduo::net::EventLoop loop;
    HttpServer server(&loop, muduo::net::InetAddress(8000) );
    server.setHttpCallback(onRequest);
    server.setThreadNum(numThreads);
    server.start();
    loop.loop();
    return 0;
}
