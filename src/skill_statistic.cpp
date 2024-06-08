#include "skill_statistic.h"

SkillStatistic::SkillStatistic(int skill_count)
{
    my_skill_stat.resize(static_cast<ssize_t>(skill_count));
    //my_skill_stat.reserve(skill_count);
}

void SkillStatistic::add_to_skill(int skill)
{
    if (skill < my_skill_stat.size() && skill >= 0) 
        my_skill_stat.at(skill)++;    
}

int SkillStatistic::get_skill_count()
{    
    return my_skill_stat.size();
}

int SkillStatistic::get_skill_stat_by_id(int id)
{
    if (id < my_skill_stat.size() && id >= 0)
        return my_skill_stat.at(id);
    else
        return 0;

}

const skill_stat_ptr_t get_skill_stat_ptr()
{
    if(!my_single_skill_stat){
        skill_ptr_t skill = get_skills();
        my_single_skill_stat = std::make_shared<SkillStatistic>(skill->get_etalon_skills_count());
        return my_single_skill_stat;
    } else {
        return my_single_skill_stat;
    }
}

int SingleSkillStat::count_awerage_salary(std::list<salary_ptr_t>  & salary_list)
{
    int temp_sum = 0;    
    int count = 0;
    for(auto & s : salary_list){
        if (s->get_int_from() != 0 && s->get_int_to() !=0) {
            temp_sum += (s->get_int_from() + s->get_int_to()) / 2;
            count++;
        }
    }
    return (temp_sum / count);
}

int SingleSkillStat::count_awerage_salary_from(std::list<salary_ptr_t> &jun_salary_list)
{
    int temp_sum = 0;    
    int count = 0;
    for(auto & s : jun_salary_list){
        if (s->get_int_from() != 0) {
            temp_sum += s->get_int_from(); 
            count++;
        }
    }
    return (temp_sum / count);    
}

int SingleSkillStat::count_awerage_salary_to(std::list<salary_ptr_t> &jun_salary_list)
{
    int temp_sum = 0;
    int count = 0;
    for(auto & s : jun_salary_list){
        if (s->get_int_to() != 0) {
            temp_sum += s->get_int_to(); 
            count++;
        }
    }
    return (temp_sum / count); 
    return 0;
}

void SingleSkillStat::add_to_stat(ApplicantLevel level, salary_ptr_t && salary, std::queue<int> & friend_skills)
{
    web_logger()->debug("SingleSkillStat::add_to_stat - started");
    switch (level){
        case ApplicantLevel::june :
            my_jun_vacansies_count++;
            my_jun_salary_list.push_back(std::move(salary));
            while (!friend_skills.empty()){
                if (my_friend_skills.size() > static_cast<ssize_t>(friend_skills.front()))
                    my_friend_skills.at(friend_skills.front())++;
                else
                    web_logger()->error("SingleSkillStat::add_to_stat skill id [{}] is bigger then size of frien skill count [{}]", 
                        static_cast<ssize_t>(friend_skills.front()), my_friend_skills.size());
                friend_skills.pop();
            }
            break;
        case ApplicantLevel::midle :
            my_midl_vacancies_count++;
            my_mid_salary_list.push_back(std::move(salary));
            while (!friend_skills.empty()){
                if (my_friend_skills.size() > static_cast<ssize_t>(friend_skills.front()))
                    my_friend_skills.at(friend_skills.front())++;
                else
                    web_logger()->error("SingleSkillStat::add_to_stat skill id [{}] is bigger then size of frien skill count [{}]", 
                        static_cast<ssize_t>(friend_skills.front()), my_friend_skills.size());
                friend_skills.pop();
            }
            break;
        case ApplicantLevel::senior :
            my_senior_vacansies_count++;
            my_senior_salary_list.push_back(std::move(salary));
            while (!friend_skills.empty()){
                if (my_friend_skills.size() > static_cast<ssize_t>(friend_skills.front()))
                    my_friend_skills.at(friend_skills.front())++;
                else
                    web_logger()->error("SingleSkillStat::add_to_stat skill id [{}] is bigger then size of frien skill count [{}]", 
                        static_cast<ssize_t>(friend_skills.front()), my_friend_skills.size());
                friend_skills.pop();
            }
            break;
        case ApplicantLevel::unknown :
            my_undef_vacansies_count++;
            my_common_salary_list.push_back(std::move(salary));
            while (!friend_skills.empty()){
                if (my_friend_skills.size() > static_cast<ssize_t>(friend_skills.front()))
                    my_friend_skills.at(friend_skills.front())++;
                else
                    web_logger()->error("SingleSkillStat::add_to_stat skill id [{}] is bigger then size of frien skill count [{}]", 
                        static_cast<ssize_t>(friend_skills.front()), my_friend_skills.size());
                friend_skills.pop();
            }
            break;
    }
}

int SingleSkillStat::get_my_senior_vacansies_count()
{
    return my_senior_vacansies_count;
}

int SingleSkillStat::get_count_senior_salaries_saved()
{
    return static_cast<int>(my_senior_salary_list.size());
}

std::vector<int> &SingleSkillStat::get_my_friend_skills()
{
    return my_friend_skills;
}
