#pragma once

#include <libjson/ast/Ast.hpp>
#include <libjson/parser.hpp>

#include <JsonBaseVisitor.h>

namespace json::ast::detail {

class Builder final : public JsonBaseVisitor {
 public:
  explicit Builder(ast::Document& document) : document_(document) {}

  antlrcpp::Any visitDocument(JsonParser::DocumentContext* context) override;
  antlrcpp::Any visitObject(JsonParser::ObjectContext* context) override;
  antlrcpp::Any visitMembers(JsonParser::MembersContext* context) override;
  antlrcpp::Any visitArray(JsonParser::ArrayContext* context) override;
  antlrcpp::Any visitNumber(JsonParser::NumberContext* context) override;
  antlrcpp::Any visitString(JsonParser::StringContext* context) override;

 private:
  ast::Document& document_;
};

}  // namespace json::ast::detail
