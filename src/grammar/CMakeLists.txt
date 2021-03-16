set(parser_lib_name Json)

add_library(${parser_lib_name} STATIC)

find_package(ANTLR REQUIRED)

set(antlr_parser_target_name Antlr${parser_lib_name})
antlr_target(
  ${antlr_parser_target_name}
  ${parser_lib_name}.g4
  LEXER
  PARSER
  VISITOR
)

target_sources(
  ${parser_lib_name}
  PRIVATE
    ${ANTLR_${antlr_parser_target_name}_CXX_OUTPUTS}
)

target_include_directories(
  ${parser_lib_name}
  PUBLIC
    ${ANTLR_${antlr_parser_target_name}_OUTPUT_DIR}
)

target_link_libraries(
  ${parser_lib_name}
  PUBLIC
    antlr4
)
