cmake_minimum_required(VERSION 2.8)
project( wn_distance )

include (GenerateExportHeader)

file(GLOB _headers "*.h")
file(GLOB _src "*.cpp")
set(SRC_FILES
            ${_headers}
            ${_src}
            CMakeLists.txt
            )


# Library - wn_distance
set(HEADERS   distance.h
              synset.h
              ) 

add_library(wn_distance ${SRC_FILES})
target_link_libraries(wn_distance ${Boost_LIBRARIES} ${WNB_LIBRARIES})
set_target_properties(wn_distance PROPERTIES DEBUG_POSTFIX d
                                             PUBLIC_HEADER "${HEADERS}"
                                             LINKER_LANGUAGE CXX
                                             FOLDER "libraries")
generate_export_header(wn_distance)


install(TARGETS wn_distance
  RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" COMPONENT bin
  LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" COMPONENT shlib
  ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" COMPONENT lib  
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_PREFIX}/include/distance"
  )
