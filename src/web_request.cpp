#include "include/web_request.h"
#include "web_request.h"

static std::string answer;
static int ptr_count;


static size_t write_answer(void *data, size_t size, size_t nmemb, char *userdata)
{
    size_t str_length = nmemb * size;
    memmove(userdata + ptr_count, data, str_length);
    ptr_count += str_length;
    /*try
    {
       answer.append((char*)data, str_length); 
    }
    catch(const std::bad_alloc& e)
    {
        web_logger()->error("can't alloc memory [{}]", e.what());
        return 0;        
    }*/    
    return str_length;
}

Request::Request()
{
        
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
    else
        return 1; /*error*/    
}

void Request::set_options()
{       
    curl_easy_setopt(my_curl, CURLOPT_HEADER, 1);
    list = curl_slist_append(list, my_header.c_str());
    curl_easy_setopt(my_curl, CURLOPT_HTTPHEADER, list);    
    //curl_easy_setopt(my_curl, CURLOPT_WRITEFUNCTION, write_answer);
    web_logger()->info("set_options: ok");   
}

void Request::take_answer()
{   
    /*todo later reserve can throw exception*/
    my_response.resize(116000);
    //my_data = std::make_unique<char>(CURL_MAX_WRITE_SIZE);
    ptr_count = 0;           
    curl_easy_setopt(my_curl, CURLOPT_WRITEFUNCTION, write_answer);
    curl_easy_setopt(my_curl, CURLOPT_WRITEDATA, (void*)my_response.data());      
    response = curl_easy_perform(my_curl);
    if(response != CURLE_OK)
    {
        web_logger()->error("take_answer: can't take response. error [{}]", curl_easy_strerror(response));        
    }
    else
    {
        web_logger()->info("take_answer - ok");        
    }    
    web_logger()->info("readed {} byte from API", ptr_count);
    my_response.resize(ptr_count);                   
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
    web_logger()->info("test");
}

void Request::add_standart_option(const vacansy_parameters &parameter, const std::string &option)
{
    switch (parameter)
    {
        case (vacansy_parameters::specialization) :
        {
            std::string to_request {"text="};
            to_request.append(option);
            add_options_in_request(to_request);
            break;
        }
            
        default :
            break;
    }
}

void Request::set_url()
{
    curl_easy_setopt(my_curl, CURLOPT_URL, my_url.c_str()); 
}  

void Request::print_transaction_info()
{    
    char *info;
    curl_easy_getinfo(my_curl, CURLINFO_EFFECTIVE_URL, &info);
    web_logger()->info("last url [{}]", info);
}

/*
    return answer  in std::string &
*/
std::string &Request::get_response()
{
    return my_response;
}

nlohmann::json & Request::get_json()
{
    return my_json;
}

std::string ProfessionRequest::get_from_api(const vacansy_parameters &parameter, const std::string &request)
{
    set_options();
    add_standart_option(parameter, request);    
    take_answer();
    print_answer();
    return answer;    
}


size_t Request::read_from_api(void *ptr, size_t size, size_t nmemb, void* userdata)
{
    ssize_t realsize = size * nmemb;
    web_logger()->info("{}", realsize); 
    try
    {
       my_response.append((char*)ptr, realsize); 
    }
    catch(const std::bad_alloc& e)
    {
        web_logger()->error("can't alloc memory [{}]", e.what());
        return 0;        
    } 
    return size * nmemb;
}

ProfessionRequest::ProfessionRequest(specializations_t specialization)
{
    auto ret = init_my_curl();    
    if (ret)
    {
        web_logger()->error("filed to init_my_curl");
    }
    my_spec = std::move(specialization);
    set_options();  
    set_specialization();
    set_url();            
}

void ProfessionRequest::execute_request()
{
    take_answer();
    std:: cout << get_response() << std::endl;    
}

/*  add specialization in request
*   specialization set in object
*/

void ProfessionRequest::set_specialization()
{
    /*to do later 
        change switch on std::map for more faster search
    */
    switch (my_spec) 
    {
        case specializations_t::cpp :
        {
            add_standart_option(vacansy_parameters::specialization, "с%2B%2B");
            web_logger()->info("set cpp in request");
            break;
        }
        default :
        {
            web_logger()->error("wrong specialization in request");
        }

    }
}

request_type_t ProfessionRequest::get_request_type()
{
    return my_req_type;
}