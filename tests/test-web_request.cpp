#include <gtest/gtest.h>
#include <request_handler.h>
#include <vacansy_handler.h>

TEST(web_reques_sut, get_num_pages_test)
{
    
    std::shared_ptr<VacansyHandler> vh_ptr_t = std::make_shared<VacansyHandler>();
    RequestHandler rh(vh_ptr_t);
    request_t request = std::make_unique<ProfessionRequest>(specializations_t::cpp);        
    rh.add_request(request);
    request_t &my_req = rh.get_request();
    my_req->execute_request();
    int num_pages_in_request {};
    num_pages_in_request = rh.get_num_pages_in_request(my_req);
    EXPECT_GE(num_pages_in_request, 0);
    EXPECT_LE(num_pages_in_request, 32600);
}

TEST(web_request_sut, parsing_web_request_add_requests_in_queue)
{
    
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}