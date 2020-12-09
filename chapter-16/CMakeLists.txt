# TO BUILD THS YOU MUST SET THE TARGET TO amd64

cmake_minimum_required(VERSION 3.16)
project(chapter_16 C CXX)

set(CMAKE_CXX_STANDARD 20)

set(PYTHON_SEARCH_PATH "C:\\Python27")
include_directories(C:\\Python27\\include)
include_directories(C:\\Python27\\Lib\\site-packages\\numpy\\core\\include)
LINK_DIRECTORIES(C:\\Python27\\libs)
add_definitions(-DMATPLOTLIBCPP_PYTHON_HEADER=Python.h)

include_directories(..\\common)
add_executable(predicted_premium_accounts.cpp predicted_premium_accounts.cpp)
