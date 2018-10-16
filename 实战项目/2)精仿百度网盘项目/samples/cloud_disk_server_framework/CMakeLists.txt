project(itcast_cloud_disk_fastcgi)
cmake_minimum_required(VERSION 3.2)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin_cgi)

#让rapid json 支持std::string
add_definitions(-DRAPIDJSON_HAS_STDSTRING)
#不要让rapidjson 产生一些测试程序
SET(RAPIDJSON_BUILD_EXAMPLES OFF CACHE BOOL "Disable rapid json examples" FORCE)
SET(RAPIDJSON_BUILD_TESTS OFF CACHE BOOL "Disable rapid json tests" FORCE)
SET(RAPIDJSON_BUILD_DOC OFF CACHE BOOL "Disable rapid json doc" FORCE)

#添加rapidjson 的子目录
add_subdirectory(./dependencies/rapidjson/)

#设置可执行程序输出目录
SET(EXECUTABLE_OUTPUT_PATH ./bin_cgi)
#设置使用C++11
set(CMAKE_CXX_STANDARD 11)

link_directories(${CMAKE_BINARY_DIR}/dependencies/mysql-connector-cpp/jdbc/install/lib)
set(libs fdfsclient fastcommon fcgi++ fcgi mysqlcppconn hiredis)

include_directories(
    ./include
    ./dependencies/rapidjson/include
    /usr/include/fastdfs
    /usr/include/fastcommon
    /usr/local/include/hiredis
)
file(GLOB itcast_libs_src ./common/*.cpp)
add_library(itcast_fastcgi ${itcast_libs_src})

#cgi可执行程序目标
add_executable(login ./src_cgi/login_cgi.cpp)
add_executable(register ./src_cgi/register_cgi.cpp)
add_executable(myfiles ./src_cgi/myfiles_cgi.cpp)
add_executable(md5 ./src_cgi/md5_cgi.cpp)
add_executable(upload ./src_cgi/upload_cgi.cpp)
add_executable(dealfile ./src_cgi/dealfile_cgi.cpp)
add_executable(sharefiles ./src_cgi/sharefiles_cgi.cpp)
add_executable(dealsharefile ./src_cgi/dealsharefile_cgi.cpp)

#连接库
target_link_libraries(register itcast_fastcgi ${libs})
target_link_libraries(login itcast_fastcgi ${libs})
target_link_libraries(myfiles itcast_fastcgi ${libs})
target_link_libraries(md5 itcast_fastcgi ${libs})
target_link_libraries(upload itcast_fastcgi ${libs})
target_link_libraries(dealfile itcast_fastcgi ${libs})
target_link_libraries(sharefiles itcast_fastcgi ${libs})
target_link_libraries(dealsharefile itcast_fastcgi ${libs})


#测试模块
add_executable(testFastCGIApplication ./test/testFastCGIApplication.cpp)
target_link_libraries(testFastCGIApplication itcast_fastcgi ${libs})
