#pragma once

#include <curl/curl.h>
#include <memory>
#include <iostream>
#include <string>
#include "logger.h"

class Request{
    CURL *my_curl;
    std::string my_url {"https://api.hh.ru/vacancies"};
    std::string my_header {"User-Agent: api-test-agent"};
    std::string my_received_data{};
    CURLcode response;
    uint8_t m_count_options = 0;
    struct curl_slist *list = nullptr;
public:
    Request();
    ~Request();
    uint8_t init_my_curl();
    void set_options();
    size_t read_from_api(void *buffer, size_t size, size_t received, void* my_received_data);
    void take_answer();
    void print_answer();
    void add_options_in_request(std::string options);
    void test_logger();
};

 enum class vacansy_parameters{
    per_page,
    text,
    area,

 };

