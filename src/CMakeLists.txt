set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES ${SOURCES})

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED system random thread)
if (NOT Boost_FOUND)
    message("===Boost not existed, please install===")
    return()
else ()
    message("boost dirs: ${Boost_INCLUDE_DIRS}")
    message("boost libraries: ${Boost_LIBRARIES}")
endif()

find_package(OpenSSL REQUIRED)

add_executable(${BINARY}_run ${SOURCES})

add_library(${BINARY}_lib STATIC ${SOURCES})

target_link_libraries(${BINARY}_run PUBLIC ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})
target_link_libraries(${BINARY}_lib PUBLIC ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})