#pragma once

#include <memory>
#include <string>
#include "request_enums.h"
#include "web_request.h"
#include <nlohmann/json.hpp>

#include <boost/lexical_cast.hpp>

using json = nlohmann::json;

class RequestHandler;

typedef std::shared_ptr<RequestHandler> RequestHandlerPtr_t;

class RequestParser
{
    RequestHandler *  my_handler;
    json my_json;
public:
    RequestParser(RequestHandler * rh);
    virtual void parse(request_t & req) = 0;
    RequestHandler * get_my_request_handler();
    std::string * get_string_from_request(request_t & req);
    void get_json(request_t & req);
    json & get_my_json();
};

class HHRequestParser : public RequestParser
{
    bool first_page {false};      
public:
    HHRequestParser(RequestHandler * rh) : RequestParser(rh){};
    void parse(request_t & req) override;
    bool is_first_page(request_t & req);    
    void trim_answer(request_t & req);    
    void fill_requests_list(int num_pages, request_t & req);    
};

class HHVacansyRequestParser : public RequestParser
{
public:
    HHVacansyRequestParser(RequestHandler * rh) : RequestParser(rh){};
    void parse(request_t & req) override;
    void trim_answer(request_t & req);
};

typedef std::unique_ptr<RequestParser> request_parser_t;

class RequestParserFabrica
{
public:
    request_parser_t get_request_parser(RequestHandler * rh, request_type_t req_type);
};