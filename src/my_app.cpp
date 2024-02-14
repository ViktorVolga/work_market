#include "my_app.h"

App::App()
{
    my_vacansy_handler = std::make_shared<VacansyHandler>();
    my_request_handler = std::make_shared<RequestHandler>(my_vacansy_handler);    
}

void App::first_request()
{
    request_t request = std::make_unique<ProfessionRequest>(specializations_t::cpp);
    my_request_handler->add_request(request);
}

void App::run()
{
    using namespace std::chrono_literals;
    first_request();
    int count = 2;
    while(count){
        if(my_vacansy_handler->is_empty()){
            my_request_handler->handle_one_request();
            std::this_thread::sleep_for(1s);
            count--;
        } else { 
            count--;
        }
    }
    
}
