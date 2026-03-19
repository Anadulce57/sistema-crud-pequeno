cmake_minimum_required(VERSION 4.1)
project(crud)

set(CMAKE_CXX_STANDARD 20)

add_executable(crud main.cpp)

find_package(Drogon CONFIG REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)

target_link_libraries(crud PRIVATE Drogon::Drogon unofficial::sqlite3::sqlite3)