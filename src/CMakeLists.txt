add_library(src)

target_sources(src PRIVATE
  node.cpp
  utils.cpp
  )

target_include_directories(src PUBLIC
  ${PROJECT_SOURCE_DIR}/inc
  )
