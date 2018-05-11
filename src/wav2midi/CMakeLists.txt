file(GLOB_RECURSE SRCS "*.cpp")
add_library(${LIB_NAME} ${SRCS} ${HEADERS})
target_include_directories(${LIB_NAME} PUBLIC ${vendor_product_INCLUDE_DIRS})
target_link_libraries(${LIB_NAME} PUBLIC ${vendor_product_LIBRARIES})
