#pragma once

#include <memory>
#include "request_enums.h"
#include "web_request.h"

class RequestHandler;

class RequestParser
{
    RequestHandler * my_handler;
public:
    RequestParser(RequestHandler * rh);
    virtual void parse(request_t & req) = 0;
};

class HHRequestParser : public RequestParser
{
    bool first_page {false};
public:
    HHRequestParser(RequestHandler * rh) : RequestParser(rh){};
    void parse(request_t & req) override;
    bool is_first_page(request_t & req);
};

typedef std::unique_ptr<RequestParser> request_parser_t;

class RequestParserFabrica
{
public:
    request_parser_t get_request_parser(RequestHandler * rh, request_type_t req_type);
};