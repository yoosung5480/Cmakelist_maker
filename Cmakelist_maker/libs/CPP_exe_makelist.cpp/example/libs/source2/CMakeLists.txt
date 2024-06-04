add_library(source2 source2.cpp)
target_compile_options(source2 PUBLIC -g -Wall)
target_include_directories(source2 PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(source2 new_main Decoder)
