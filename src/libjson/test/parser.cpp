#include <gtest/gtest.h>

#include <libjson/parser.hpp>

#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>

namespace json::test {

static size_t count_indentation(const std::string& str) {
  const auto it = std::find_if_not(
      str.begin(), str.end(), [](char ch) { return std::isspace(ch); });
  return std::distance(str.begin(), it);
}

static std::string dedent(const std::string& str) {
  std::stringstream ss(str);
  std::stringstream out;
  std::string line;
  // Skip first '\n'
  std::getline(ss, line);

  std::getline(ss, line);
  const auto indentation = count_indentation(line);
  out << line.substr(std::min(indentation, line.size())) << "\n";

  while (std::getline(ss, line)) {
    out << line.substr(std::min(indentation, line.size())) << "\n";
  }

  return out.str();
}

TEST(ParserSuite, ValidDocument) {
  // Given
  std::stringstream in(R"(
    {
      "foo": {
        "bar" : "baz"
      }
    }
    )");

  // When
  auto parse_result = json::parse(in);

  // Then
  EXPECT_TRUE(parse_result.errors_.empty());

  std::stringstream ast_str;
  json::dump_ast(parse_result.document_, ast_str);
  EXPECT_EQ(ast_str.str(), dedent(R"(
      <?xml version="1.0"?>
      <json>
        <foo>
          <bar>baz</bar>
        </foo>
      </json>)"));
}

TEST(ParserSuite, InvalidDocument) {
  // Given
  std::stringstream in(R"(
    {
      "foo" {}
    }
    )");

  // When
  auto parse_result = json::parse(in);

  // Then
  std::stringstream errors;
  json::dump_errors(parse_result.errors_, errors);
  EXPECT_EQ(errors.str(), "3:12 missing ':' at '{'\n");
}

}  // namespace json::test
