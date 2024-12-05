cmake_minimum_required(VERSION 3.5)
project(crypto_trading)
set(CMAKE_CXX_STANDARD 23)

include_directories(src)
# import google test
add_subdirectory(libs/googletest)
add_subdirectory(src)
add_subdirectory(test)