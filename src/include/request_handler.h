#pragma once

#include "request_parser.h"
#include "vacansy_handler.h"
#include "logger.h"
#include "vacansy_saver.h"

//class VacansyHandler;

//typedef std::shared_ptr<VacansyHandler> VacansyHandlerPtr_t;

class RequestHandler
{
    request_t my_request;
    std::queue<request_t> my_req_queue;
    std::queue<request_t> my_vacansy_req_queue;
    request_parser_t my_request_parser;
    /*Request Parser Fabrica*/
    std::unique_ptr<RequestParserFabrica> my_rpf;
    VacansyHandlerPtr_t my_vacansy_handler_ptr;
    int requests_handled {0};
    int vacansy_handled {0};
    
public:
    RequestHandler(VacansyHandlerPtr_t vh);    
    void add_request(request_t &req);   
    request_t &get_request();
    void run();
    int get_num_pages_in_request(request_t & req);
    void print_mum_requests_in_queue();
    void add_vacansy(vacansy_ptr_t vacansy);
    void add_vacansy_request(request_t request);
    int handle_one_request();
    void set_first_request();  
    bool is_empty();
    bool is_vacansy_requests_empty();
    void add_to_to_handled();
};