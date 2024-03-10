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
