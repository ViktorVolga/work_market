#include "skill.h"

int Skill::is_skill(std::string skill_candidat)
{
    int skill = 0;
    if (auto it = my_skills.find(skill_candidat); it != my_skills.end())
    {
        skill = 1;
    }       
    
    if (auto it2 = my_multy_world_skills.find(skill_candidat); it2 != my_multy_world_skills.end())
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

