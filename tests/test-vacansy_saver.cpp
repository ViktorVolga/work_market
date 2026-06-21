#include <gtest/gtest.h>
#include <vacansy_saver.h>

std::unique_ptr<SaveInSQL> saver;
std::unique_ptr<Vacansy> vacancy;

void init_test_enviropment(){
    saver = std::make_unique<SaveInSQL>();
    vacancy = std::make_unique<HHVacansy>();    
}

TEST(save_city_sut, save_city_in_dtb){
    vacancy->set_my_city("Москва");
    vacancy->set_my_company("Test Enterprise");
    vacancy->set_my_id(666);
    vacancy->set_my_name("c++ profi");
    vacancy->set_my_description("code c++ apps");
    

    std::shared_ptr<VacancyTables> vt = std::make_shared<VacancyTables>();
    saver->resolve_save(vacancy);
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}