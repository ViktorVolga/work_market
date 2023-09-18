#pragma once

#include <curl/curl.h>
#include <memory>
#include <iostream>
#include <string>
#include "logger.h"

enum class vacansy_parameters{
    specialization,
    per_page,
    text,
    area,
 };

class Request{
    CURL *my_curl;
    std::string my_url {"https://api.hh.ru/vacancies"};
    std::string my_header {"User-Agent: api-test-agent"};    
    CURLcode response;
    uint8_t m_count_options = 0;
    struct curl_slist *list = nullptr;    
public:    
    Request();
    virtual ~Request();
    uint8_t init_my_curl();
    void set_options();
    size_t read_from_api(void *buffer, size_t size, size_t received, void* my_received_data);
    void take_answer();
    void print_answer();    
    void add_options_in_request(const std::string &options);
    void test_logger();
    void add_standart_option(const vacansy_parameters &parameter, const std::string &option);
    void set_url(); 
    void print_transaction_info();
    virtual std::string get_from_api(const vacansy_parameters &parameter, const std::string &request) = 0;         
};

class ProfessionRequest : public Request
{
public:
    std::string get_from_api(const vacansy_parameters &parameter, const std::string &request);
};

 

