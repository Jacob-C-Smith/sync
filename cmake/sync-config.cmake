# SYNC CMake configuration file:
# This file is meant to be placed in a cmake subfolder of SYNC-devel-2.x.y-VC

cmake_minimum_required(VERSION 3.0)

include(FeatureSummary)
set_package_properties(SYNC PROPERTIES
    URL "https://www.g10.app/status"
    DESCRIPTION "sync"
)

# Copied from `configure_package_config_file`
macro(set_and_check _var _file)
    set(${_var} "${_file}")
    if(NOT EXISTS "${_file}")
        message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
    endif()
endmacro()

# Copied from `configure_package_config_file`
macro(check_required_components _NAME)
    foreach(comp ${${_NAME}_FIND_COMPONENTS})
        if(NOT ${_NAME}_${comp}_FOUND)
            if(${_NAME}_FIND_REQUIRED_${comp})
                set(${_NAME}_FOUND FALSE)
            endif()
        endif()
    endforeach()
endmacro()

set(SYNC_FOUND TRUE)

# For compatibility with autotools SYNC-config.cmake, provide SYNC_* variables.

set_and_check(SYNC_PREFIX       "${CMAKE_CURRENT_LIST_DIR}/..")
set_and_check(SYNC_EXEC_PREFIX  "${CMAKE_CURRENT_LIST_DIR}/..")
set_and_check(SYNC_INCLUDE_DIR  "${SYNC_PREFIX}/include")
set(SYNC_INCLUDE_DIRS           "${SYNC_INCLUDE_DIR}")
set_and_check(SYNC_BINDIR       "${CMAKE_CURRENT_LIST_DIR}/../build/Debug/")
set_and_check(SYNC_LIBDIR       "${CMAKE_CURRENT_LIST_DIR}/../build/Debug/")

set(SYNC_LIBRARIES sync::sync)

# All targets are created, even when some might not be requested though COMPONENTS.
# This is done for compatibility with CMake generated SYNC-target.cmake files.

set(_SYNC_library     "${SYNC_LIBDIR}/sync.lib")
set(_SYNC_dll_library "${SYNC_BINDIR}/sync.dll")
if(EXISTS "${_SYNC_library}" AND EXISTS "${_SYNC_dll_library}")
    if(NOT TARGET sync::sync)
        add_library(sync::sync SHARED IMPORTED)
        set_target_properties(sync::sync
            PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${SYNC_INCLUDE_DIRS}"
                IMPORTED_IMPLIB "${_SYNC_library}"
                IMPORTED_LOCATION "${_SYNC_dll_library}"
                COMPATIBLE_INTERFACE_BOOL "SYNC_SHARED"
                INTERFACE_SYNC_SHARED "ON"
        )
    endif()
    set(SYNC_SYNC_FOUND TRUE)
else()
    set(SYNC_SYNC_FOUND FALSE)
endif()
unset(_SYNC_library)
unset(_SYNC_dll_library)

check_required_components(SYNC)
