cmake_minimum_required(VERSION 3.16)
project(common C CXX)

set(CMAKE_CXX_STANDARD 20)
set(WITHOUT_NUMPY 1)

set(PYTHON_SEARCH_PATH "C:\\Python27")
include_directories(C:\\Python27\\include)
include_directories(C:\\Python27\\Lib)
set(Python_ADDITIONAL_VERSIONS 2.7)
find_package(PythonLibs REQUIRED)

add_library(common
        matplotlib.h
        vectormath.h
        matrixmath.h
        statistics.h
        probabilities.h
        gradient.h
        dimensionality_reduction.h
        machinelearning.h
        knn.h
        naive_bayes.h
        naive_bays_classifier.h
        linear_regression.h
        multiple_regression.h
        common.cpp)
