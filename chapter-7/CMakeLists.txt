# TO BUILD THS YOU MUST SET THE TARGET TO amd64

cmake_minimum_required(VERSION 3.16)
project(chapter_6 C CXX)

set(CMAKE_CXX_STANDARD 20)

set(PYTHON_SEARCH_PATH "C:\\Python27")
include_directories(C:\\Python27\\include)
include_directories(C:\\Python27\\Lib\\site-packages\\numpy\\core\\include)
LINK_DIRECTORIES(C:\\Python27\\libs)
add_definitions(-DMATPLOTLIBCPP_PYTHON_HEADER=Python.h)

include_directories(..\\common)
add_executable(probabilities_test probabilities_test.cpp)
add_executable(bayesian_distribution_test bayesian_distribution_test.cpp)
add_executable(bayesian_posterior_test bayesian_posterior_test.cpp)
