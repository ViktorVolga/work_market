#include "web_request.h"

Request::Request()
{
    uint8_t temp = init_my_curl();
    if(temp)
        std::cout << "init_my_curl: eror" << std::endl;
    else
       std::cout << "curl init - ok" << std::endl;     
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
    // curl_easy_setopt(my_curl, CURLOPT_WRITEFUNCTION, read_from_api);
    curl_easy_setopt(my_curl, CURLOPT_HEADER, 1);
    list = curl_slist_append(list, my_header.c_str());
    curl_easy_setopt(my_curl, CURLOPT_HTTPHEADER, list);
    //curl_easy_setopt(my_curl, CURLOPT_HTTPGET, 1L);
    //curl_easy_setopt(my_curl, CURLOPT_WRITEDATA, stdout);
    std::cout << "[Request::set_options] - ok" << std::endl; 

}
void Request::take_answer()
{
    std::cout << "[Request::take_answer] - start" << std::endl;    
    response = curl_easy_perform(my_curl);
    if(response != CURLE_OK)
    {
        std::cout << "[Request::take_answer] can't take response" << std::endl;
        std::cout << curl_easy_strerror(response) << std::endl;
    }
    else
    {
        std::cout << "[Request::take_answer] - ok" << std::endl;
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
/*
size_t Request::read_from_api(void *buffer, size_t size, size_t received, void *my_received_data)
{
    my_received_data.append((char*)buffer, size *received);
    return size *received;
}
*/
