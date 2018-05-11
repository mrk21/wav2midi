cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)
project(wav2midi)

# -----------------------------------------------------------------------------
# options
# -----------------------------------------------------------------------------
option(BUILD_TEST "Whether to build the tests" OFF)

# -----------------------------------------------------------------------------
# compiler settings
# -----------------------------------------------------------------------------
if(CMAKE_CXX_COMPILER_ID STREQUAL Clang)
  if(CMAKE_CXX_COMPILER_VERSION LESS 5.0)
    message(FATAL_ERROR "A supported Clang version is greater than or equal to 5.0!")
  endif()

  add_compile_options(-std=c++17 -stdlib=libc++ -Wall -Wextra)
  set(CMAKE_EXE_LINKER_FLAGS -stdlib=libc++)
  set(VENDOR_CXX_FLAGS -stdlib=libc++)

elseif(CMAKE_CXX_COMPILER_ID STREQUAL GNU)
  if(CMAKE_CXX_COMPILER_VERSION LESS 7.0)
    message(FATAL_ERROR "A supported GCC version is greater than or equal to 7.0!")
  endif()

  add_compile_options(-std=c++17 -Wall -Wextra)
else()
  message(FATAL_ERROR "Unsupported compiler!")
endif()

# -----------------------------------------------------------------------------
# init submodules
# -----------------------------------------------------------------------------
execute_process(COMMAND git submodule update --init --recursive WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

# -----------------------------------------------------------------------------
# helpers
# -----------------------------------------------------------------------------
macro(set_project_var name)
  set(${name} ${ARGN})
  set(${name} ${ARGN} PARENT_SCOPE)
endmacro()

macro(append_project_var name)
  set_project_var(${name} ${${name}} ${ARGN})
endmacro()

# -----------------------------------------------------------------------------
# build settings
# -----------------------------------------------------------------------------
set(LIB_NAME wav2midi)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
include_directories(${PROJECT_SOURCE_DIR})

enable_testing()
add_subdirectory(vendor)
add_subdirectory(wav2midi)
add_subdirectory(src)
add_subdirectory(test)
