#include <libjson/ast/Ast.hpp>

#include <libjson/ast/Visitor.hpp>

namespace json::ast {

void Object::accept(Visitor& visitor) {
  visitor.visit(*this);
}

void Array::accept(Visitor& visitor) {
  visitor.visit(*this);
}

void String::accept(Visitor& visitor) {
  visitor.visit(*this);
}

void Number::accept(Visitor& visitor) {
  visitor.visit(*this);
}

}  // namespace json::ast
