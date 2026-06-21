#pragma once 

#include "web_request.h"
#include "json.h"
#include <memory>
#include <queue>
#include "request_parser.h"
#include "request_handler.h"
#include "vacansy_handler.h"
#include "vacansy_saver.h"
#include <chrono>
#include <thread>
#include "logger.h"
#include "skill_statistic.h"
#include "sql_io.h"

class App
{    
    RequestHandlerPtr_t my_request_handler;
    VacansyHandlerPtr_t my_vacansy_handler;
    std::unique_ptr<SQL_IO> m_sql_connect;    
public:
    App();
    void first_request();
    void run();    
};