#pragma once 

#include "web_request.h"
#include "json.h"
#include <memory>
#include <queue>
#include "request_parser.h"
#include "request_handler.h"
#include "vacansy_handler.h"
#include <chrono>
#include <thread>

class App
{    
    RequestHandlerPtr_t my_request_handler;
    VacansyHandlerPtr_t my_vacansy_handler;
public:
    App();
    void first_request();
    void run();    
};