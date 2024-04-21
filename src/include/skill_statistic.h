#pragma once

#include <vector>
#include <memory>

#include "skill.h"

class SkillStatistic{
    std::vector<int> my_skill_stat;
public:
    SkillStatistic(int skill_count);
    void add_to_skill(int skill);
    int get_skill_count();
    int get_skill_stat_by_id(int id);
};

typedef std::shared_ptr<SkillStatistic> skill_stat_ptr_t;

static skill_stat_ptr_t my_single_skill_stat;

const skill_stat_ptr_t get_skill_stat_ptr();