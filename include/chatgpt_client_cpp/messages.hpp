#ifndef CHATGPT_CLIENT_CPP_MESSAGES_HPP_
#define CHATGPT_CLIENT_CPP_MESSAGES_HPP_
#include <memory>

#include <cpprest/json.h>

namespace chatgpt_client_cpp::messages
{

class ChatBodyBuilder
{
public:
  using SharedPtr = std::shared_ptr<ChatBodyBuilder>;
  ChatBodyBuilder();
  ~ChatBodyBuilder() = default;

  ChatBodyBuilder& model(const utility::string_t& model);
  ChatBodyBuilder& message(const web::json::value& message);
  ChatBodyBuilder& max_tokens(const uint32_t max_tokens);

  web::json::value get();

private:
 web::json::value json_;
};

class MessageElementBuilder
{
public:
  using SharedPtr = std::shared_ptr<MessageElementBuilder>;
  MessageElementBuilder();
  ~MessageElementBuilder() = default;

  MessageElementBuilder& role(const utility::string_t& role);
  MessageElementBuilder& content(const web::json::value& content);

  web::json::value get();

private:
 web::json::value json_;
};


class ContentTextPartBuilder
{
public:
  using SharedPtr = std::shared_ptr<ContentTextPartBuilder>;
  ContentTextPartBuilder() = default;
  ~ContentTextPartBuilder() = default;

  ContentTextPartBuilder& type(const utility::string_t& type);
  ContentTextPartBuilder& text(const utility::string_t& text);

  web::json::value get() const;

private:
  web::json::value json_;
};


class ContentImageUriPartBuilder
{
public:
  using SharedPtr = std::shared_ptr<ContentImageUriPartBuilder>;
  ContentImageUriPartBuilder() = default;
  ~ContentImageUriPartBuilder() = default;

  ContentImageUriPartBuilder& type(const utility::string_t& type);
  ContentImageUriPartBuilder& image_uri(const web::json::value& json);

  web::json::value get() const;

private:
  web::json::value json_;
};

class ImageUriBuilder
{
public:
  using SharedPtr = std::shared_ptr<ImageUriBuilder>;
  ImageUriBuilder() = default;
  ~ImageUriBuilder() = default;

  ImageUriBuilder& uri(const utility::string_t& type);
  ImageUriBuilder& detail(const utility::string_t& type);

  web::json::value get() const;

private:
  web::json::value json_;
};


}  // namespace chatgpt_client_cpp::messages
#endif  // CHATGPT_CLIENT_CPP_MESSAGES_HPP_
