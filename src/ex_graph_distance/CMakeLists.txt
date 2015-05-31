cmake_minimum_required(VERSION 2.8)
project( ex_graph_distance )


file(GLOB _headers "*.h")
file(GLOB _src "*.cpp")
set(SRC_FILES
            ${_headers}
            ${_src}
            CMakeLists.txt
            )

# Dependencies

# Project example
add_executable( ex_graph_distance ${SRC_FILES})
set_property(TARGET ex_graph_distance PROPERTY CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
target_link_libraries(ex_graph_distance ${Boost_LIBRARIES} ${WNB_LIBRARIES} wn_corpus wn_wordnet wn_distance_synset wn_conceptual_graph wn_distance_graph)
set_target_properties(ex_graph_distance PROPERTIES DEBUG_POSTFIX d
                                               LINKER_LANGUAGE CXX
                                               FOLDER "examples")

install(TARGETS ex_graph_distance
  RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" COMPONENT bin
  LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" COMPONENT shlib
  ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" COMPONENT lib
  )
