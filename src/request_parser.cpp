#include "include/request_parser.h"

RequestParser::RequestParser(RequestHandler * rh)
{
    my_handler = rh;
}

void HHRequestParser::parse(request_ptr_t & req)
{
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

