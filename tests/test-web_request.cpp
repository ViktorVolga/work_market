#include <gtest/gtest.h>
#include <web_request.h>

TEST(web_reques_sut, get_num_pages_test)
{
    RequestHandler rh;
    request_t request = std::make_unique<ProfessionRequest>(specializations_t::cpp);        
    rh.add_request(request);
    request_t &my_req = rh.get_request();
    my_req->execute_request();
    int num_pages_in_request {};
    num_pages_in_request = rh.get_num_pages_in_request(my_req);
    EXPECT_GE(num_pages_in_request, 0);
    EXPECT_LE(num_pages_in_request, 32600);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}