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
    first_request();
    my_request_handler->run();
}
