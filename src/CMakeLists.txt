add_library(web_request web_request.cpp)

target_include_directories(web_request PUBLIC include)

set(spdlog_DIR "/home/libs/spdlog/build/")
find_package(spdlog REQUIRED)


add_library(spdlog STATIC IMPORTED)
target_link_libraries(web_request spdlog::spdlog)
include_directories(${spdlog_DIR})

set(CURL_LIBRARY "-lcurl")

find_package(CURL REQUIRED)

if(CURL_FOUND)
    add_library(curl STATIC IMPORTED)
    add_definitions(-DCURL_STATICLIB)
    target_link_libraries(web_request ${CURL_LIBRARIES})
endif()

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(web_request nlohmann_json::nlohmann_json)

add_library(vacansy vacansy.cpp)

add_library(request_parser request_parser.cpp)

target_link_libraries(web_request request_parser)

target_link_libraries(request_parser nlohmann_json::nlohmann_json)
target_link_libraries(request_parser spdlog::spdlog)

target_include_directories(request_parser PUBLIC include)