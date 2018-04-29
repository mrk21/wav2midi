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
  add_compile_options(-std=c++17 -stdlib=libc++)
  set(CMAKE_EXE_LINKER_FLAGS -stdlib=libc++)
  set(VENDOR_CXX_FLAGS -stdlib=libc++)
else()
  message(FATAL_ERROR "Supported compiler is Clang!")
endif()

add_compile_options(
  -Wall
  -Wextra
)

# -----------------------------------------------------------------------------
# init submodules
# -----------------------------------------------------------------------------
execute_process(COMMAND git submodule update --init --recursive WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

# -----------------------------------------------------------------------------
# build settings
# -----------------------------------------------------------------------------
set(LIB_NAME wav2midi)
include_directories(${PROJECT_SOURCE_DIR})

enable_testing()
add_subdirectory(vendor)
add_subdirectory(src)
add_subdirectory(test)
