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


