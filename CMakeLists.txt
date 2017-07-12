cmake_minimum_required(VERSION 3.7)
project(http_file_server)

set(CMAKE_CXX_STANDARD 14)

message("system: ${CMAKE_SYSTEM_PREFIX_PATH}")
list(APPEND CMAKE_PREFIX_PATH /usr/local)
find_package(Boost COMPONENTS log log_setup thread filesystem system)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

set(SOURCE_FILES src/main.cpp)
add_executable(http_file_server ${SOURCE_FILES})
target_link_libraries(http_file_server
        ${Boost_LOG_SETUP_LIBRARY}
        ${Boost_LOG_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_THREAD_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        )