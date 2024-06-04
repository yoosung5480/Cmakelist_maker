add_library(new_source1 new_source1.cpp)
target_compile_options(new_source1 PUBLIC -g -Wall)
target_include_directories(new_source1 PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(new_source1 new_main Decoder)
