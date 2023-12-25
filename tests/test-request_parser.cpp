#include <gtest/gtest.h>
#include <request_handler.h>
#include <request_parser.h>

TEST(RequestFabricaSut, shuldReturnHHProfRequestParser)
{
    /*Arrange*/
    RequestHandler rh;
    request_t request = std::make_unique<ProfessionRequest>(specializations_t::cpp);  
    RequestParserFabrica fabrica;
    std::unique_ptr<RequestParser> parser_ptr;

    /*Action*/
    parser_ptr = fabrica.get_request_parser(&rh, request_type_t::HHProfRequest);
    RequestParser * rp_ptr = parser_ptr.get();
    
    /*Assert*/
    EXPECT_NE(dynamic_cast<HHRequestParser*>(rp_ptr), nullptr);
}

TEST(isRequestFirstPageSut, shuldbeTruer)
{
   
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}