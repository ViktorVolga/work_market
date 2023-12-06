#pragma once

#include <curl/curl.h>
#include <memory>
#include <iostream>
#include <string>
#include "logger.h"
#include <queue>

enum class vacansy_parameters{
    specialization,
    per_page,
    text,
    area,
};

typedef enum class Specializations{
    cpp,
    python,
} specializations_t;


class Request{
    CURL *my_curl;
    std::string my_url {"https://api.hh.ru/vacancies"};
    std::string my_header {"User-Agent: api-test-agent"};    
    CURLcode response;
    uint8_t m_count_options = 0;
    struct curl_slist *list = nullptr;
    std::string my_response;
    std::unique_ptr<char> my_data;    
public:    
    Request();
    virtual ~Request();
    uint8_t init_my_curl();
    void set_options();
    size_t read_from_api(void *ptr, size_t size, size_t nmemb, void* userdata);
    void take_answer();
    void print_answer();    
    void add_options_in_request(const std::string &options);
    void test_logger();
    void add_standart_option(const vacansy_parameters &parameter, const std::string &option);
    void set_url(); 
    void print_transaction_info();
    virtual void execute_request() = 0;
    virtual std::string get_from_api(const vacansy_parameters &parameter, const std::string &request) = 0;
    std::string &get_response();             
};

typedef std::unique_ptr<Request> request_t;

class ProfessionRequest : public Request
{
    specializations_t my_spec;
public:
    ProfessionRequest(specializations_t specialization);
    std::string get_from_api(const vacansy_parameters &parameter, const std::string &request);
    void execute_request() override;
    void set_specialization();
};

class RequestHandler
{
    request_t my_request;
    std::queue<request_t> my_req_queue;
public:
    void add_request(request_t &req);
    request_t &get_request();
    void run();    
};

 

