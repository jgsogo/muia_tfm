cmake_minimum_required(VERSION 2.8)
project( wn_conceptual_graph )

include (GenerateExportHeader)

file(GLOB _headers "*.h")
file(GLOB _src "*.cpp")
set(SRC_FILES
            ${_headers}
            ${_src}
            CMakeLists.txt
            )


# Library - wn_conceptual_graph
set(HEADERS   conceptual_graph.h
              )

add_library(wn_conceptual_graph ${SRC_FILES})
target_link_libraries(wn_conceptual_graph ${Boost_LIBRARIES})
set_target_properties(wn_conceptual_graph PROPERTIES DEBUG_POSTFIX d
                                             PUBLIC_HEADER "${HEADERS}"
                                             LINKER_LANGUAGE CXX
                                             FOLDER "libraries")
generate_export_header(wn_conceptual_graph)


install(TARGETS wn_conceptual_graph
  RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" COMPONENT bin
  LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" COMPONENT shlib
  ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" COMPONENT lib
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_PREFIX}/include/conceptual_graph"
  )
