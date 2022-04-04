add_library(tests)

target_sources(tests PRIVATE
  unit_tests.cpp
  )

target_include_directories(tests PUBLIC
  ${PROJECT_SOURCE_DIR}/inc
  )
