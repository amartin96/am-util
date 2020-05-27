cmake_minimum_required(VERSION 3.13)
project(AMUtil)
set(CMAKE_CXX_STANDARD 20)

add_library(AMUtil)
target_include_directories(AMUtil PUBLIC include)

add_subdirectory(src)
