#include "include/vacansy.h"
#include "vacansy.h"
#include "logger.h"

Salary::Salary(const int & from, const int & to)
{
    this->from = from;
    this->to = to;
}

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

void Vacansy::set_my_sity(std::string sity)
{
    web_logger()->info("Vacansy::set_my_sity = [{}]", sity);
    my_sity = sity;
}

void Vacansy::set_my_salary(int min_salary, int max_salary)
{    
    web_logger()->info("Vacansy::set_my_salary min = [{}], max = [{}]", min_salary, max_salary);   
    my_salary = std::make_unique<Salary>(min_salary, max_salary);
}

void Vacansy::set_my_expirience(std::string expirience)
{
    web_logger()->info("Vacansy::set_my_expirience = [{}]",expirience);
    if(expirience == "noExperience")
        my_expirience =  Expirience::no_expirince;
}

HHVacansy::HHVacansy(const json &vacansy_json)
{   
    int min_salary, max_salary;  
    set_my_id(stoi(vacansy_json["id"].template get<std::string>()));
    set_my_name(vacansy_json["name"].template get<std::string>());
    set_my_sity(vacansy_json["area"]["name"].template get<std::string>());
    try{
        min_salary = vacansy_json["salary"]["from"].template get<int>();
    }
    catch (const json::type_error& ex){
        min_salary = 0;
    }
    try{
        max_salary = vacansy_json["salary"]["to"].template get<int>();
    }
    catch (const json::type_error& ex){
        max_salary = 0;
    }
    set_my_salary(min_salary, max_salary);
    set_my_expirience(vacansy_json["experience"]["id"].template get<std::string>());
}

void HHVacansy::save()
{

}