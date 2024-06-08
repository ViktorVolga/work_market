#pragma once

#include <vector>
#include <memory>
#include <list>

#include "salary.h"
#include "skill.h"
#include "vacansy.h"

class SingleSkillStat{
    const int my_skill_id;
    const std::string my_skill_name;
    int my_jun_vacansies_count {0};
    int my_midl_vacancies_count {0};
    int my_senior_vacansies_count {0};
    int my_undef_vacansies_count {0};
    std::list<salary_ptr_t> my_jun_salary_list;
    std::list<salary_ptr_t> my_mid_salary_list;
    std::list<salary_ptr_t> my_senior_salary_list;
    std::list<salary_ptr_t> my_common_salary_list;
    int my_average_june_salary_from {0};
    int my_average_june_salary_to {0};
    int my_average_june_salary {0};
    int my_averaпу_midle_salary {0};
    int my_averaпу_midle_salary_from {0};
    int my_averaпу_midle_salary_to {0};
    int my_average_senior_salary_from {0};
    int my_average_senior_salary_to {0};
    int my_average_senior_salary {0};
    int my_average_salary_common {0};
    int my_average_salary_common_from {0};
    int my_average_salary_common_to {0};
    std::vector<int> my_friend_skills;
public:
    SingleSkillStat(int id, std::string & name) : my_skill_id(id), my_skill_name(name) {
        my_friend_skills.resize(get_skills()->get_etalon_skills_count());
    };
    int count_awerage_salary(std::list<salary_ptr_t> & jun_salary_list);
    int count_awerage_salary_from(std::list<salary_ptr_t> & jun_salary_list);
    int count_awerage_salary_to(std::list<salary_ptr_t> & jun_salary_list);
    void add_to_stat(ApplicantLevel level, salary_ptr_t && salary, std::queue<int> & friend_skills);
    int get_my_senior_vacansies_count();
    int get_count_senior_salaries_saved();
    std::vector<int> & get_my_friend_skills();
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