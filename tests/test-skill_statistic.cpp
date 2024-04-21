#include <gtest/gtest.h>
#include <skill_statistic.h>

TEST(SkillStatistic_sut, shuldReturnNotNull){
    /*arrange*/
    skill_stat_ptr_t stat_ptr = get_skill_stat_ptr();

    /*assert*/
    EXPECT_NE(stat_ptr, nullptr);
}

TEST(SkillStatistic_sut_sut, constructor){
    /*arrange*/
    skill_ptr_t skill_ptr = get_skills();

    /*action*/
    SkillStatistic stat(skill_ptr->get_etalon_skills_count());

    /*assert*/
    EXPECT_EQ(skill_ptr->get_etalon_skills_count(), stat.get_skill_count());
}

TEST(SkillStatistic_sut_sut, add_to_skill_count){
    /*arrange*/
    skill_stat_ptr_t stat_ptr = get_skill_stat_ptr();

    /*action*/
    stat_ptr->add_to_skill(0);

    /*assert*/
    EXPECT_EQ(1, stat_ptr->get_skill_stat_by_id(0));
}

TEST(SkillStatistic_sut_sut, add_to_skill_count1){
    /*arrange*/
    skill_stat_ptr_t stat_ptr = get_skill_stat_ptr();

    /*action*/
    stat_ptr->add_to_skill(stat_ptr->get_skill_count() + 1);

    /*assert*/
    EXPECT_EQ(0, stat_ptr->get_skill_stat_by_id(stat_ptr->get_skill_count() + 1));
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}