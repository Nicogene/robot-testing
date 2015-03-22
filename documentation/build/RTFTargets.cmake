# Generated by CMake 2.8.12.2

if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.5)
   message(FATAL_ERROR "CMake >= 2.6.0 required")
endif()
cmake_policy(PUSH)
cmake_policy(VERSION 2.6)
#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Protect against multiple inclusion, which would fail when already imported targets are added once more.
set(_targetsDefined)
set(_targetsNotDefined)
set(_expectedTargets)
foreach(_expectedTarget RTF::RTF RTF::RTF_dll)
  list(APPEND _expectedTargets ${_expectedTarget})
  if(NOT TARGET ${_expectedTarget})
    list(APPEND _targetsNotDefined ${_expectedTarget})
  endif()
  if(TARGET ${_expectedTarget})
    list(APPEND _targetsDefined ${_expectedTarget})
  endif()
endforeach()
if("${_targetsDefined}" STREQUAL "${_expectedTargets}")
  set(CMAKE_IMPORT_FILE_VERSION)
  cmake_policy(POP)
  return()
endif()
if(NOT "${_targetsDefined}" STREQUAL "")
  message(FATAL_ERROR "Some (but not all) targets in this export set were already defined.\nTargets Defined: ${_targetsDefined}\nTargets not yet defined: ${_targetsNotDefined}\n")
endif()
unset(_targetsDefined)
unset(_targetsNotDefined)
unset(_expectedTargets)


# Create imported target RTF::RTF
add_library(RTF::RTF SHARED IMPORTED)

# Create imported target RTF::RTF_dll
add_library(RTF::RTF_dll SHARED IMPORTED)

# Import target "RTF::RTF" for configuration ""
set_property(TARGET RTF::RTF APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(RTF::RTF PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "/home/apaikan/Install/robotology/robot-testing/build/lib/libRTF.so"
  IMPORTED_SONAME_NOCONFIG "libRTF.so"
  )

# Import target "RTF::RTF_dll" for configuration ""
set_property(TARGET RTF::RTF_dll APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(RTF::RTF_dll PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_NOCONFIG "dl"
  IMPORTED_LOCATION_NOCONFIG "/home/apaikan/Install/robotology/robot-testing/build/lib/libRTF_dll.so"
  IMPORTED_SONAME_NOCONFIG "libRTF_dll.so"
  )

# This file does not depend on other imported targets which have
# been exported from the same project but in a separate export set.

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
cmake_policy(POP)
