#pragma once

#include <memory> 

class RequestHandler;

class Request;

typedef std::unique_ptr<Request> request_ptr_t;

class RequestParser
{
    RequestHandler * my_handler;
public:
    RequestParser(RequestHandler * rh);
    virtual void parse(request_ptr_t & req) = 0;
};

class HHRequestParser : public RequestParser
{
public:
    HHRequestParser(RequestHandler * rh) : RequestParser(rh){};
    void parse(request_ptr_t & req) override;
};