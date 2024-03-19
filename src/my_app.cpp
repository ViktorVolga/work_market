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
    skill_ptr_t skill = get_skills();
    skill->read_my_dictionaries();
    std::shared_ptr<VacansySaver> vs = get_vacansy_saver_ptr();
    first_request();
    int count = 10;
    while(count){
        if(my_vacansy_handler->is_empty()){
            my_request_handler->handle_one_request();
            std::this_thread::sleep_for(1s);
            count--;
        } else { 
            my_vacansy_handler->handle_one_vacansy();
            std::this_thread::sleep_for(1s);
            count--;
        }
    }    
    skill->write_to_file();    
}
