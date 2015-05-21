cmake_minimum_required(VERSION 2.8)
project( wnb_similarity )


file(GLOB _headers "*.h")
file(GLOB _src "*.cpp")
set(SRC_FILES
            ${_headers}
            ${_src}
            CMakeLists.txt
            )

# Find BOOST
FIND_PACKAGE(Boost COMPONENTS graph REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

# Find WNB library - http://www.cmake.org/Wiki/CMake:How_To_Find_Libraries
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../dependencies/wordnet-blast/")
find_package(Wnb REQUIRED)

# Project example
include_directories(${WNB_INCLUDE_DIRS})

add_executable( wnb_similarity ${SRC_FILES})
set_property(TARGET wnb_similarity PROPERTY CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
target_link_libraries( wnb_similarity ${WNB_LIBRARIES} )

