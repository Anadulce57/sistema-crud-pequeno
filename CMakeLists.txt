set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

cmake_minimum_required(VERSION 4.1)
project(crud)

set(CMAKE_CXX_STANDARD 20)

add_executable(crud main.cpp)

find_package(Drogon REQUIRED)
find_package(SQLite3 REQUIRED)

target_link_libraries(crud PRIVATE Drogon::Drogon SQLite::SQLite3)