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

void Skill::write_to_file()
{
    namespace fs = std::filesystem;
    std::filebuf fb;
    
    skill_logger()->info("[Skill::write_to_file] - start");

    const fs::path dictionary_path_folder{"dictionary"};    
    if(fs::exists(dictionary_path_folder)){
        skill_logger()->info("[Skill::write_to_file] - dictionary folder already exists");
    } else {
        skill_logger()->info("[Skill::write_to_file] - creating dictionary folder");
        fs::create_directory(dictionary_path_folder);
    }


    const fs::path skills_path{"dictionary/skills"};
    std::ofstream skill_out_stream(skills_path, std::ios::out | std::ios::trunc);    
    json j_skills(my_skills);
    skill_out_stream << std::setw(4) << j_skills;

    const fs::path mw_skills_path{"dictionary/mw_skills"};
    std::ofstream mw_skill_out_stream(mw_skills_path, std::ios::out | std::ios::trunc);    
    json j_mw_skills(my_multy_word_skills);
    mw_skill_out_stream << std::setw(4) << j_mw_skills;

    const fs::path ignor_words_path{"dictionary/ignor_words"};
    std::ofstream ignor_words_out_stream(ignor_words_path, std::ios::out | std::ios::trunc);    
    json j_ignor_words(my_ignoring_words);
    ignor_words_out_stream << std::setw(4) << j_ignor_words;

    const fs::path unrecognized_path{"dictionary/unrecognized"};
    std::ofstream unrecognized_out_stream(unrecognized_path, std::ios::out | std::ios::trunc);    
    json j_unrecognized(my_unrecognized_strings);
    unrecognized_out_stream << std::setw(4) << j_unrecognized;

    const fs::path garbage_path{"dictionary/garbage"};
    std::ofstream garbage_out_stream(garbage_path, std::ios::out | std::ios::trunc);    
    json j_garbage(my_html_garbage);
    garbage_out_stream << std::setw(4) << j_garbage;    
    
    skill_logger()->info("[Skill::write_to_file] - end");
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
