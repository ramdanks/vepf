cmake_minimum_required(VERSION 3.2.0)

project(vepf)

# for clang that defaulted to older c standard
set(CMAKE_CXX_STANDARD 17)

# cmake build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")

set(SOURCE_PATH ${PROJECT_SOURCE_DIR}/src)

# Output build path
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)
set(HEADER_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/include)
set(TEST_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/test)

file(GLOB_RECURSE SOURCES ${SOURCE_PATH}/*.c)
file(GLOB_RECURSE HEADERS ${SOURCE_PATH}/*.h)

# Create static library
add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE libm.a)

# copy headers into build dir
file(COPY ${HEADERS} DESTINATION ${HEADER_OUTPUT_PATH})

add_subdirectory(test)

# Install library
install(TARGETS ${PROJECT_NAME} DESTINATION lib)

# Install library headers
install(FILES ${HEADERS} DESTINATION include)