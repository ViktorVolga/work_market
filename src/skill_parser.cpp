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
            vacansy->add_my_skill(std::move(std::make_unique<SkillRepresentation>(mw_skill.second, mw_skill.first)));
        }
    }
}

void SimpleSkillParser::split_description(Vacansy *vacansy)
{
    using namespace boost;
    boost::split(my_words, vacansy->get_my_descripton(), boost::is_any_of(" "));
    for(auto & s : my_words){
        trim_if(s, is_any_of("."));
        trim_if(s, is_any_of(","));
        trim_if(s, is_any_of("«"));
        trim_if(s, is_any_of("»"));
        trim_if(s, is_any_of(":"));
        trim_if(s, is_any_of(")"));
        trim_if(s, is_any_of("("));
        trim_if(s, is_any_of(";"));
        trim_if(s, is_any_of(")"));
        trim_if(s, is_any_of("\""));
        trim_if(s, is_any_of("“"));        
    }
}

void SimpleSkillParser::find_skills(Vacansy * vacansy)
{   
    skill_logger()->debug("[SimpleSkillParser::find_skills] - start");
    skill_ptr_t skills = get_skills();
    for (auto & s : my_words){
        std::unique_ptr<SkillRepresentation> sr = skills->is_skill(s);                 
        if(sr){
            skill_logger()->debug("[impleSkillParser::find_skills] found skill {}", s);
            vacansy->add_my_skill(std::move(sr));            
        } else if(skills->is_ignor_word(s)) {
            skill_logger()->debug("[impleSkillParser::find_skills] candidate is ignoring string {}", s);            
        } else {
            using namespace boost::locale::conv;     
            std::string utf8_str;
            try{
                std::locale loc("ru_RU.UTF-8");
                std::locale conv_loc = boost::locale::util::create_info(loc, loc.name());
                utf8_str = to_utf<char>(s, conv_loc);
                /*if (utf8_str == "")
                {
                    std::locale loc("");
                    std::locale conv_loc = boost::locale::util::create_info(loc, loc.name());
                    utf8_str = to_utf<char>(s, conv_loc);
                }*/
            }
            catch(std::bad_cast & bc){
                skill_logger()->error("[SimpleSkillParser::find_skills] can't convert string to utf8 {}", bc.what());
            }
            catch(boost::locale::conv::invalid_charset_error & ice){
                skill_logger()->error("[SimpleSkillParser::find_skills] can't convert string to utf8 {}", ice.what());
            }
            
            skill_logger()->debug("[impleSkillParser::find_skills] candidate is unrecognized string {}", utf8_str);
            skills->add_unrecognized_string(std::move(utf8_str));
        }
    }
    skill_logger()->debug("[SimpleSkillParser::find_skills] - end");
}

void SimpleSkillParser::parse(Vacansy *vacansy)
{
    skill_logger()->info("[SimpleSkillParser::parse] - start");
    erase_garbage(vacansy->get_my_descripton());
    parse_multy_word_skills(vacansy);
    split_description(vacansy);
    find_skills(vacansy);
}

SimpleSkillParser::~SimpleSkillParser()
{

}

skill_parser_t SkillParserFabrica::get_skill_parser()
{        
    return std::make_unique<SimpleSkillParser>();
}
