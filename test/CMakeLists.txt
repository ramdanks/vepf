# Use Catch2 library
find_package(Catch2 REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(vepf-test ${SOURCES})

target_compile_definitions(vepf-test PUBLIC TEST_RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/resource/")

target_link_libraries(vepf-test PRIVATE ${CMAKE_PROJECT_NAME} Catch2::Catch2)

set_target_properties(vepf-test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT_PATH})