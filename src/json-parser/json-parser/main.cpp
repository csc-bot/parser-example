#include <libjson/dump_tokens.hpp>
#include <libjson/parser.hpp>

#include <cxxopts.hpp>

#include <fstream>
#include <iostream>
#include <string>

const char* const file_path_opt = "file_path";
const char* const dump_tokens_opt = "dump-tokens";
const char* const dump_ast_opt = "dump-ast";

int main(int argc, char** argv) {
  cxxopts::Options options("json-parser", "ANTLR4 json parser example");

  options.positional_help("<file_path>");

  try {
    // clang-format off
    options.add_options()
        (file_path_opt, "", cxxopts::value<std::string>())
        (dump_tokens_opt, "")
        (dump_ast_opt, "")
        ("h,help", "Print help");
    // clang-format on
  } catch (const cxxopts::OptionSpecException& e) {
    std::cerr << e.what() << "\n";
    return 1;
  }

  options.parse_positional({file_path_opt});

  try {
    const auto result = options.parse(argc, argv);

    if (result.count("help") > 0 || result.count(file_path_opt) != 1) {
      std::cout << options.help() << "\n";
      return 0;
    }

    std::ifstream input_stream(result[file_path_opt].as<std::string>());

    if (!input_stream.good()) {
      std::cerr << "Unable to read stream\n";
      return 1;
    }

    if (result.count(dump_tokens_opt) > 0) {
      json::dump_tokens(input_stream, std::cout);
    } else if (result.count(dump_ast_opt) > 0) {
      auto parser_result = json::parse(input_stream);
      if (!parser_result.errors_.empty()) {
        json::dump_errors(parser_result.errors_, std::cerr);
      } else {
        json::dump_ast(parser_result.document_, std::cout);
      }
    }
  } catch (const cxxopts::OptionException& e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
