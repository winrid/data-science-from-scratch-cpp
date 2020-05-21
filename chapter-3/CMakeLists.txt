# TO BUILD THS YOU MUST SET THE TARGET TO amd64

cmake_minimum_required(VERSION 3.16)
project(chapter_3 C CXX)

set(CMAKE_CXX_STANDARD 20)

set(PYTHON_SEARCH_PATH "C:\\Python27")
include_directories(C:\\Python27\\include)
include_directories(C:\\Python27\\Lib\\site-packages\\numpy\\core\\include)
LINK_DIRECTORIES(C:\\Python27\\libs)
add_definitions(-DMATPLOTLIBCPP_PYTHON_HEADER=Python.h)

# does not seem like we need these w/ include_directories above?
#set(Python_ADDITIONAL_VERSIONS 2.7)
#find_package(PythonLibs REQUIRED)

include_directories(..\\common)
add_executable(simple-plot simple-plot.cpp)
add_executable(simple-bar simple-bar.cpp)
