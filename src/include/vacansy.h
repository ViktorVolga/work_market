#pragma once

#include <string>
#include <vector>
#include <memory>
#include <queue>
#include <nlohmann/json.hpp>
#include <iostream>
#include <boost/lexical_cast.hpp>
 
#include "salary.h"
#include "skill.h"

using json = nlohmann::json;

enum class Expirience
{
    no_expirince,
    one_three_year,
    more_three_year,
};

enum class ApplicantLevel
{
    june,
    midle,
    senior,
    unknown,
};

/*class Skill{
    std::string my_name;
    int my_id;
public:
    Skill(std::string & name, int id) : my_name(name), my_id(id){}; 
};*/

typedef std::unique_ptr<Salary> salary_t;
typedef std::unique_ptr<SkillRepresentation> skill_represent_ptr_t;

class Vacansy
{
    int my_id {};
    std::string my_name {};
    std::string my_country {}; 
    std::string my_city {};
    bool is_open {};
    std::string my_url {};
    std::string my_company {};
    salary_t my_salary {};
    Expirience my_expirience {};
    std::string my_description {};
    std::vector<skill_represent_ptr_t> my_skills {};
    ApplicantLevel my_level {3};
    std::string my_schedule {}; 
    std::queue<std::string> my_candidats_to_skills {};   
public:
    Vacansy();
    void set_my_id(int id);
    int get_my_id();
    void set_my_name(std::string name);
    const std::string & get_my_name();
    void set_my_country(std::string &country);
    const std::string & get_my_country();
    void set_my_city(std::string city);
    const std::string & get_my_city();
    void set_is_open(bool open);
    bool get_is_open();
    void set_my_url(std::string &url);
    const std::string & get_my_url();
    void set_my_company(std::string & company);
    const std::string & get_my_company();
    void set_my_salary(int min_salary, int max_salary);
    const int & get_my_rub_salary_from();
    const int & get_my_rub_salary_to();
    void set_my_expirience(std::string expirience);
    const Expirience get_my_expirience();
    void set_my_description(std::string description);
    std::string & get_my_descripton(); 
    void set_my_schedule(std::string shedule);
    void get_skils_from_json(const json & vacansy_json);
    virtual void save() = 0;
    void clear_one_description(std::string & to_delete);
    friend std::ostream& operator<< (std::ostream& stream, const Vacansy& vacansy);
    void add_my_skill(skill_represent_ptr_t && skill);
    friend std::istream& operator>> (std::istream& stream, Vacansy& vacansy); 
    void set_my_level(ApplicantLevel level);
    skill_represent_ptr_t get_my_skill();
    ApplicantLevel get_my_level();
    const std::string & get_my_schedule();
    std::vector<skill_represent_ptr_t> & get_my_skills();
};

class HHVacansy : public Vacansy {
    
public:
    HHVacansy();
    HHVacansy(const json & vacansy_json);
    HHVacansy(int id, std::string && name, std::string && country, std::string && city, std::string && company, int salary_from,
        int salary_to, std::string && expirience, std::string && description, std::vector<skill_represent_ptr_t> & skills, 
        ApplicantLevel level, std::string && schedule);
    void save() override;
};