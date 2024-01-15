#include "include/request_parser.h"

RequestParser::RequestParser(RequestHandler * rh)
{
    my_handler = rh;
}

void HHRequestParser::parse(request_t & req){
    
    bool first_page = is_first_page(req);
    trim_answer(req);
    get_json(req);
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

std::string * HHRequestParser::get_string_from_request(request_t & req)
{
    if(req != nullptr)
        return req->get_response();    
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
