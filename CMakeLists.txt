cmake_minimum_required(VERSION 3.22)

project(ControlThread LANGUAGES CXX)

add_executable(controlthread controlthread.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(controlthread PUBLIC Threads::Threads)
