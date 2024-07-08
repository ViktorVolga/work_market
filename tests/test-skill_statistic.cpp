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

//TEST(SkillStatistic_sut_sut, add_to_skill_count){
    /*arrange*/
    //skill_stat_ptr_t stat_ptr = get_skill_stat_ptr();

    /*action*/
    //stat_ptr->add_to_skill(0);

    /*assert*/
    //EXPECT_EQ(1, stat_ptr->get_skill_stat_by_id(0));
//}

TEST(SingleSkillStat_sut, SingleSkillStat_sut_count_awerage_Test){
    /*arrange*/
    std::string name = "linux";
    SingleSkillStat skill_stat(1, name);    
    std::list<salary_ptr_t> salary_list;
    salary_list.push_back(std::make_unique<Salary>(100, 200));
    salary_list.push_back(std::make_unique<Salary>(0, 200));
    salary_list.push_back(std::make_unique<Salary>(200, 300));

    /*action*/
    int awerage_salary = skill_stat.count_awerage_salary(salary_list);

    /*assert*/
    EXPECT_EQ(awerage_salary, 200);
}

TEST(SingleSkillStat_sut, SingleSkillStat_sut_count_awerage_from_Test){
    /*arrange*/
    std::string name = "linux";
    SingleSkillStat skill_stat(1, name);    
    std::list<salary_ptr_t> salary_list;
    salary_list.push_back(std::make_unique<Salary>(100, 200));
    salary_list.push_back(std::make_unique<Salary>(0, 200));
    salary_list.push_back(std::make_unique<Salary>(200, 300));

    /*action*/
    int awerage_salary = skill_stat.count_awerage_salary_from(salary_list);

    /*assert*/
    EXPECT_EQ(awerage_salary, 150);
}

TEST(SingleSkillStat_sut, SingleSkillStat_sut_count_awerage_to_Test){
    /*arrange*/
    std::string name = "linux";
    SingleSkillStat skill_stat(1, name);    
    std::list<salary_ptr_t> salary_list;
    salary_list.push_back(std::make_unique<Salary>(100, 200));
    salary_list.push_back(std::make_unique<Salary>(0, 200));
    salary_list.push_back(std::make_unique<Salary>(200, 300));

    /*action*/
    int awerage_salary = skill_stat.count_awerage_salary_to(salary_list);

    /*assert*/
    EXPECT_EQ(awerage_salary, 233);
}

TEST(SingleSkillStat_sut, SingleSkillStat_add_to_skill_stat_Test){
    /*arrange*/
    std::string name = "linux";
    SingleSkillStat skil_stat = SingleSkillStat(1, name);
    std::vector<int> friend_queue;
    friend_queue.push_back(2);
    friend_queue.push_back(1);

    
    /*action*/
    skil_stat.add_to_stat(ApplicantLevel::senior, std::make_unique<Salary>(90000, 10000), friend_queue);

    /*asset*/
    EXPECT_EQ(skil_stat.get_my_senior_vacansies_count(), 1);
    EXPECT_EQ(skil_stat.get_count_senior_salaries_saved(), 1);
    EXPECT_EQ(skil_stat.get_my_friend_skills().at(2), 1);
}



int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}