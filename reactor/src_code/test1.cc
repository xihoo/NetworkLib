#include "HttpServer.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "EventLoop.h"
#include "logging/Logging.h"
//#include "Util.h"

#include <iostream>
#include <map>
#include <string>
using namespace std;


void onRequest(const xihoo::HttpRequest& req, HttpResponse* resp)
{
    string path="/root/index.html";
    //string extent=Util::GetExtent(path);
    string contentType="html";
    //Util::GetContentType(extent,contentType);
    string content="<html><head><title>Welcome to nginx!</title></head><body bgcolor='white' text='black'><center><h1>xihoo Welcome to nginx!</h1></center></body></html>";
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
        xihoo::Logger::setLogLevel(xihoo::Logger::WARN);
        numThreads = atoi(argv[1]);
    }
    xihoo::EventLoop loop;
    xihoo::HttpServer server(&loop, xihoo::InetAddress(8000) );
    server.setHttpCallback(onRequest);
    server.setThreadNum(numThreads);
    server.start();
    loop.loop();
    return 0;
}
