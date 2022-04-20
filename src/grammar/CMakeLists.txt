set(lexer_lib_name JsonLexer)

add_library(${lexer_lib_name} STATIC)

find_package(ANTLR REQUIRED)

set(antlr_lexer_target_name Antlr${lexer_lib_name})
antlr_target(
  ${antlr_lexer_target_name}
  ${lexer_lib_name}.g4
  LEXER
)

include(CompileOptions)
target_set_cxx_stanrard(${lexer_lib_name})

target_sources(
  ${lexer_lib_name}
  PRIVATE
    ${ANTLR_${antlr_lexer_target_name}_CXX_OUTPUTS}
)

target_include_directories(
  ${lexer_lib_name}
  PUBLIC
    ${ANTLR_${antlr_lexer_target_name}_OUTPUT_DIR}
)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

target_link_libraries(
  ${lexer_lib_name}
  PUBLIC
    antlr4
    Threads::Threads
)
