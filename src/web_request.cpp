#include "web_request.h"

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
    curl_easy_setopt(my_curl, CURLOPT_URL, my_url.c_str());    
    curl_easy_setopt(my_curl, CURLOPT_HEADER, 1);
    list = curl_slist_append(list, my_header.c_str());
    curl_easy_setopt(my_curl, CURLOPT_HTTPHEADER, list);
    web_logger()->info("set_options: ok");   
}

void Request::take_answer()
{        
    response = curl_easy_perform(my_curl);
    if(response != CURLE_OK)
    {
        web_logger()->error("take_answer: can't take response %s", curl_easy_strerror(response));        
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
void Request::add_options_in_request(std::string options)
{
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

/*
size_t Request::read_from_api(void *buffer, size_t size, size_t received, void *my_received_data)
{
    my_received_data.append((char*)buffer, size *received);
    return size *received;
}
*/
