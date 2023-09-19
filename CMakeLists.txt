# Need CMake 3.20
cmake_minimum_required (VERSION 3.20)

# The name of the repository
project ("sync")

# Set the correct paths
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/extern/)

# Set compiler warnings
if(MSVC)
    # TODO
else()

    # For clang
    #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lrt -std=gnu99 -Wall -Wextra -Wpedantic -Weverything -Wno-declaration-after-statement -Ofast")

    # For GCC
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -Wall -Wextra -Wpedantic -Wno-declaration-after-statement -O3")
    add_compile_definitions(__USE_POSIX199309)
endif()

# Comment out for Debug mode
set(IS_DEBUG_BUILD CMAKE_BUILD_TYPE STREQUAL "Debug")

# Set debug mode
if (${IS_DEBUG_BUILD})
    add_compile_definitions(NDEBUG)
endif()

# Add the sync project
if ( NOT "${HAS_SYNC}")

    # Log
    message("[sync] Adding sync project")

    # Let any parent project know that it has the sync project
    set(HAS_SYNC CACHE true PARENT_SCOPE)
endif()

# Add source to the executable
add_executable(sync_example "sync.c" "main.c")
target_include_directories(sync_example PUBLIC include include/sync/)

# Add source to the library
add_library(sync SHARED "sync.c")
target_include_directories(sync PUBLIC include include/sync/)