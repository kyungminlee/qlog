cmake_minimum_required(VERSION 3.0)
project(qlog VERSION 0.0 DESCRIPTION "logger")
set(CMAKE_CXX_STANDARD 14)

add_library(qlog SHARED src/qlog.cpp)
set_target_properties(qlog PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(qlog PROPERTIES SOVERSION 0)
set_target_properties(qlog PROPERTIES PUBLIC_HEADER "include/qlog.hpp;include/teestream.hpp")
target_include_directories(qlog PRIVATE include)
target_include_directories(qlog PRIVATE src)
include(GNUInstallDirs)
install(TARGETS qlog
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

add_executable(test test/test.cpp)
target_link_libraries(test qlog)
target_include_directories(test PRIVATE include)
target_include_directories(test PRIVATE src)
add_test(NAME test COMMAND test)

# https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake