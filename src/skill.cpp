#include "skill.h"

std::unique_ptr<SkillRepresentation> Skill::is_skill(std::string &skill_candidat){
    
    if (auto it = my_skills.find(skill_candidat); it != my_skills.end())
    {
        int id = it->second;
        std:: string name = get_etalon_name(id);
        return std::make_unique<SkillRepresentation>(id, name);        
    }       
    
    if (auto it2 = my_multy_word_skills.find(skill_candidat); it2 != my_multy_word_skills.end())
    {
        int id = it2->second;
        std:: string name = get_etalon_name(id);
        return std::make_unique<SkillRepresentation>(id, name);  
    } 

    return nullptr;      
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
    if(skill_out_stream.is_open()){
        skill_logger()->debug("[Skill::write_to_file] - skill_out_stream is opened");
        json j_skills(my_skills);      
        skill_out_stream << std::setw(4) << j_skills;
        skill_logger()->debug("[Skill::write_to_file] - my_skills writed");        
    } else {
        skill_logger()->error("[Skill::write_to_file] - skill_out_stream isn't opened");
    }
    

    const fs::path mw_skills_path{"dictionary/mw_skills"};
    std::ofstream mw_skill_out_stream(mw_skills_path, std::ios::out | std::ios::trunc);    
    json j_mw_skills(my_multy_word_skills);
    skill_logger()->debug("[Skill::write_to_file] - j_mw_skills parsed"); 
    mw_skill_out_stream << std::setw(4) << j_mw_skills;

    const fs::path ignor_words_path{"dictionary/ignor_words"};
    std::ofstream ignor_words_out_stream(ignor_words_path, std::ios::out | std::ios::trunc);    
    json j_ignor_words(my_ignoring_words);
    skill_logger()->debug("[Skill::write_to_file] - ignor_words parsed"); 
    ignor_words_out_stream << std::setw(4) << j_ignor_words;

    const fs::path unrecognized_path{"dictionary/unrecognized"};
    std::ofstream unrecognized_out_stream(unrecognized_path, std::ios::out | std::ios::trunc);    
    json j_unrecognized(my_unrecognized_strings);
    skill_logger()->debug("[Skill::write_to_file] - unrecognized parsed"); 
    
    unrecognized_out_stream << std::setw(4) << j_unrecognized;    

    const fs::path garbage_path{"dictionary/garbage"};
    std::ofstream garbage_out_stream(garbage_path, std::ios::out | std::ios::trunc);    
    json j_garbage(my_html_garbage);
    skill_logger()->debug("[Skill::write_to_file] - garbage parsed"); 
    garbage_out_stream << std::setw(4) << j_garbage;    
    
    skill_logger()->info("[Skill::write_to_file] - end");
}

void Skill::read_skills_from_file()
{
    skill_logger()->debug("[Skill::read_skills_from_file] - start");
    namespace fs = std::filesystem;  

    const fs::path skills_path{"dictionary/skills"};
    std::ifstream skill_in_stream(skills_path, std::ios::in);
    if(!skill_in_stream.is_open()){
        skill_logger()->error("[Skill::read_skills_from_file] - can't open file ");
        return;
    }    
    json j_skills;
    skill_in_stream >> j_skills;
    for (auto & item : j_skills.items()){        
        my_skills.emplace(item.key(), item.value());
    }
    skill_logger()->debug("[Skill::read_skills_from_file] - end");
}

void Skill::read_mw_skills_from_file()
{
    skill_logger()->debug("[Skill::read_mw_skills_from_file] - start");
    namespace fs = std::filesystem;  

    const fs::path skills_path{"dictionary/mw_skills"};
    std::ifstream skill_in_stream(skills_path, std::ios::in);
    if(!skill_in_stream.is_open()){
        skill_logger()->error("[Skill::read_mw_skills_from_file] - can't open file ");
        return;
    }    
    json j_skills;
    skill_in_stream >> j_skills;
    for (auto & item : j_skills.items()){        
        my_multy_word_skills.emplace(item.key(), item.value());
    }
    skill_logger()->debug("[Skill::read_mw_skills_from_file] - end");
}

