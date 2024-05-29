#ifndef CHATGPT_CLIENT_CPP_CHAT_HPP_
#define CHATGPT_CLIENT_CPP_CHAT_HPP_
#include <memory>

#include <cpprest/http_msg.h>
#include <cpprest/json.h>

namespace chatgpt_client_cpp
{

namespace v1
{

namespace chat {

class Builder
{
public:
  using SharedPtr = std::shared_ptr<Builder>;

  Builder() noexcept(false);
  virtual ~Builder() = default;

  web::http::http_request get() const noexcept;

  Builder& body(const web::json::value& body);

private:
  web::http::http_request req_;
};

namespace body
{

class Builder
{
public:
  using SharedPtr = std::shared_ptr<Builder>;
  Builder();
  ~Builder() = default;

  Builder& model(const utility::string_t& model);
  Builder& message(const web::json::value& message);
  Builder& max_tokens(const uint32_t max_tokens);

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


class ContentImageUrlPartBuilder
{
public:
  using SharedPtr = std::shared_ptr<ContentImageUrlPartBuilder>;
  ContentImageUrlPartBuilder() = default;
  ~ContentImageUrlPartBuilder() = default;

  ContentImageUrlPartBuilder& type(const utility::string_t& type);
  ContentImageUrlPartBuilder& image_url(const web::json::value& json);

  web::json::value get() const;

private:
  web::json::value json_;
};

class ImageUrlBuilder
{
public:
  using SharedPtr = std::shared_ptr<ImageUrlBuilder>;
  ImageUrlBuilder() = default;
  ~ImageUrlBuilder() = default;

  ImageUrlBuilder& url(const utility::string_t& type);
  ImageUrlBuilder& detail(const utility::string_t& type);

  web::json::value get() const;

private:
  web::json::value json_;
};
}  // namespace body

}  // namespace chat
}  // namespace v1
}  // namespace chatgpt_client_cpp
#endif  // CHATGPT_CLIENT_CPP_CHAT_HPP_
