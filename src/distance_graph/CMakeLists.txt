cmake_minimum_required(VERSION 2.8)
project( wn_distance_graph )

include (GenerateExportHeader)

file(GLOB _headers "*.h")
file(GLOB _src "*.cpp")
set(SRC_FILES
            ${_headers}
            ${_src}
            CMakeLists.txt
            )


# Library - wn_distance_graph
set(HEADERS   graph_distance.h
              )

add_library(wn_distance_graph ${SRC_FILES})
target_link_libraries(wn_distance_graph ${Boost_LIBRARIES} ${WNB_LIBRARIES} wn_conceptual_graph)
set_target_properties(wn_distance_graph PROPERTIES DEBUG_POSTFIX d
                                             PUBLIC_HEADER "${HEADERS}"
                                             LINKER_LANGUAGE CXX
                                             FOLDER "libraries")
generate_export_header(wn_distance_graph)


install(TARGETS wn_distance_graph
  RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" COMPONENT bin
  LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" COMPONENT shlib
  ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" COMPONENT lib
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_PREFIX}/include/distance_graph"
  )
