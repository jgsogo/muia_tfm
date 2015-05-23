cmake_minimum_required(VERSION 2.8)
project( ex_corpus )


file(GLOB _headers "*.h")
file(GLOB _src "*.cpp")
set(SRC_FILES
            ${_headers}
            ${_src}
            CMakeLists.txt
            )

# Dependencies
include_directories(${wn_corpus_INCLUDE_DIR})

# Project example
add_executable( ex_corpus ${SRC_FILES})
set_property(TARGET ex_corpus PROPERTY CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
target_link_libraries(ex_corpus ${Boost_LIBRARIES} ${WNB_LIBRARIES} wn_wordnet wn_corpus)
set_target_properties(ex_corpus PROPERTIES DEBUG_POSTFIX d
                                               LINKER_LANGUAGE CXX
                                               FOLDER "examples")

install(TARGETS ex_corpus
  RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" COMPONENT bin
  LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" COMPONENT shlib
  ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" COMPONENT lib
  )
