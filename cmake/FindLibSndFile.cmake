find_path(LibSndFile_INCLUDE_DIRS NAMES sndfile.h)
find_library(LibSndFile_LIBRARIES NAMES sndfile)

find_package(PackageHandleStandardArgs)
find_package_handle_standard_args(
  LibSndFile
  REQUIRED_VARS
    LibSndFile_LIBRARIES
    LibSndFile_INCLUDE_DIRS
)

mark_as_advanced(LibSndFile_LIBRARIES LibSndFile_INCLUDE_DIRS)
