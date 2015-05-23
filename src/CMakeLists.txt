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

# Find xml_parser
find_package(xml_parser REQUIRED)


# Needed include directories
include_directories(${CMAKE_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Libraries and executables
#--------------------------
add_subdirectory(distance)
add_subdirectory(wordnet)
add_subdirectory(corpus)

option(BUILD_EXAMPLES "Build examples" ON)
if (BUILD_EXAMPLES)
    add_subdirectory(ex_similarity)
    add_subdirectory(ex_semcor)
endif(BUILD_EXAMPLES)


# Data
#------------------------
option(DOWNLOAD_WORDNET "Download WordNet 3.1" OFF)
if(DOWNLOAD_WORDNET)
    if(IS_DIRECTORY "${CMAKE_INSTALL_PREFIX}/data/wordnet3.1")
              message(STATUS "WordNet 3.1 is already on disk")
    else()
              message(STATUS "Downloading WordNet 3.1 database to ${CMAKE_INSTALL_PREFIX}/data/wordnet3.1")
              file(DOWNLOAD http://wordnetcode.princeton.edu/wn3.1.dict.tar.gz ${CMAKE_INSTALL_PREFIX}/data/wordnet3.1/wn3.1.dict.tar.gz                            SHOW_PROGRESS)
              
              message(STATUS "Uncompressing database...")
              execute_process(COMMAND ${CMAKE_COMMAND} -E tar xvzf ${CMAKE_INSTALL_PREFIX}/data/wordnet3.1/wn3.1.dict.tar.gz
                            WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/data/wordnet3.1)

    endif()
endif()

# We use SemCor from NLTK because it is in XML format (http://www.nltk.org/nltk_data/) not like the Mihaela one (http://web.eecs.umich.edu/~mihalcea/)
option(DOWNLOAD_SEMCOR "Download SemCor from NLTK" OFF)
if(DOWNLOAD_SEMCOR)
    set(SEMCOR_DIR "${CMAKE_INSTALL_PREFIX}/data")
    if(IS_DIRECTORY ${SEMCOR_DIR}/semcor3.0)
              message(STATUS "SemCor is already on disk (${SEMCOR_DIR}/semcor)")
    else()
              message(STATUS "Downloading SemCor NLTK database to ${SEMCOR_DIR}")
              file(DOWNLOAD http://www.nltk.org/nltk_data/packages/corpora/semcor.zip ${SEMCOR_DIR}/semcor.zip                            SHOW_PROGRESS)
              
              message(STATUS "Uncompressing database...")
              execute_process(COMMAND ${CMAKE_COMMAND} -E tar xvzf ${SEMCOR_DIR}/semcor.zip
                            WORKING_DIRECTORY ${SEMCOR_DIR})

    endif()
endif()

option(DOWNLOAD_BROWN "Download Brown Corpus" OFF)
if(DOWNLOAD_BROWN)
    set(BROWN_DIR "${CMAKE_INSTALL_PREFIX}/data")
    if(IS_DIRECTORY ${BROWN_DIR}/brown)
              message(STATUS "Brown Corpus is already on disk (${BROWN_DIR}/brown)")
    else()
              message(STATUS "Downloading Brown Corpus database to ${BROWN_DIR}")
              file(DOWNLOAD http://www.nltk.org/nltk_data/packages/corpora/brown.zip ${BROWN_DIR}/brown.zip                            SHOW_PROGRESS)
              
              message(STATUS "Uncompressing database...")
              execute_process(COMMAND ${CMAKE_COMMAND} -E tar xvzf ${BROWN_DIR}/brown.zip
                            WORKING_DIRECTORY ${BROWN_DIR})

    endif()
endif()

