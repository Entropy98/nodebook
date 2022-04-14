cmake_minimum_required(VERSION 3.10)

set(CMAKE_VERBOSE_MAKEFILE TRUE)

project(nodebook)
add_subdirectory(src)
if(CMAKE_BUILD_TYPE STREQUAL "TEST")
  add_subdirectory(tests)
  add_executable(${PROJECT_NAME}_tests tests/unit_tests.cpp)
  target_compile_options(${PROJECT_NAME}_tests PUBLIC
    -g
    )
  target_link_libraries(${PROJECT_NAME}_tests
    -Wall
    -Wextra
    -O0
    -Wunreachable-code
    tests
    src
    )
else()
  add_executable(${PROJECT_NAME} src/main.cpp)
  target_compile_options(${PROJECT_NAME} PUBLIC
    -g
    )
  target_link_libraries(${PROJECT_NAME}
    -Wall
    -Wextra
    -O0
    -Wunreachable-code
    -ggdb
    src
    )
endif()

