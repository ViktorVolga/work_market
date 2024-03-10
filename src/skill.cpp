#include "skill.h"

int Skill::is_skill(std::string skill_candidat)
{
    int skill = 0;
    if (auto it = my_skills.find(skill_candidat); it != my_skills.end())
    {
        skill = 1;
    }       
    
    if (auto it2 = my_multy_word_skills.find(skill_candidat); it2 != my_multy_word_skills.end())
    {
        skill = 1;
    } 

    if (skill == 0)
    {
        if(auto it = my_unrecognized_strings.find(skill_candidat); it != my_unrecognized_strings.end())
            skill = 2;
        else{
            skill = 2;
            my_unrecognized_strings.insert(skill_candidat);
        }            
    } 
    return skill;      
}

std::map<std::string, int> & Skill::get_skills()
{
    return my_skills;    
}

std::map<std::string, int> & Skill::get_multy_word_skills()
{
    return my_multy_word_skills;
}

std::set<std::string> & Skill::get_ignoring_words()
{
    return my_ignoring_words;
}

std::set<std::string> & Skill::get_unrecognized_strings()
{
    return my_unrecognized_strings;
}

std::vector<std::string> & Skill::get_garbage()
{
    return my_html_garbage;
}

const skill_ptr_t get_skills()
{
    if(singletone_skill) {
        skill_logger()->info("[get_skills] singletone_skill already inicialized");
        return singletone_skill;
    } else {
        skill_logger()->info("[get_skills] inicializing new singletone_skill");
        singletone_skill = std::make_shared<Skill>();
        return singletone_skill;
    }        
}
