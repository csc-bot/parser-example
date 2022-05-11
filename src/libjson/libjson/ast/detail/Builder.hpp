#pragma once

#include <libjson/ast/Ast.hpp>
#include <libjson/parser.hpp>

#include <JsonBaseVisitor.h>

#include <any>

namespace json::ast::detail {

class Builder final : public JsonBaseVisitor {
 public:
  explicit Builder(ast::Document& document) : document_(document) {}

  std::any visitDocument(JsonParser::DocumentContext* context) override;
  std::any visitObject(JsonParser::ObjectContext* context) override;
  std::any visitMembers(JsonParser::MembersContext* context) override;
  std::any visitArray(JsonParser::ArrayContext* context) override;
  std::any visitNumber(JsonParser::NumberContext* context) override;
  std::any visitString(JsonParser::StringContext* context) override;

 private:
  ast::Document& document_;
};

}  // namespace json::ast::detail
