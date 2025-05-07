cmake_minimum_required(VERSION 3.26)

project(crypto_trading LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)

include_directories(libs/rapidjson/include)
include_directories(src)

add_subdirectory(libs/googletest)
add_subdirectory(src)
add_subdirectory(test)


#file(COPY ${CMAKE_SOURCE_DIR}/python/
#     DESTINATION ${CMAKE_BINARY_DIR}/python
#     FILES_MATCHING PATTERN "*.py")

#file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/mmap)