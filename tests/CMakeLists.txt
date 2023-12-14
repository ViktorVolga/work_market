find_package(GTest REQUIRED)

add_executable(test-web_request test-web_request.cpp)

target_link_libraries(test-web_request
 PRIVATE
  GTest::GTest
  web_request)

add_test(web_request_tests test-web_request)
