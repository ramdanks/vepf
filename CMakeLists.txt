cmake_minimum_required(VERSION 2.4.0)

project(vepf)

# Output build path
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)
set(HEADER_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/include)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)

file(GLOB_RECURSE SOURCES src/*.c)
file(GLOB_RECURSE HEADERS src/*.h)

# Create static library
add_library(${PROJECT_NAME} STATIC ${SOURCES})

# copy headers into build dir
file(COPY ${HEADERS} DESTINATION ${HEADER_OUTPUT_PATH})

if(BUILD_TESTING)
    file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS test/*.cpp)
    add_executable(vepf-test ${TEST_SOURCES})
    target_link_libraries(vepf-test ${PROJECT_NAME})
endif()

# Install library
install(TARGETS ${PROJECT_NAME} DESTINATION lib)

# Install library headers
install(FILES ${HEADERS} DESTINATION include)