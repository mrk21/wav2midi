add_subdirectory(wav2midi)

file(GLOB SRCS "*.cpp")

foreach(f ${SRCS})
  get_filename_component(bf ${f} NAME_WE)
  add_executable(${bf} ${f})
  target_link_libraries(${bf} ${LIB_NAME})
endforeach()
