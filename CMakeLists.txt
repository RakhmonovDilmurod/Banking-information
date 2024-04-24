cmake_minimum_required(VERSION 3.8)
project("Bank")

set(CMAKE_CXX_STANDARD 20)
include(FetchContent)

add_executable(main main.cpp)
target_link_libraries(main nlohmann_json::nlohmann_json)
add_subdirectory(nlohmann_json)
