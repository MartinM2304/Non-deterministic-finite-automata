cmake_minimum_required(VERSION 3.24)
project(NDFA04)

set(CMAKE_CXX_STANDARD 17)

add_executable(NDFA04 main.cpp MyString.cpp MyVector.hpp MySet.hpp Automata.cpp Automata.h Transition.hpp State.cpp State.h)
