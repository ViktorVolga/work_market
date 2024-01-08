#include "request_handler.h"
#include "include/intro.hpp"

int main(int argc, char * argv[])
{   
    ProgramOptions po(argc, argv);
    po.init();
    RequestHandler rh;
    request_t request = std::make_unique<ProfessionRequest>(specializations_t::cpp);        
    rh.add_request(request);
    request_t &my_req = rh.get_request();
    my_req->execute_request();  
    rh.get_num_pages_in_request(my_req);
    HHRequestParser req_parser = HHRequestParser(&rh); 
    req_parser.trim_answer(my_req);
    std::string * answer = req_parser.get_string_from_request(my_req);
    std::cout << *answer << std::endl;
    std::cout << std::endl << std::endl;
    req_parser.get_json(my_req);

    return 0;
}
