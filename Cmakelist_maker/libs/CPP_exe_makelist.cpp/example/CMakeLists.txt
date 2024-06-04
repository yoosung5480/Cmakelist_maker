# main
   cmake_minimum_required(VERSION 3.10)
   set(CMAKE_CXX_STANDARD 17)
   set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
   add_subdirectory( lib )
   add_executable( new_main new_main.cpp )
   target_link_libraries(new_main new_main)
   target_include_directories( new_main PUBLIC "${PROJECT_SOURCE_DIR}/include" )
   set_target_properties( new_main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
