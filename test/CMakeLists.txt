if(NOT BUILD_TEST)
  return()
endif()

# -----------------------------------------------------------------------------
# build
# -----------------------------------------------------------------------------
file(GLOB_RECURSE specs *_spec.cpp)

add_executable(spec_runner
  spec_runner.cpp
  ${specs}
)
target_include_directories(spec_runner PRIVATE
  ${PROJECT_SOURCE_DIR}/test
  ${vendor_develop_INCLUDE_DIRS}
)
target_link_libraries(spec_runner PRIVATE
  ${LIB_NAME}
  ${vendor_develop_LIBRARIES}
)
add_dependencies(spec_runner vendor_develop)

# -----------------------------------------------------------------------------
# register test target
# -----------------------------------------------------------------------------
add_custom_target(spec
  COMMAND $<TARGET_FILE:spec_runner> --reporter=spec
  DEPENDS spec_runner
)
foreach(path IN LISTS specs)
  # build target name
  string(REPLACE ${PROJECT_SOURCE_DIR}/test/spec/ "" basepath ${path})
  string(REPLACE _spec.cpp "" basepath ${basepath})
  string(REPLACE / :: name wav2midi/${basepath})

  # register to ctest
  add_test(
    NAME ${name}
    COMMAND $<TARGET_FILE:spec_runner> --only=${name}
  )

  # set labels
  file(GLOB_RECURSE srcs ${PROJECT_SOURCE_DIR}/wav2midi/${basepath}/*.hpp)
  set_property(TEST ${name} PROPERTY LABELS
    ${path}
    ${PROJECT_SOURCE_DIR}/wav2midi/${basepath}.cpp
    ${PROJECT_SOURCE_DIR}/wav2midi/${basepath}.hpp
    ${srcs}
  )
endforeach()
