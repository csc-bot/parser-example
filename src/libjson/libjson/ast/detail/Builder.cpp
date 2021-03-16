#include <libjson/ast/detail/Builder.hpp>

namespace json::ast::detail {

antlrcpp::Any Builder::visitDocument(JsonParser::DocumentContext* context) {
  auto* value = std::any_cast<Value*>(visitChildren(context));
  document_.set_value(value);
  return value;
}

antlrcpp::Any Builder::visitObject(JsonParser::ObjectContext* context) {
  auto const members =
      std::any_cast<Object::Members>(visit(context->members()));
  return static_cast<Value*>(document_.create_node<Object>(members));
}

static std::string trim_quotes(const std::string& str) {
  // NOLINTNEXTLINE
  assert(str[0] == '"' && str[str.size() - 1] == '"');
  return str.substr(1, str.size() - 2);
}

antlrcpp::Any Builder::visitMembers(JsonParser::MembersContext* context) {
  Object::Members members;
  for (auto* member : context->member()) {
    auto const key_text = trim_quotes(member->STRING()->getText());
    auto* key = document_.create_node<String>(key_text);
    auto* element = std::any_cast<Value*>(visit(member->element()));
    members.emplace_back(key, element);
  }
  return members;
}

antlrcpp::Any Builder::visitArray(JsonParser::ArrayContext* context) {
  Array::Elements elements;
  for (const auto& element : context->element()) {
    elements.push_back(std::any_cast<Value*>(visit(element)));
  }
  return static_cast<Value*>(document_.create_node<Array>(elements));
}

antlrcpp::Any Builder::visitNumber(JsonParser::NumberContext* context) {
  return static_cast<Value*>(document_.create_node<Number>(context->getText()));
}

antlrcpp::Any Builder::visitString(JsonParser::StringContext* context) {
  auto const text = trim_quotes(context->getText());
  return static_cast<Value*>(document_.create_node<String>(text));
}

}  // namespace json::ast::detail
