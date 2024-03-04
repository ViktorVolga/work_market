#pragma once

#include <string>
#include <vector>
#include <memory>
#include <queue>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

enum class Expirience
{
    no_expirince,
    one_three_year,
    more_three_year,
};

enum class Level
{
    june,
    midle,
    senior,
    unknown,
};

class Salary
{
    int from;
    int to;
public:
    Salary(const int & from, const int & to);
};

typedef std::unique_ptr<Salary> salary_t;

class Vacansy
{
    int my_id                                {};
    std::string my_name                      {};
    std::string my_country                   {}; 
    std::string my_sity                      {};
    bool is_open                             {};
    std::string my_url                       {};
    std::string my_company                   {};
    salary_t my_salary                       {};
    Expirience my_expirience                 {};
    std::string my_description               {};
    std::vector<std::string> my_skills       {};
    Level my_level                          {3};
    std::string my_shedule                   {};
public:
    Vacansy();
    void set_my_id(int id);
    int get_my_id();
    void set_my_name(std::string name);
    const std::string & get_my_name();
    void set_my_country(std::string &country);
    const std::string & get_my_country();
    void set_my_sity(std::string sity);
    const std::string & get_my_sity();
    void set_is_open(bool open);
    bool get_is_open();
    void set_my_url(std::string &url);
    const std::string & get_my_url();
    void set_my_company(std::string & company);
    const std::string & get_my_company();
    void set_my_salary(int min_salary, int max_salary);
    const int & get_my_rub_salary();
    void set_my_expirience(std::string expirience);
    const Expirience get_my_expirience();
    void set_my_description(std::string description);
    const std::string & get_my_descripton(); 
    void set_my_schedule(std::string shedule);
    virtual void save() = 0;   
};

class HHVacansy : public Vacansy {
    
public:
    HHVacansy(const json & vacansy_json);
    void save() override;

};

