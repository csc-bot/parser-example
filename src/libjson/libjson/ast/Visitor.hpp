#pragma once

#include <libjson/ast/Ast.hpp>

namespace json::ast {

class Visitor {
 public:
  virtual void visit(Object& value) = 0;
  virtual void visit(Array& value) = 0;
  virtual void visit(String& value) = 0;
  virtual void visit(Number& value) = 0;
};

}  // namespace json::ast