void Skill::read_my_ignoring_words()
{
    skill_logger()->debug("[Skill::read_my_ignoring_words] - start");
    namespace fs = std::filesystem;  

    const fs::path skills_path{"dictionary/ignor_words"};
    std::ifstream skill_in_stream(skills_path, std::ios::in);
    if(!skill_in_stream.is_open()){
        skill_logger()->error("[Skill::read_my_ignoring_words] - can't open file ");
        return;
    }    
    json j_iw;
    skill_in_stream >> j_iw;
    for (auto & item : j_iw.items()){
        skill_logger()->debug("[Skill::read_my_ignoring_words] - ignoring word {}", item.value());       
        my_ignoring_words.emplace(item.value());
    }
    skill_logger()->debug("[Skill::read_my_ignoring_words] - end");
}

void Skill::read_my_unrecognized_strings()
{
    skill_logger()->info("[Skill::read_my_unrecognized_strings] - start");
    namespace fs = std::filesystem;  

    const fs::path skills_path{"dictionary/unrecognized"};
    std::ifstream skill_in_stream(skills_path, std::ios::in);
    if(!skill_in_stream.is_open()){
        skill_logger()->error("[Skill::read_my_unrecognized_strings] - can't open file ");
        return;
    }    
    json j_unrecognized;
    skill_in_stream >> j_unrecognized;
    for (auto & item : j_unrecognized.items()){        
       my_unrecognized_strings.emplace(item.value());
    }
    skill_logger()->info("[Skill::read_my_unrecognized_strings] - end");
}

void Skill::read_my_html_garbage()
{
    skill_logger()->info("[Skill::read_my_html_garbage] - start");
    namespace fs = std::filesystem;  

    const fs::path skills_path{"dictionary/garbage"};
    std::ifstream skill_in_stream(skills_path, std::ios::in);
    if(!skill_in_stream.is_open()){
        skill_logger()->error("[Skill::read_my_html_garbage] - can't open file ");
        return;
    }    
    json j_garbage;
    skill_in_stream >> j_garbage;    
    for (auto & item : j_garbage.items()){        
        my_html_garbage.push_back(item.value());
    }
    skill_logger()->info("[Skill::read_my_html_garbage] - end");
}

void Skill::read_my_dictionaries()
{
    skill_logger()->info("[Skill::read_my_dictionaries] - start");
    
    namespace fs = std::filesystem;

    const fs::path dictionary_path_folder{"dictionary"};  
    if(fs::exists(dictionary_path_folder)){
        if(fs::exists("dictionary/skills")){
            read_skills_from_file();
        } else {
            skill_logger()->error("[Skill::read_my_dictionaries] - no skills file exists");
        }
        if(fs::exists("dictionary/mw_skills")){
            read_mw_skills_from_file();
        } else {
            skill_logger()->error("[Skill::read_my_dictionaries] - no mw_skills file exists");
        }
        if(fs::exists("dictionary/ignor_words")){
            read_my_ignoring_words();
        } else {
            skill_logger()->error("[Skill::read_my_dictionaries] - no ignor_words file exists");
        }
        if(fs::exists("dictionary/unrecognized")){
            read_my_unrecognized_strings();
        } else {
            skill_logger()->error("[Skill::read_my_dictionaries] - no unrecognized file exists");
        }
        if(fs::exists("dictionary/garbage")){
            read_my_html_garbage();
        } else {
            skill_logger()->error("[Skill::read_my_dictionaries] - no garbage file exists");
        }
    } else {
        skill_logger()->error("[Skill::read_my_dictionaries] - dictionary folder isn't exists");
    }
    skill_logger()->info("[Skill::read_my_dictionaries] - end");
}

/*
    id - skill id
    return etalon name used for this skill id if succes
    or string "error" 
*/
std::string Skill::get_etalon_name(int id)
{
    auto it = etalon_skills.find(id);
    if (it != etalon_skills.end())
        return it->second;
    else 
        return "error";    
}

bool Skill::is_ignor_word(std::string &word)
{   
    auto it = my_ignoring_words.find(word);
    if(it == my_ignoring_words.end())
        return false;
    else
        return true;    
}

void Skill::add_unrecognized_string(std::string &&unrec_word)
{
    skill_logger()->debug("[Skill::add_unrecognized_string] - start");
    
    if(unrec_word == "")
        return;
    
    my_unrecognized_strings.emplace(unrec_word);
           
        
    skill_logger()->debug("[Skill::add_unrecognized_string] - end");    
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

std::ostream &operator<<(std::ostream &stream, const SkillRepresentation &skill_representation)
{
    stream << "skill {" << std::endl; 
    stream << " id: " << skill_representation.my_id << "," << std::endl;
    stream << " name: " << skill_representation.my_id << " }"<< std::endl;
    return stream;   
}
