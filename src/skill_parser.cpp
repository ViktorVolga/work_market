#include "skill_parser.h"

SkillParser::SkillParser()
{
    skill = get_skills();
}

void SimpleSkillParser::erase_garbage(std::string & description)
{
    skill_logger()->info("[SimpleSkillParser::erase_garbage] - start");
    skill_ptr_t skils = get_skills();
    for (auto & garbage : skils->get_garbage())
    {        
        auto garbage_pos = description.find(garbage);
        while(garbage_pos != std::string::npos)
        {
            description.erase(garbage_pos, garbage.length());
            garbage_pos = description.find(garbage);
        }
    }
    skill_logger()->info("[SimpleSkillParser::erase_garbage] - result description: {}", description);
}

void SimpleSkillParser::parse_multy_word_skills(Vacansy *vacansy)
{
    skill_logger()->info("[SimpleSkillParser::parse_multy_word_skills] - start");
    std::string & description = vacansy->get_my_descripton();
    std::map<std::string, int> & mw_map  = get_skills()->get_multy_word_skills();
    for (auto & mw_skill : mw_map){
        auto it = description.find(mw_skill.first);
        if(it != std::string::npos){            
            vacansy->add_my_skill(mw_skill.second);
        }
    }
}

void SimpleSkillParser::parse(Vacansy *vacansy)
{
    skill_logger()->info("[SimpleSkillParser::parse] - start");
    erase_garbage(vacansy->get_my_descripton());

}

SimpleSkillParser::~SimpleSkillParser()
{

}

skill_parser_t SkillParserFabrica::get_skill_parser()
{        
    return std::make_unique<SimpleSkillParser>();
}
