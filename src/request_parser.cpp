#include "include/request_parser.h"

RequestParser::RequestParser(RequestHandler * rh)
{
    my_handler = rh;
}

void HHRequestParser::parse(request_t & req)
{

}

bool HHRequestParser::is_first_page(request_t & req)
{
    std::string answer;
    if(req != nullptr)
        answer = req->get_response();
    else
    {
        web_logger()->error("[is_first_page] request_t is null_ptr");
        return false;
    }
    auto pos = answer.find("\"page\":");
    auto end_pos = answer.find(",\"per_page\":");
    std::string sub_str;
    while(pos < end_pos)
    {
        sub_str.push_back(answer[pos++]);
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

