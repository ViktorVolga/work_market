find_package(GTest REQUIRED)

add_executable(test-web_request test-web_request.cpp)

target_link_libraries(test-web_request PRIVATE GTest::GTest request_handler vacansy)

add_test(web_request_tests test-web_request)

add_executable(test-request_parser test-request_parser.cpp)

target_link_libraries(test-request_parser PRIVATE GTest::GTest request_handler)

target_link_libraries(test-request_parser PRIVATE request_handler vacansy) 

add_test(request_parser_tests test-request_parser)