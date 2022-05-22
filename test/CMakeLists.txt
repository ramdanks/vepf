# Use Catch2 library
find_package(Catch2 REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp)

file(COPY testfile DESTINATION ${TEST_OUTPUT_PATH})

add_executable(vepf-test ${SOURCES})
target_link_libraries(vepf-test PRIVATE ${CMAKE_PROJECT_NAME} Catch2::Catch2)
set_target_properties(vepf-test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT_PATH})