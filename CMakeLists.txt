cmake_minimum_required(VERSION 3.26)

project(crypto_trading)
set(CMAKE_CXX_STANDARD 23)

include_directories(libs/rapidjson/include)
include_directories(src)

add_subdirectory(libs/googletest)
add_subdirectory(src)
add_subdirectory(test)
