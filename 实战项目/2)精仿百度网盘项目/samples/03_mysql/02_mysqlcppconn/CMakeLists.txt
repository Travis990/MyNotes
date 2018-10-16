project(mysql_cpp_jdbc_test)
cmake_minimum_required(VERSION 3.2)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_CXX_STANDARD 11)
set(libs mysqlcppconn)

add_executable(jdbc_test ./jdbc_test.cpp)
target_link_libraries(jdbc_test ${libs})

