#include "vacansy_handler.h"

VacansyHandler::VacansyHandler()
{

}

void VacansyHandler::add_vacansy_to_queue(vacansy_ptr_t vacansy)
{
    my_vacansy_queue.push(std::move(vacansy));
}
