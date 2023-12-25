#pragma once

#include "request_parser.h"

class RequestHandler
{
    request_t my_request;
    std::queue<request_t> my_req_queue;
    request_parser_t my_request_parser;
public:    
    void add_request(request_t &req);
    request_t &get_request();
    void run();
    int get_num_pages_in_request(request_t & req);    
};