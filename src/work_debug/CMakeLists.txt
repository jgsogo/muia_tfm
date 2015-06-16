cmake_minimum_required(VERSION 2.8)
project( work_debug )


file(GLOB _headers "*.h")
file(GLOB _src "*.cpp")
set(SRC_FILES
            ${_headers}
            ${_src}
            ../work_sample/sample_file.h
            ../work_sample/sample_file.cpp
            ../work_sample/utils.h
            CMakeLists.txt
            )

add_executable( work_debug ${SRC_FILES})
# Project example
set_property(TARGET work_debug PROPERTY CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
target_link_libraries(work_debug ${Boost_LIBRARIES} ${WNB_LIBRARIES} wn_corpus wn_wordnet wn_distance_synset wn_conceptual_graph wn_distance_graph wn_distance_relation)
set_target_properties(work_debug PROPERTIES DEBUG_POSTFIX d
                                               LINKER_LANGUAGE CXX
                                               FOLDER "work")

install(TARGETS work_debug
  RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" COMPONENT bin
  LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" COMPONENT shlib
  ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" COMPONENT lib
  )
