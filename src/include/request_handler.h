#pragma once

#include "request_parser.h"

class RequestHandler
{
    request_t my_request;
    std::queue<request_t> my_req_queue;
    std::queue<request_t> my_vacansy_req_queue;
    request_parser_t my_request_parser;
    /*Request Parser Fabrica*/
    std::unique_ptr<RequestParserFabrica> my_rpf;
public:
    RequestHandler();    
    void add_request(request_t &req);
    request_t &get_request();
    void run();
    int get_num_pages_in_request(request_t & req);
    void print_mum_requests_in_queue();    
};