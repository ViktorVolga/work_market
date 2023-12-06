cmake_minimum_required(VERSION 3.22)

project(work_market VERSION 0.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDART 20)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_CXX_FLAGS -Wall)

enable_testing()

add_subdirectory(tests)

add_subdirectory(src)

add_executable(
    work_market
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/src/web_request.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/src/sql.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/src/my_app.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/src/json.cpp
)

target_link_libraries(work_market web_request)

######################add libcurl libraries#########################

set(CURL_LIBRARY "-lcurl")

find_package(CURL REQUIRED)

if(CURL_FOUND)
    add_library(curl STATIC IMPORTED)
    add_definitions(-DCURL_STATICLIB)
    target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})
endif()

########################spdlog#####################################

set(spdlog_DIR "/home/libs/spdlog/build/")
find_package(spdlog REQUIRED)


add_library(spdlog STATIC IMPORTED)
#target_link_libraries(${PROJECT_NAME} spdlog::spdlog)
include_directories("/home/libs/spdlog/include")

####################################################################
                      ### SQL ###
                      
#target_link_libraries(${PROJECT_NAME} mysqlcppconn)


#Boost

find_package(Boost REQUIRED COMPONENTS headers)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
#target_link_libraries(${PROJECT_NAME} Boost::headers Threads::Threads OpenSSL::Crypto OpenSSL::SSL)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

#target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)