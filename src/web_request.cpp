#include "web_request.h"

static std::string answer;

static size_t write_answer(void *data, size_t size, size_t nmemb, char *userdata)
{
    size_t str_length = nmemb * size;
    try
    {
       answer.append((char*)data, str_length); 
    }
    catch(const std::bad_alloc& e)
    {
        web_logger()->error("can't alloc memory [{}]", e.what());
        return 0;        
    }    
    return str_length;
}

Request::Request()
{
    uint8_t temp = init_my_curl();
    if(temp)
        web_logger()->error("init_my_curl: eror");
    else
       web_logger()->info("init_my_curl: ok");     
}

Request::~Request()
{
    curl_slist_free_all(list);
    curl_easy_cleanup(my_curl);    
}

uint8_t Request::init_my_curl()
{
    curl_global_init(CURL_GLOBAL_ALL);
    my_curl = curl_easy_init();
    if(my_curl != nullptr)
        return 0;
    return 1; /*error*/    
}

void Request::set_options()
{       
    curl_easy_setopt(my_curl, CURLOPT_HEADER, 1);
    list = curl_slist_append(list, my_header.c_str());
    curl_easy_setopt(my_curl, CURLOPT_HTTPHEADER, list);
    web_logger()->info("set_options: ok");
    curl_easy_setopt(my_curl, CURLOPT_WRITEFUNCTION, write_answer);   
}

void Request::take_answer()
{        
    response = curl_easy_perform(my_curl);
    if(response != CURLE_OK)
    {
        web_logger()->error("take_answer: can't take response. error [{}]", curl_easy_strerror(response));        
    }
    else
    {
        web_logger()->info("take_answer - ok");        
    }
           
}
void Request::print_answer()
{
    std::cout << response << std::endl;
}

void Request::add_options_in_request(const std::string &options)
{
    std::string to_apend{};
    if(m_count_options)
    {
        my_url.push_back('&');
        my_url.append(options);
        m_count_options++;
    }
    else
    {
        my_url.push_back('?');
        my_url.append(options);
        m_count_options++;
    }    
    std::cout << my_url << std:: endl;
}

void Request::test_logger()
{
    web_logger()->info("gavno");
}

void Request::add_standart_option(const vacansy_parameters &parameter, const std::string &option)
{
    switch (parameter)
    {
        case vacansy_parameters::specialization :
            std::string to_request {"text="};
            to_request.append(option);
            add_options_in_request(to_request);
            break;
    }
}

void Request::set_url()
{
    curl_easy_setopt(my_curl, CURLOPT_URL, my_url.c_str()); 
}  

void Request::print_transaction_info()
{
    char * info;
    CURLcode res = curl_easy_getinfo(my_curl, CURLINFO_EFFECTIVE_URL, &info);
    web_logger()->info("last url [{}]", info);
}

std::string ProfessionRequest::get_from_api(const vacansy_parameters &parameter, const std::string &request)
{
    set_options();
    add_standart_option(parameter, request);    
    take_answer();
    return answer;    
}

/*
size_t Request::read_from_api(void *buffer, size_t size, size_t received, void *my_received_data)
{
    my_received_data.append((char*)buffer, size *received);
    return size *received;
}
*/
