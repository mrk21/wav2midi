include(ExternalProject)

macro(set_project_var name)
  set(${name} ${ARGN})
  set(${name} ${ARGN} PARENT_SCOPE)
endmacro()

macro(append_project_var name)
  set_project_var(${name} ${${name}} ${ARGN})
endmacro()

# -----------------------------------------------------------------------------
# Custom target
# -----------------------------------------------------------------------------
add_custom_target(vendor)
add_custom_target(vendor_product)
add_custom_target(vendor_develop)

add_dependencies(vendor vendor_develop)
add_dependencies(vendor_develop vendor_product)

# -----------------------------------------------------------------------------
# Libraries
# -----------------------------------------------------------------------------
# boost
find_package(Boost 1.67 REQUIRED system thread)
append_project_var(vendor_product_INCLUDE_DIRS ${Boost_INCLUDE_DIRS})
append_project_var(vendor_product_LIBRARIES ${Boost_LIBRARIES})

# libsndfile
find_package(LibSndFile 1.0 REQUIRED)
append_project_var(vendor_product_INCLUDE_DIRS ${LibSndFile_INCLUDE_DIRS})
append_project_var(vendor_product_LIBRARIES ${LibSndFile_LIBRARIES})

if(BUILD_TEST)
  # bandit
  append_project_var(vendor_develop_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/vendor)
endif()
