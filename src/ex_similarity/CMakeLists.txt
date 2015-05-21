cmake_minimum_required(VERSION 2.8)
project( ex_similarity )


file(GLOB _headers "*.h")
file(GLOB _src "*.cpp")
set(SRC_FILES
            ${_headers}
            ${_src}
            CMakeLists.txt
            )

# Dependencies
include_directories(${wn_distance_INCLUDE_DIR})

# Project example
add_executable( ex_similarity ${SRC_FILES})
set_property(TARGET ex_similarity PROPERTY CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
target_link_libraries(ex_similarity ${WNB_LIBRARIES} wn_distance wn_wordnet )
set_target_properties(ex_similarity PROPERTIES DEBUG_POSTFIX d
                                               LINKER_LANGUAGE CXX
                                               FOLDER "examples")

install(TARGETS ex_similarity
  RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" COMPONENT bin
  LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" COMPONENT shlib
  ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" COMPONENT lib  
  )
