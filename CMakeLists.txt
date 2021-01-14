cmake_minimum_required(VERSION 3.17)
project(Base64)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(googletest)
include_directories(src)
include_directories(googletest/googletest/include)
set(lib src/base64.cpp src/base64.h)
add_executable(Base64 main.cpp ${lib})
add_executable(GoogleTests tests.cpp ${lib})
target_link_libraries(GoogleTests gtest)