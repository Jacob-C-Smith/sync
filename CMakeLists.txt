﻿# Need CMake 3.16.0
cmake_minimum_required (VERSION 3.16.0)

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
    #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lrt -std=gnu99 -Wall -Wextra  -Weverything -Wno-declaration-after-statement -Ofast")

    # For GCC
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -Wall -Wextra -O3 -pthread -lpthread")
    add_compile_definitions(__USE_POSIX199309)
    add_compile_options(-Wall -Wextra -Wpointer-arith -Wstrict-prototypes -Wformat-security -Wfloat-equal -Wshadow -Wconversion -pthread -lpthread -Wlogical-not-parentheses -Wnull-dereference)
endif()

# Comment out for Debug mode
set(IS_DEBUG_BUILD CMAKE_BUILD_TYPE STREQUAL "Debug")

# Build sync with timer
add_compile_definitions(BUILD_SYNC_WITH_TIMER)

# Build sync with mutex
add_compile_definitions(BUILD_SYNC_WITH_MUTEX)

# Build sync with spinlock
add_compile_definitions(BUILD_SYNC_WITH_SPINLOCK)

# Build sync with rwlock
add_compile_definitions(BUILD_SYNC_WITH_RW_LOCK)

# Build sync with semaphore
add_compile_definitions(BUILD_SYNC_WITH_SEMAPHORE)

# Build sync with condition variable
add_compile_definitions(BUILD_SYNC_WITH_CONDITION_VARIABLE)

# Build sync with monitor
add_compile_definitions(BUILD_SYNC_WITH_MONITOR)

# Build sync with barrier
add_compile_definitions(BUILD_SYNC_WITH_BARRIER)

# Build sync with debug
#add_compile_definitions(SYNC_DEBUG)

# Set debug mode
if (${IS_DEBUG_BUILD})
    add_compile_definitions(NDEBUG)
endif()

# Find the log module
if ( NOT "${HAS_LOG}")

    # Add the log directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/log ${CMAKE_SOURCE_DIR}/build/log)

    # Let any parent project know that this project has log
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_LOG true PARENT_SCOPE)
        set(LOG_INCLUDE_DIR ${LOG_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Add the sync project
if ( NOT "${HAS_SYNC}")

    # Log
    message("[sync] Adding sync project")
    
    set(SYNC_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

    # Let any parent project know that it has the sync project
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_SYNC true PARENT_SCOPE)
        set(SYNC_INCLUDE_DIR ${SYNC_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Add source to the executable
add_executable(sync_example "main.c")
add_dependencies(sync_example sync log)
target_include_directories(sync_example PUBLIC ${SYNC_INCLUDE_DIR} ${LOG_INCLUDE_DIR})
target_link_libraries(sync_example sync log pthread)

# Mac already includes rt, so its not needed on Mac
if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	target_link_libraries(sync_example rt)
endif()

# Add source to the library
add_library(sync SHARED "sync.c")
add_dependencies(sync log)
target_include_directories(sync PUBLIC ${SYNC_INCLUDE_DIR} ${LOG_INCLUDE_DIR})
target_link_libraries(sync log pthread)

# Mac already includes rt, so its not needed on Mac
if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	target_link_libraries(sync rt)
endif()

