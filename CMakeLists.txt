cmake_minimum_required(VERSION 3.22)

project(work_market VERSION 0.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDART 20)
set(CMAKE_SYSTEM_NAME Linux)

add_executable(
    work_market
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/web_request.cpp
)

include(ExternalProject)

ExternalProject_Add(
gtest
URL https://github.com/google/googletest/archive/master.zip
PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
# Disable install step
INSTALL_COMMAND ""
)

ExternalProject_Get_Property(gtest source_dir binary_dir)

add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

set_target_properties(libgtest PROPERTIES
   "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
   "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)

set_target_properties(libgmock PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

include_directories("${source_dir}/googletest/include"
                "${source_dir}/googlemock/include"
                "${source_dir}/src"
)

####################################################################
######################add libcurl libraries#########################

set(CURL_LIBRARY "-lcurl")

find_package(CURL REQUIRED)

if(CURL_FOUND)
    add_library(curl STATIC IMPORTED)
    add_definitions(-DCURL_STATICLIB)
    target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})
endif()

####################################################################
####################################################################

