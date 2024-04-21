#include "include/vacansy.h"
#include "vacansy.h"
#include "logger.h"

Salary::Salary(const int from, const int to)
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
    web_logger()->debug("Vacansy::set_my_id my_id =  [{}]", id);
    my_id = id;
}

int Vacansy::get_my_id()
{    
    return my_id;
}

void Vacansy::set_my_name(std::string name)
{
    web_logger()->debug("Vacansy::set_my_name =  [{}]", name);
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

void Vacansy::set_my_city(std::string city)
{
    web_logger()->debug("Vacansy::set_my_city = [{}]", city);
    my_city = city;
}

void Vacansy::set_my_salary(int min_salary, int max_salary)
{    
    web_logger()->debug("Vacansy::set_my_salary min = [{}], max = [{}]", min_salary, max_salary);   
    my_salary = std::make_unique<Salary>(min_salary, max_salary);
}

void Vacansy::set_my_expirience(std::string expirience)
{
    web_logger()->debug("Vacansy::set_my_expirience = [{}]",expirience);
    if(expirience == "noExperience")
        my_expirience =  Expirience::no_expirince;
}

void Vacansy::set_my_description(std::string description)
{
   web_logger()->debug("Vacansy::set_my_description = [{}]", description);
   my_description = description;
}

std::string &Vacansy::get_my_descripton()
{
    return my_description;
}

void Vacansy::set_my_schedule(std::string shedule)
{
    web_logger()->debug("Vacansy::set_my_schedule = [{}]", shedule);
    my_shedule = shedule;
}

HHVacansy::HHVacansy(const json &vacansy_json)
{   
    int min_salary, max_salary;  
    set_my_id(stoi(vacansy_json["id"].template get<std::string>()));
    set_my_name(vacansy_json["name"].template get<std::string>());
    set_my_city(vacansy_json["area"]["name"].template get<std::string>());
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
    web_logger()->debug("Vacansy::get_skils_from_json start");
    for (auto & skill : vacansy_json["key_skills"])
    {
        web_logger()->debug("Vacansy::get_skils_from_json candidate [{}]", skill["name"]);
        my_candidats_to_skills.push(skill["name"]);
    }
}

void Vacansy::clear_one_description(std::string & to_delete)
{
    web_logger()->debug("[Vacansy::clear_description] start");
    
    auto it = my_description.find(to_delete);
    while(it != -1)
    {
        my_description.erase(it, 3);
        it = my_description.find(to_delete);
    }
    web_logger()->debug("[Vacansy::clear_description] end");
}

void Vacansy::add_my_skill(skill_represent_ptr_t && skill)
{
    for (auto & s: my_skills){
        if (s->my_id == skill->my_id)
            return;
    }
    my_skills.push_back(std::move(skill));     //   push_back(skill);
}

std::ostream & operator<<(std::ostream &stream, const Vacansy &vacansy)
{    
    stream << "id: " << boost::lexical_cast<std::string>(vacansy.my_id) << std::endl;
    stream << "name: " << vacansy.my_name << std::endl;
    stream << "country: " << vacansy.my_country << std::endl;
    stream << "city: " << vacansy.my_city << std::endl;
    stream << "company: " << vacansy.my_company << std::endl;
    stream << "salary: " <<  std::endl;
    stream << " from: " <<  vacansy.my_salary->get_from() << std::endl;
    stream << " to: " <<  vacansy.my_salary->get_to() << std::endl;
    stream << "expirience: ";
    switch (vacansy.my_expirience){
        case Expirience::no_expirince :
            stream << "no expirience";
            break;
        case Expirience::one_three_year :
            stream << "1 - 3 years";
            break;
        case Expirience::more_three_year :
            stream << "> 3 years";
            break;
    }
    stream << std::endl;
    stream << "description: " << vacansy.my_description << std::endl;
    stream << "skills[" << vacansy.my_skills.size() << "] :" << std::endl;
    for (auto & s : vacansy.my_skills){
        stream << *s.get();
    }    
    stream << "level: ";
    switch (vacansy.my_level){
        case Level::june :
            stream << "june";
            break;
        case Level::midle :
            stream << "midle";
            break;
        case Level::senior :
            stream << "senior";
            break;
        case Level::unknown :
            stream << "unknown";
            break;
        default :
            stream << "unknown";
            break;
    }
    stream << std::endl;
    stream << "shedule: " << vacansy.my_shedule << std::endl;
    return stream;
}

std::istream &operator>>(std::istream &stream, Vacansy &vacansy)
{
    std::string raw_id;
    std::string id;
    std::getline(stream, raw_id);
    if(id[0] == 'i'){
        id = raw_id.substr(4, raw_id.size() - 4);        
        vacansy.my_id = boost::lexical_cast<int>(id);
    }

    std::string raw_name;
    std::getline(stream, raw_name);
    if(raw_name[0] == 'n'){
        vacansy.my_name = raw_name.substr(6, raw_name.size() - 6);
    }

    std::string raw_country;
    std::getline(stream, raw_country);
    if(raw_country[0] == 'c'){
        if(raw_country.size() > 9)
            vacansy.my_country = raw_country.substr(9, raw_country.size() - 9);
    }

    std::string raw_city;
    std::getline(stream, raw_city);
    if(raw_city[0] == 's' || raw_city[0] == 'c'){
        if(raw_city.size() > 6)
            vacansy.my_city = raw_city.substr(6, raw_city.size() - 6);
    }

    std::string raw_company;
    std::getline(stream, raw_company);
    if(raw_company[0] == 'c'){
        if(raw_company.size() > 9)
            vacansy.my_company = raw_company.substr(9, raw_company.size() - 9);
    }

  
    std::string raw_from;
    int from{}, to{};
    std::getline(stream, raw_from);
    std::getline(stream, raw_from);
    if(raw_from[1] == 'f'){
        std::string salary_from = raw_from.substr(7, raw_from.size() - 7);
        from = boost::lexical_cast<int>(salary_from);
    }

    std::string raw_to;
       std::getline(stream, raw_to);
    if(raw_to[1] == 't'){
        std::string salary_to = raw_to.substr(5, raw_to.size() - 5);
        to = boost::lexical_cast<int>(salary_to);
    }
    vacansy.my_salary = std::make_unique<Salary>(from, to);



    
    return stream;
}

void HHVacansy::save()
{
    
}

