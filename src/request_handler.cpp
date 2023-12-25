#include "include/request_handler.h"

void RequestHandler::add_request(request_t &req)
{
    if(req != nullptr)
    {
        my_req_queue.push(std::move(req));
        web_logger()->info("added request in queue");
    }
    else
    {
        web_logger()->error("request - nullptr");
    }    
}

request_t &RequestHandler::get_request()
{
    if(my_req_queue.empty())
    {
        my_request = nullptr;
        return my_request;
    }        
    else
    {
        my_request = std::move(my_req_queue.front());
        my_req_queue.pop();
        return my_request;
    }
}

void RequestHandler::run()
{
    request_t request = std::make_unique<ProfessionRequest>(specializations_t::cpp);        
    add_request(request);
    while(!my_req_queue.empty())
    {
        my_request = std::move(my_req_queue.front());
        my_request->execute_request();
        
    }
}

int RequestHandler::get_num_pages_in_request(request_t &req)
{
    std::string response = req->get_response();

    /*find num pages in request*/
    auto pos = response.find("pages");
    if(pos == std::string::npos)
    {
        web_logger()->debug("request not consider num pages");
        return -1;
    }
    else
    {
        pos += 7;
        std::string sub_string{};
        while(response.at(pos) != ',')
        {
            sub_string.push_back(response.at(pos));
            pos++;
        }
        int num_pages = stoul(sub_string);
         web_logger()->debug("num_pages  in request {}", num_pages);
        return num_pages;
    }    
}