add_library(request_handler request_parser.cpp web_request.cpp request_handler.cpp)

target_include_directories(request_handler PUBLIC include)

set(spdlog_DIR "/home/libs/spdlog/build/")
find_package(spdlog REQUIRED)


add_library(spdlog SHARED IMPORTED)
target_link_libraries(request_handler spdlog::spdlog)
include_directories(${spdlog_DIR})

set(CURL_LIBRARY "-lcurl")

find_package(CURL REQUIRED)

if(CURL_FOUND)
    add_library(curl STATIC IMPORTED)
    add_definitions(-DCURL_STATICLIB)
    target_link_libraries(request_handler ${CURL_LIBRARIES})
endif()

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(request_handler nlohmann_json::nlohmann_json)

add_library(vacansy vacansy.cpp vacansy_handler.cpp)
target_include_directories(vacansy PUBLIC include)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.82 COMPONENTS program_options) 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_library(intro intro.cpp) 
    target_link_libraries(intro ${Boost_LIBRARIES})
endif()