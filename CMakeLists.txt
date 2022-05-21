cmake_minimum_required(VERSION 2.4.0)

project(vepf)

# Output build path
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)
set(HEADER_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/include)

file(GLOB_RECURSE SOURCES src/*.c)
file(GLOB_RECURSE HEADERS src/*.h)

# Create static library
add_library(${PROJECT_NAME} STATIC ${SOURCES})

# copy headers into build dir
file(COPY ${HEADERS} DESTINATION ${HEADER_OUTPUT_PATH})

# Install library
install(TARGETS ${PROJECT_NAME} DESTINATION lib)

# Install library headers
install(FILES ${HEADERS} DESTINATION include)