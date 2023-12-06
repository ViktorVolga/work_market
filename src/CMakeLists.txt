add_library(web_request web_request.cpp)

target_include_directories(web_request PUBLIC include)

set(spdlog_DIR "/home/libs/spdlog/build/")
find_package(spdlog REQUIRED)


add_library(spdlog STATIC IMPORTED)
target_link_libraries(web_request spdlog::spdlog)
include_directories(${spdlog_DIR})