cmake_minimum_required(VERSION 2.8)
project( wn_wordnet )

include (GenerateExportHeader)

file(GLOB _headers "*.h")
file(GLOB _src "*.cpp")
set(SRC_FILES
            ${_headers}
            ${_src}
            CMakeLists.txt
            )


# Library - wn_wordnet
set(HEADERS   hyperonym_graph.h
              synset.h
              wordnet.h
              ) 

add_library(wn_wordnet ${SRC_FILES})
target_link_libraries(wn_wordnet ${Boost_LIBRARIES} ${WNB_LIBRARIES})
set_target_properties(wn_wordnet PROPERTIES DEBUG_POSTFIX d
                                             PUBLIC_HEADER "${HEADERS}"
                                             LINKER_LANGUAGE CXX
                                             FOLDER "libraries")
generate_export_header(wn_wordnet)


install(TARGETS wn_wordnet
  RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" COMPONENT bin
  LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" COMPONENT shlib
  ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" COMPONENT lib  
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_PREFIX}/include/wordnet"
  )
