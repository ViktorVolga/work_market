#pragma once

#include <vector>
#include <memory>
#include <list>

#include "salary.h"
#include "skill.h"

class SingleSkillStat{
    const int skill_id;
    std::string skill_name;
    int jun_vacansies_count {0};
    int midl_vacancies_count {0};
    int senior_vacansies_count {0};
    int undef_vacansies_count {0};
    std::list<Salary> jun_salary_list;
    std::list<Salary> mid_salary_list;
    std::list<Salary> senior_salary_list;
    std::list<Salary> common_salary_list;
    int average_june_salary_from {0};
    int average_june_salary_to {0};
    int average_june_salary {0};
    int averaпу_midle_salary {0};
    int averaпу_midle_salary_from {0};
    int averaпу_midle_salary_to {0};
    int average_senior_salary_from {0};
    int average_senior_salary_to {0};
    int average_senior_salary {0};
    int average_salary_common {0};
    int average_salary_common_from {0};
    int average_salary_common_to {0};
};

class SkillStatistic{
    std::vector<int> my_skill_stat;
public:
    SkillStatistic(int skill_count);
    void add_to_skill(int skill);
    int get_skill_count();
    int get_skill_stat_by_id(int id);
};

typedef std::shared_ptr<SkillStatistic> skill_stat_ptr_t;

static skill_stat_ptr_t my_single_skill_stat;

const skill_stat_ptr_t get_skill_stat_ptr();