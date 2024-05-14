#include <gtest/gtest.h>
#include <vacansy.h>

TEST(SkillStatistic_sut, save_and_read_from_file){
    namespace fs = std::filesystem;

    /*cleaning*/
    if(fs::exists("test_vacansy")){
        fs::remove("test_vacansy");
    }

    /*arrange*/
    std::vector<skill_represent_ptr_t> skills;    
    skills.push_back(std::make_unique<SkillRepresentation>(1, "linux"));
    HHVacansy vacansy(666666, "test_vacansy", "Russia", "Samara", "Volga Software", 
        100000, 140000, "noExpirience", "good vacansy for a friends", skills, Level::june, "fullDay");    
      
    const fs::path vacansy_path{"test_vacansy"};    
    std::ofstream vacansy_out_stream(vacansy_path, std::ios::out | std::ios::trunc);
        vacansy_out_stream << vacansy;
    
    std::unique_ptr<Vacansy> vacansy_from_file = std::make_unique<HHVacansy>();
    std::ifstream vacansy_in_stream(vacansy_path, std::ios::in);
    vacansy_in_stream >> *vacansy_from_file.get();

    EXPECT_EQ(vacansy_from_file->get_my_id(), 666666);
    EXPECT_EQ(vacansy_from_file->get_my_name(), "test_vacansy");
    EXPECT_EQ(vacansy_from_file->get_my_country(), "Russia");
    EXPECT_EQ(vacansy_from_file->get_my_city(), "Samara");
    EXPECT_EQ(vacansy_from_file->get_my_company(), "Volga Software");
    EXPECT_EQ(vacansy_from_file->get_my_rub_salary_from(), 100000);
    EXPECT_EQ(vacansy_from_file->get_my_rub_salary_to(), 140000);   
    EXPECT_EQ(vacansy_from_file->get_my_expirience(), Expirience::no_expirince); 
    EXPECT_EQ(vacansy_from_file->get_my_descripton(), "good vacansy for a friends"); 
    EXPECT_EQ(vacansy_from_file->get_my_skill()->my_id, 1);    
    EXPECT_EQ(static_cast<int>(vacansy_from_file->get_my_level()), static_cast<int>(Level::june));
    EXPECT_EQ(vacansy_from_file->get_my_schedule(), "fullDay");
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}