cmake_minimum_required(VERSION 3.26)

project(E-LearningSystem)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# treat warnings as errors
add_compile_options(-Wall -Werror -Wno-sign-compare -Wno-unused-variable -Wno-unused-function -Wno-infinite-recursion)

add_executable(driverMain driverMain.cpp functions.cpp)


