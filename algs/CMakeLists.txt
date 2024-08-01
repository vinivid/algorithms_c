add_library(algos sorting.c actors.c data_structures.c)

target_include_directories(algos PRIVATE "${CMAKE_SOURCE_DIR}")