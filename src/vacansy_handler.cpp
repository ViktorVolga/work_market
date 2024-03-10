#include "vacansy_handler.h"

VacansyHandler::VacansyHandler()
{

}

void VacansyHandler::add_vacansy_to_queue(vacansy_ptr_t vacansy)
{
    if(vacansy){
        web_logger()->info("[VacansyHandler::add_vacansy_to_queue] - added new vacansy to vacansy queue");
        my_vacansy_queue.push(std::move(vacansy));
    } else { 
        web_logger()->error("[VacansyHandler::add_vacansy_to_queue] - can't add nullptr in queue");
    }    
}

bool VacansyHandler::is_empty()
{
    if(my_vacansy_queue.empty())
        return true;
    else
        return false;
}

/*take one vacansy from queue - parse skills and save to the database*/
void VacansyHandler::handle_one_vacansy()
{
    web_logger()->info("[VacansyHandler::handle_one_vacansy] - start");
    if(my_vacansy_queue.empty()){
        web_logger()->info("[VacansyHandler::handle_one_vacansy] - vacansy_queu is empty - nothing to do");
        return;
    } else { 
        web_logger()->info("[VacansyHandler::handle_one_vacansy] - take one vacansy from queue");
        my_vacancy = std::move(my_vacansy_queue.front());
        my_vacansy_queue.pop();

        /*get skill parser*/
        SkillParserFabrica spf = SkillParserFabrica();
        skill_parser_t parser = spf.get_skill_parser();

        /*here we find skills in description of vacansy*/
        parser->parse(my_vacancy.get());

    }
    web_logger()->info("[VacansyHandler::handle_one_vacansy] - vacansy handled");
}
