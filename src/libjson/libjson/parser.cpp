#include <libjson/parser.hpp>

#include <libjson/ast/XmlSerializer.hpp>
#include <libjson/ast/detail/Builder.hpp>

#include <JsonLexer.h>
#include <JsonParser.h>

#include <fmt/format.h>

namespace json {

namespace {

class StreamErrorListener : public antlr4::BaseErrorListener {
 public:
  void syntaxError(
      antlr4::Recognizer* /*recognizer*/,
      antlr4::Token* /*offendingSymbol*/,
      size_t line,
      size_t column,
      const std::string& message,
      std::exception_ptr /*e*/) override {
    errors_.emplace_back(Error{line, column, message});
  }

  const Errors& errors() const { return errors_; }

 private:
  Errors errors_;
};

}  // namespace

ParseResult parse(std::istream& in) {
  antlr4::ANTLRInputStream stream(in);
  JsonLexer lexer(&stream);
  antlr4::CommonTokenStream tokens(&lexer);
  JsonParser parser(&tokens);

  StreamErrorListener error_listener;
  parser.removeErrorListeners();
  parser.addErrorListener(&error_listener);

  auto* document_parse_tree = parser.document();

  const auto& errors = error_listener.errors();
  if (!errors.empty()) {
    return ParseResult::errors(errors);
  }

  ast::Document document;
  ast::detail::Builder builder(document);
  builder.visit(document_parse_tree);

  return ParseResult::document(std::move(document));
}

void dump_ast(ast::Document& document, std::ostream& out) {
  ast::XmlSerializer::exec(document, out);
}

void dump_errors(const Errors& errors, std::ostream& out) {
  for (const auto& error : errors) {
    out << fmt::format(
        "{}:{} {}\n", error.line_, error.column_, error.message_);
  }
}

}  // namespace json
