set(lib_name json)

add_library(${lib_name})

include(CompileOptions)
json_target_set_compile_options(${lib_name})

target_include_directories(${lib_name} PUBLIC .)

target_sources(
  ${lib_name}
  PUBLIC
    libjson/dump_tokens.hpp
  PRIVATE
    libjson/dump_tokens.cpp
)

target_link_libraries(
  ${lib_name}
  PRIVATE
    JsonLexer
    fmt
)

set(test_name libjson_test)

add_executable(${test_name})

add_test(NAME ${test_name} COMMAND ${test_name})

json_target_set_compile_options(${test_name})

target_sources(
  ${test_name}
  PRIVATE
    test/lexer.cpp
)

target_link_libraries(
  ${test_name}
  PRIVATE
    ${lib_name}
    gtest
    gtest_main
)
