set(BINARY ${CMAKE_PROJECT_NAME}_test)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

set(SOURCES ${TEST_SOURCES})

enable_testing()
add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED system random thread)
if (NOT Boost_FOUND)
    message("===Boost not existed, please install===")
    return()
else ()
    message("boost dirs: ${Boost_INCLUDE_DIRS}")
    message("boost libraries: ${Boost_LIBRARIES}")
endif()

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest gtest_main ${Boost_LIBRARIES})
include(GoogleTest)
gtest_discover_tests(${BINARY})
