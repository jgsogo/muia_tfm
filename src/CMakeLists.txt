cmake_minimum_required(VERSION 2.8)

project( muia_tfm )

# Common for all projects
#--------------------------
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Find BOOST
find_package(Boost COMPONENTS graph REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

# Find WNB library - http://www.cmake.org/Wiki/CMake:How_To_Find_Libraries
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../dependencies/wordnet-blast/")
find_package(Wnb REQUIRED)
include_directories(${WNB_INCLUDE_DIRS})
link_directories(${WNB_LIBRARY_DIRS})

include_directories(${CMAKE_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR})


# Libraries and executables
#--------------------------
add_subdirectory(distance)
add_subdirectory(ex_similarity)