cmake_minimum_required(VERSION 2.8)
project( ex_conceptual_graph )


file(GLOB _headers "*.h")
file(GLOB _src "*.cpp")
set(SRC_FILES
            ${_headers}
            ${_src}
            CMakeLists.txt
            )

# Dependencies

# Project example
add_executable( ex_conceptual_graph ${SRC_FILES})
set_property(TARGET ex_conceptual_graph PROPERTY CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
target_link_libraries(ex_conceptual_graph ${Boost_LIBRARIES} ${WNB_LIBRARIES} wn_conceptual_graph)
set_target_properties(ex_conceptual_graph PROPERTIES DEBUG_POSTFIX d
                                               LINKER_LANGUAGE CXX
                                               FOLDER "examples")

install(TARGETS ex_conceptual_graph
  RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" COMPONENT bin
  LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" COMPONENT shlib
  ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" COMPONENT lib
  )
