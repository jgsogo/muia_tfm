cmake_minimum_required(VERSION 2.8)
project( wnb_similarity )


file(GLOB _headers "*.h")
file(GLOB _src "*.cpp")
set(SRC_FILES
            ${_headers}
            ${_src}
	    CMakeLists.txt
            )

# WNB library
set(wnb_LIBS "/home/javi/Programing/muia_tfm/dependencies/wordnet-blast/lib/libwnb.a")
set(wnb_SOURCE_DIRS "../../dependencies/wordnet-blast")

include_directories(${wnb_SOURCE_DIRS})

add_executable( wnb_similarity ${SRC_FILES})
set_property(TARGET wnb_similarity PROPERTY CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
target_link_libraries( wnb_similarity ${wnb_LIBS} )

