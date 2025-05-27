set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "*.h" "*.hpp" "*.cpp")
list(FILTER SOURCES EXCLUDE REGEX "cppTrading.cpp|pythonTrading.cpp|ticker.cpp|TradingSystem.cpp")

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

#set(PYBIND11_FINDPYTHON ON)
#find_package(Python 3.12 REQUIRED COMPONENTS Interpreter Development.Module)
find_package(pybind11 CONFIG REQUIRED)
pybind11_add_module(trading pyInterface/mmapQueue.cpp)
install(TARGETS trading DESTINATION liuyang)

add_library(${BINARY}_lib STATIC ${SOURCES})
add_executable(${BINARY}_cpp_trading ${SOURCES} TradingSystem.cpp)
add_executable(${BINARY}_ticker ${SOURCES} ticker.cpp)

target_link_libraries(${BINARY}_cpp_trading PRIVATE ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})
target_link_libraries(${BINARY}_ticker PRIVATE ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})

target_link_libraries(${BINARY}_lib PRIVATE ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})