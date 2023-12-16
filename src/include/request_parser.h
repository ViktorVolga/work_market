#pragma once

#include <memory>
#include "request_enums.h"

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

typedef std::unique_ptr<RequestParser> request_parser_t;

class RequestParserFabrica
{
public:
    request_parser_t get_request_parser(RequestHandler * rh, request_type_t req_type);
};