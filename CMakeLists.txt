cmake_minimum_required(VERSION 4.1)
project(Proiect_POO)

set(CMAKE_CXX_STANDARD 20)

add_executable(Proiect_POO main.cpp
        Turist.cpp
        Hotel.cpp
        Zbor.cpp
)

add_executable(turist Turist.cpp)

add_executable(hotel Hotel.cpp
        Zbor.h
        Zbor.cpp)
