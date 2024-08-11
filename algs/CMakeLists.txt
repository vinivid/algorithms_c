add_library(algos sorting.c actors.c data_structures.c)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

target_include_directories(algos PRIVATE "${CMAKE_SOURCE_DIR}")

if(MSVC)
    target_compile_options(algos PRIVATE /W4)
else()
    target_compile_options(algos PRIVATE -Wall)
endif()