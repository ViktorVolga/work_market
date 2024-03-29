#include "include/request_parser.h"
#include "request_parser.h"
#include "request_handler.h"

RequestParser::RequestParser(RequestHandler * rh)
{
    my_handler = rh;
}

void HHRequestParser::parse(request_t & req){
    
    bool first_page = is_first_page(req);
    trim_answer(req);
    get_json(req);     
    if(first_page)
    {        
        int num_pages = get_my_request_handler()->get_num_pages_in_request(req);
        fill_requests_list(num_pages, req);
    }
    for (auto & item : my_json["items"])
    {
        std::string vacansy_url = item["alternate_url"].template get<std::string>();
        request_t vacansy_request = std::make_unique<HHVacansyRequest>(&vacansy_url);
    }    
}

bool HHRequestParser::is_first_page(request_t & req)
{
    std::string * answer;
    if(req != nullptr)
        answer = req->get_response();
    else
    {
        web_logger()->error("[is_first_page] request_t is null_ptr");
        return false;
    }
    auto pos = answer->find("\"page\":");
    auto end_pos = answer->find(",\"per_page\":");
    std::string sub_str;
    pos += 7;
    while(pos < end_pos)
    {
        sub_str.push_back(answer->at(pos++));
    }   
    int page = stoi(sub_str);
    if(page == 0)
        return true;
    else
        return false;    
}

std::string * HHRequestParser::get_string_from_request(request_t & req)
{
    if(req != nullptr)
        return req->get_response();    
    return nullptr;
}

void HHRequestParser::trim_answer(request_t & req)
{
    std::string * answer = get_string_from_request(req);
    if(answer->empty())
    {
        web_logger()->error("HHRequestParser::trim_answer - answer is empty");
        return;        
    }    
    auto start_json = std::next(answer->begin(), answer->find("{\"items\""));
    answer->erase(answer->begin(), start_json);
}

void HHRequestParser::get_json(request_t & req)
{
    using namespace nlohmann::literals;
    std::string * answer = get_string_from_request(req);
    my_json = json::parse(*answer);
    std::cout << my_json;
}

void HHRequestParser::fill_requests_list(int num_pages, request_t &req)
{
    for (int i = 1; i < num_pages; i++)
    {
        std::unique_ptr<Request> next_req = std::make_unique<HHProfRequestPage>(req, i);
        get_my_request_handler()->add_request(next_req);
    }
    get_my_request_handler()->print_mum_requests_in_queue();
}

RequestHandler * RequestParser::get_my_request_handler()
{
    return my_handler;
}

request_parser_t RequestParserFabrica::get_request_parser(RequestHandler * rh, request_type_t req_type)
{
    switch(req_type)
    {
        case request_type_t::HHProfRequest :
            return std::make_unique<HHRequestParser>(rh);
            
        default:
            return nullptr;
    }
    return nullptr;
}
