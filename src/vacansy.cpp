#include "include/vacansy.h"
#include "vacansy.h"
#include "logger.h"

Salary::Salary(const int & from, const int & to)
{
    this->from = from;
    this->to = to;
}

std::string Salary::get_from()
{
    return boost::lexical_cast<std::string>(from);
}

std::string Salary::get_to()
{
    return boost::lexical_cast<std::string>(to);
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

void Vacansy::set_my_description(std::string description)
{
   web_logger()->info("Vacansy::set_my_description = [{}]", description);
   my_description = description;
}

std::string &Vacansy::get_my_descripton()
{
    return my_description;
}

void Vacansy::set_my_schedule(std::string shedule)
{
    web_logger()->info("Vacansy::set_my_schedule = [{}]", shedule);
    my_shedule = shedule;
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
    set_my_schedule(vacansy_json["schedule"]["id"].template get<std::string>());
    set_my_description(vacansy_json["description"].template get<std::string>());
    get_skils_from_json(vacansy_json);
}

void Vacansy::get_skils_from_json(const json & vacansy_json)
{
    web_logger()->info("Vacansy::get_skils_from_json start");
    for (auto & skill : vacansy_json["key_skills"])
    {
        web_logger()->info("Vacansy::get_skils_from_json candidate [{}]", skill["name"]);
        my_candidats_to_skills.push(skill["name"]);
    }
}

void Vacansy::clear_one_description(std::string & to_delete)
{
    web_logger()->info("[Vacansy::clear_description] start");
    
    auto it = my_description.find(to_delete);
    while(it != -1)
    {
        my_description.erase(it, 3);
        it = my_description.find(to_delete);
    }
    web_logger()->info("[Vacansy::clear_description] end");
}

std::ostream & operator<<(std::ostream &stream, const Vacansy &vacansy)
{    
    stream << "id: " << boost::lexical_cast<std::string>(vacansy.my_id) << std::endl;
    stream << "name: " << vacansy.my_name << std::endl;
    stream << "country: " << vacansy.my_country << std::endl;
    stream << "sity: " << vacansy.my_sity << std::endl;
    stream << "company: " << vacansy.my_company << std::endl;
    stream << "salary: " <<  std::endl;
    stream << " from: " <<  vacansy.my_salary->get_from() << std::endl;
    stream << " to: " <<  vacansy.my_salary->get_to() << std::endl;
    return stream;
}

void HHVacansy::save()
{
    
}

