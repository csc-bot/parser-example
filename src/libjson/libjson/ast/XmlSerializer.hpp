#pragma once

#include <libjson/ast/Visitor.hpp>

#include <pugixml.hpp>

#include <ostream>
#include <stack>

namespace json::ast {

class XmlSerializer final : public Visitor {
 public:
  static void exec(Document& document, std::ostream& out);

  void visit(Object& value) override;
  void visit(Array& value) override;
  void visit(String& value) override;
  void visit(Number& value) override;

 private:
  pugi::xml_node append_child(const char* name);
  void append_text(const char* text);

  pugi::xml_document doc_;
  std::stack<pugi::xml_node> nodes_;
};

}  // namespace json::ast
