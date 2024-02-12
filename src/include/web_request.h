#pragma once

#include <curl/curl.h>
#include <memory>
#include <iostream>
#include <string>
#include <queue>
#include <nlohmann/json.hpp>

#include "logger.h"
#include "request_enums.h"

class Request{
    CURL *my_curl;
    std::string my_url {"https://api.hh.ru/vacancies"};
    std::string my_header {"User-Agent: api-test-agent"};    
    CURLcode response;
    uint8_t m_count_options = 0;
    struct curl_slist *list = nullptr;
    std::string my_response;
    std::unique_ptr<char> my_data;
    nlohmann::json my_json;    
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
    void set_url(std::string * url);
    void set_url(std::string && url); 
    std::string * get_url();
    void print_transaction_info();
    virtual void execute_request() = 0;
    virtual std::string get_from_api(const vacansy_parameters &parameter, const std::string &request) = 0;
    std::string * get_response();
    nlohmann::json & get_json();
    virtual request_type_t get_request_type() = 0;
    uint8_t get_num_options();
    void set_num_options(uint8_t count);
    void clean_up_curl();             
};

typedef std::unique_ptr<Request> request_t;

class ProfessionRequest : public Request
{
    specializations_t my_spec;
    const request_type_t my_req_type{request_type_t::HHProfRequest};
public:
    ProfessionRequest(specializations_t specialization);
    std::string get_from_api(const vacansy_parameters &parameter, const std::string &request);
    void execute_request() override;
    void set_specialization();
    request_type_t get_request_type();
};

class HHProfRequestPage : public Request
{
    specializations_t my_spec;
    const request_type_t my_req_type{request_type_t::HHProfRequestPage};
public:
    HHProfRequestPage(request_t & request, int page_num);
    void execute_request() override;
    ~HHProfRequestPage();
    request_type_t get_request_type();
    std::string get_from_api(const vacansy_parameters &parameter, const std::string &request);
};

class HHVacansyRequest : public Request
{
    const request_type_t my_req_type{request_type_t::HHVacansyRequest};
public:
    HHVacansyRequest(std::string * address);
    void execute_request() override;
    request_type_t get_request_type() override;
    std::string get_from_api(const vacansy_parameters &parameter, const std::string &request) override;
};