#include "skill_statistic.h"

SkillStatistic::SkillStatistic(int skill_count)
{   
    skill_logger()->debug("[SkillStatistic::SkillStatistic] constructor start");
    my_skill_stat.resize(get_skills()->get_etalon_skills_count() + 1);    
    SingleSkillStatFabrica sssf;
    my_skill_stat[0] =  sssf.get_sss(static_cast<int>(1));
    for (ssize_t i = 1; i <= get_skills()->get_etalon_skills_count(); i++){      
        my_skill_stat[i] = sssf.get_sss(static_cast<int>(i));
        if (!my_skill_stat[i]){
            skill_logger()->error("[SkillStatistic::SkillStatistic] can't construct skill with id {i}");
        }
    }
    skill_logger()->debug("[SkillStatistic::SkillStatistic] constructor end");
}

void SkillStatistic::add_to_skills(std::unique_ptr<Vacansy> &vacansy)
{
    skill_logger()->debug("[SkillStatistic::add_to_skills] - start");
    if (!vacansy){
        skill_logger()->error("[SkillStatistic::add_to_skill] vacansy is null_ptr");
        return;
    }

    std::vector<skill_represent_ptr_t>  & v_skills = vacansy->get_my_skills();

   std::vector<int> friend_skills;

    for(const auto & s : v_skills){
        friend_skills.push_back(s->my_id);
    }

    for (const auto & s : v_skills){
        int id = s->my_id;
        my_skill_stat[id]->add_to_stat(vacansy->get_my_level(), 
            std::make_unique<Salary>(vacansy->get_my_rub_salary_from(), vacansy->get_my_rub_salary_to()),
            friend_skills);        
    }
    skill_logger()->debug("[SkillStatistic::add_to_skills] - end");
}

int SkillStatistic::get_skill_count()
{    
    return my_skill_stat.size();
}

void SkillStatistic::sort_skill_by_count()
{
    skill_logger()->debug("[SkillStatistic::sort_skill_by_count] - start");
    std::sort(my_skill_stat.begin(), my_skill_stat.end(), [](std::unique_ptr<SingleSkillStat> & sss1, std::unique_ptr<SingleSkillStat> & sss2){
        return sss1->get_my_common_vacansies_count() > sss2->get_my_common_vacansies_count();
    });
    skill_logger()->debug("[SkillStatistic::sort_skill_by_count] - end");
}

void SkillStatistic::print_stat()
{    
    for (auto & s : my_skill_stat){
        std::cout << *s.get();
    }
}

/*int SkillStatistic::get_skill_stat_by_id(int id)
{
    if (id < my_skill_stat.size() && id >= 0)
        return my_skill_stat.at(id);
    else
        return 0;

}*/

bool operator<(const SingleSkillStat &sss1, const SingleSkillStat &sss2)
{    
    return sss1.my_common_vacansies_count < sss2.my_common_vacansies_count;
}

std::ostream &operator<<(std::ostream &stream, const SingleSkillStat &skill_stat)
{
    stream << skill_stat.my_skill_name << " " << skill_stat.my_common_vacansies_count << std::endl;
    return stream;
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

int SingleSkillStat::count_awerage_salary_from(std::list<salary_ptr_t> & salary_list)
{
    int temp_sum = 0;    
    int count = 0;
    for(auto & s : salary_list){
        if (s->get_int_from() != 0) {
            temp_sum += s->get_int_from(); 
            count++;
        }
    }
    return (temp_sum / count);    
}

int SingleSkillStat::count_awerage_salary_to(std::list<salary_ptr_t> & salary_list)
{
    int temp_sum = 0;
    int count = 0;
    for(auto & s : salary_list){
        if (s->get_int_to() != 0) {
            temp_sum += s->get_int_to(); 
            count++;
        }
    }
    return (temp_sum / count);   
}

void SingleSkillStat::add_to_stat(ApplicantLevel level, salary_ptr_t && salary, std::vector<int> & friend_skills)
{
    web_logger()->debug("SingleSkillStat::add_to_stat - started");
    my_common_vacansies_count++;
    switch (level){
        case ApplicantLevel::june :
            my_jun_vacansies_count++;
            my_jun_salary_list.push_back(std::move(salary));
            for(auto & f_s : friend_skills){
                if (my_friend_skills.size() > static_cast<ssize_t>(f_s))
                    my_friend_skills.at(f_s)++;
            }
            break;
        case ApplicantLevel::midle :
            my_midl_vacancies_count++;
            my_mid_salary_list.push_back(std::move(salary));
            for(auto & f_s : friend_skills){
                if (my_friend_skills.size() > static_cast<ssize_t>(f_s))
                    my_friend_skills.at(f_s)++;
            }
            break;
        case ApplicantLevel::senior :
            my_senior_vacansies_count++;
            my_senior_salary_list.push_back(std::move(salary));
            for(auto & f_s : friend_skills){
                if (my_friend_skills.size() > static_cast<ssize_t>(f_s))
                    my_friend_skills.at(f_s)++;
            }
            break;
        case ApplicantLevel::unknown :
            my_undef_vacansies_count++;
            my_common_salary_list.push_back(std::move(salary));
            for(auto & f_s : friend_skills){
                if (my_friend_skills.size() > static_cast<ssize_t>(f_s))
                    my_friend_skills.at(f_s)++;
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

int SingleSkillStat::get_my_common_vacansies_count()
{
    return my_common_vacansies_count;
}

std::unique_ptr<SingleSkillStat> SingleSkillStatFabrica::get_sss(int id)
{
    return std::make_unique<SingleSkillStat>(id, get_skills()->get_etalon_name(id));
}
