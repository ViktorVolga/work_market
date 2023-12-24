#include "include/web_request.h"
#include "include/request_parser.h"
#include "include/intro.hpp"

int main(int argc, char * argv[])
{   
    ProgramOptions po(argc, argv);
    po.init();
    /*RequestHandler rh;
    request_t request = std::make_unique<ProfessionRequest>(specializations_t::cpp);        
    rh.add_request(request);
    request_t &my_req = rh.get_request();
    my_req->execute_request();  
    rh.get_num_pages_in_request(my_req);
    HHRequestParser req_parser = HHRequestParser(&rh);*/ 
    
    return 0;
}
