#pragma once

#include <memory>
#include <vector>

namespace json::ast {

class String;
class Value;
class Visitor;

class Document final {
 public:
  template <class T, class... Args>
  T* create_node(Args&&... args) {
    static_assert(std::is_base_of_v<Value, T>);
    values_.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
    return dynamic_cast<T*>(values_.back().get());
  }

  void set_value(ast::Value* value) { value_ = value; }
  ast::Value* get_value() const { return value_; }

 private:
  std::vector<std::unique_ptr<Value>> values_;
  ast::Value* value_ = nullptr;
};

class Value {
 public:
  virtual ~Value() = default;
  virtual void accept(Visitor& visitor) = 0;
};

class Object final : public Value {
 public:
  class Member {
   public:
    Member(String* key, Value* value) : key_(key), value_(value) {}
    String* key() const { return key_; }
    Value* value() const { return value_; }

   private:
    String* key_;
    Value* value_;
  };

  using Members = std::vector<Member>;

  explicit Object(Members members) : members_(std::move(members)) {}
  const Members& members() const { return members_; }
  void accept(Visitor& visitor) override;

 private:
  Members members_;
};

class Array final : public Value {
 public:
  using Elements = std::vector<ast::Value*>;

  explicit Array(Elements elements) : elements_(std::move(elements)) {}
  const Elements& elements() const { return elements_; }
  void accept(Visitor& visitor) override;

 private:
  Elements elements_;
};

class String final : public Value {
 public:
  explicit String(std::string text) : text_(std::move(text)) {}
  const std::string& text() const { return text_; }
  void accept(Visitor& visitor) override;

 private:
  std::string text_;
};

class Number final : public Value {
 public:
  explicit Number(std::string text) : text_(std::move(text)) {}
  const std::string& text() const { return text_; }
  void accept(Visitor& visitor) override;

 private:
  std::string text_;
};

}  // namespace json::ast
