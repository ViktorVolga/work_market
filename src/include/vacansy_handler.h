#pragma once

#include "vacansy.h"
#include <queue>

typedef std::unique_ptr<Vacansy> vacansy_ptr_t;



class VacansyHandler
{
    vacansy_ptr_t my_vacancy;
    std::queue<vacansy_ptr_t> my_vacansy_queue;
public:
    VacansyHandler();   
    void add_vacansy_to_queue(vacansy_ptr_t vacansy);
};

typedef std::shared_ptr<VacansyHandler> VacansyHandlerPtr_t;