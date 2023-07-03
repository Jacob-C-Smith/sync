cmake_minimum_required (VERSION 3.26)

project ("sync")

# Comment out for Debug mode
set(IS_DEBUG_BUILD CMAKE_BUILD_TYPE STREQUAL "Debug")
if ( NOT "${HAS_SYNC}")
    message("[sync] Adding sync project")
    set(HAS_STACK true PARENT_SCOPE)
endif()

if (${IS_DEBUG_BUILD})
    add_compile_definitions(NDEBUG)
endif()

# Add source to the executable
add_executable(sync_example "sync.c" "main.c")
target_include_directories(sync_example PUBLIC "include" include/sync/)

# Add source to the library
add_library(sync SHARED "sync.c")
target_include_directories(sync PUBLIC "include" include/sync/)