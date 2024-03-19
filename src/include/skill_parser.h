#pragma once

#include "skill.h"
#include "vacansy.h"

#include <memory>

//extern const skill_ptr_t get_skills(); 

class SkillParser{    
    skill_ptr_t skill;
public:
    SkillParser();
    virtual void parse(Vacansy * vacansy) = 0;    
    virtual ~SkillParser(){};
};

typedef std::unique_ptr<SkillParser> skill_parser_t;

class SimpleSkillParser : public SkillParser{
public:
    SimpleSkillParser() : SkillParser(){};
    void erase_garbage(std::string & description);
    void parse_multy_word_skills(Vacansy * vacansy);
    void parse(Vacansy * vacansy) override;
    ~SimpleSkillParser() override;
};

class SkillParserFabrica {
public:
    skill_parser_t get_skill_parser();
};

