cmake_minimum_required(VERSION 3.12) 
project(library VERSION 1.0.0 LANGUAGES CXX)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../../cmake")
include (prevent_source_builds)
include (clang_tidy)

add_library(${CMAKE_PROJECT_NAME} 
  Audio.h Audio.cpp
  Book.h Book.cpp
  Genre.h Genre.cpp
  Library.h Library.cpp
  LibraryItem.h LibraryItem.cpp
  Patron.h Patron.cpp
  Periodical.h Periodical.cpp
  Utility.h Utility.cpp
  Video.h Video.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME}
  PRIVATE 
    project_options
    project_warnings
)

add_executable(library main.cpp)

target_link_libraries(library ${CMAKE_PROJECT_NAME})

target_include_directories(${CMAKE_PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

file(COPY library_collections.txt 
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)

file(COPY library_patrons.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)