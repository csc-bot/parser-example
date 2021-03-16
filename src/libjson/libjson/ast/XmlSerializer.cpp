#include <libjson/ast/XmlSerializer.hpp>

#include <string>

namespace json::ast {

void XmlSerializer::exec(Document& document, std::ostream& out) {
  XmlSerializer xml_serializer;
  xml_serializer.nodes_.push(xml_serializer.doc_.append_child("json"));
  document.get_value()->accept(xml_serializer);
  xml_serializer.doc_.save(out, "  ");
}

void XmlSerializer::visit(Object& value) {
  for (const auto& member : value.members()) {
    auto key = append_child(member.key()->text().c_str());
    nodes_.push(key);
    member.value()->accept(*this);
    nodes_.pop();
  }
}

void XmlSerializer::visit(Array& value) {
  for (const auto& element : value.elements()) {
    auto item = append_child("item");
    nodes_.push(item);
    element->accept(*this);
    nodes_.pop();
  }
}

void XmlSerializer::visit(String& value) {
  append_text(value.text().c_str());
}

void XmlSerializer::visit(Number& value) {
  append_text(value.text().c_str());
}

pugi::xml_node XmlSerializer::append_child(const char* name) {
  return nodes_.top().append_child(name);
}

void XmlSerializer::append_text(const char* text) {
  auto text_node = nodes_.top().append_child(pugi::node_pcdata);
  text_node.set_value(text);
}

}  // namespace json::ast
