cmake_minimum_required(VERSION 3.14)
project(CPP11HF2)

set(CMAKE_CXX_STANDARD 17)

add_executable(CPP11HF2 main.cpp GameManager.cpp GameManager.h GameDatabase.cpp GameDatabase.h GameDisplay.cpp GameDisplay.h)