#include "include/vacansy.h"
#include "vacansy.h"
#include "logger.h"

Vacansy::Vacansy()
{

}

void Vacansy::set_my_id(int id)
{
    web_logger()->info("Vacansy::set_my_id my_id =  [{}]", id);
    my_id = id;
}

int Vacansy::get_my_id()
{    
    return my_id;
}

void Vacansy::set_my_name(std::string name)
{
    web_logger()->info("Vacansy::set_my_name =  [{}]", name);
    my_name = std::move(name);
}

const std::string & Vacansy::get_my_name()
{
    return my_name;
}

void Vacansy::set_my_country(std::string &country)
{
    my_country = std::move(country);
}

const std::string & Vacansy::get_my_country()
{
    return my_country;
}

HHVacansy::HHVacansy(const json &vacansy_json)
{    
    set_my_id(stoi(vacansy_json["id"].template get<std::string>()));
    set_my_name(vacansy_json["name"].template get<std::string>());

}

void HHVacansy::save()
{

}