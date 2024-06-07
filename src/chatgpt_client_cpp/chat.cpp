#include "chatgpt_client_cpp/chat.hpp"

#include "chatgpt_client_cpp/utils.hpp"


namespace chatgpt_client_cpp
{
namespace v1
{
namespace chat
{

Builder::Builder() noexcept(false)
{
  this->req_.set_request_uri("v1/chat/completions");
  this->req_.set_method(web::http::methods::POST);
  this->req_.headers().add("Authorization", utils::GetKey());
  this->req_.headers().add("Content-Type", "application/json");
}

web::http::http_request Builder::build() const noexcept
{
  return req_;
}

Builder& Builder::body(const web::json::value& body)
{
  this->req_.set_body(body);
  return *this;
}

namespace body
{

Builder::Builder()
{
  this->json_["messages"] = web::json::value::array();
}

Builder& Builder::model(const utility::string_t& model)
{
  this->json_["model"] = web::json::value::string(model);
  return *this;
}

Builder& Builder::message(const web::json::value& message)
{
  this->json_["messages"][this->json_["messages"].size()] = message;
  return *this;
}

Builder& Builder::max_tokens(const uint32_t max_tokens)
{
  this->json_["max_tokens"] = web::json::value::number(max_tokens);
  return *this;
}

web::json::value Builder::build()
{
  const bool has_required_fields =
    this->json_.has_field("model") && this->json_.has_field("messages");
  const bool has_at_least_one_message = this->json_["messages"].size() > 0;
  if (!has_at_least_one_message || !has_required_fields)
  {
    std::cerr << "Please check the messages in body" << std::endl;
    return web::json::value();
  }
  return this->json_;
}

MessageElementBuilder::MessageElementBuilder()
{
  this->json_["content"] = web::json::value::array();
}

MessageElementBuilder& MessageElementBuilder::role(const utility::string_t& role)
{
  this->json_["role"] = web::json::value::string(role);
  return *this;
}

MessageElementBuilder& MessageElementBuilder::content(const web::json::value& content)
{
  this->json_["content"][this->json_["content"].size()] = content;
  return *this;
}

web::json::value MessageElementBuilder::build()
{
  const bool has_required_fields =
    this->json_.has_field("role") &&
    this->json_.has_field("content");
  const bool has_at_least_one_content = this->json_["content"].size() > 0;

  if (!has_at_least_one_content || !has_required_fields)
  {
    std::cerr << "Please check the messages in body" << std::endl;
    return web::json::value();
  }
  return this->json_;
}

ContentTextPartBuilder& ContentTextPartBuilder::type(const utility::string_t& type)
{
  this->json_["type"] = web::json::value::string(type);
  return *this;
}

ContentTextPartBuilder& ContentTextPartBuilder::text(const utility::string_t& text)
{
  this->json_["text"] = web::json::value::string(text);
  return *this;
}

web::json::value ContentTextPartBuilder::build() const
{
  const bool has_text_part = this->json_.has_field("type") && this->json_.has_field("text");
  if (!has_text_part)
  {
    std::cerr << "Please set both of type and text" << std::endl;
    return this->json_;
  }
  return this->json_;
}

ContentImageUrlPartBuilder& ContentImageUrlPartBuilder::type(const utility::string_t& type)
{
  this->json_["type"] = web::json::value::string(type);
  return *this;
}

ContentImageUrlPartBuilder& ContentImageUrlPartBuilder::image_url(const web::json::value& image_url)
{
  this->json_["image_url"] = image_url;
  return *this;
}

web::json::value ContentImageUrlPartBuilder::build() const
{
  const bool has_required_fields = this->json_.has_field("type") && this->json_.has_field("image_url");
  if (!has_required_fields)
  {
    std::cerr << "Set both of type and image_url" << std::endl;
    return web::json::value();
  }
  return this->json_;
}

ImageUrlBuilder& ImageUrlBuilder::url(const utility::string_t& type)
{
  this->json_["url"] = web::json::value::string(type);
  return *this;
}

ImageUrlBuilder& ImageUrlBuilder::detail(const utility::string_t& type)
{
  this->json_["detail"] = web::json::value::string(type);
  return *this;
}

web::json::value ImageUrlBuilder::build() const
{
  const bool has_required_fields = this->json_.has_field("url");
  if (!has_required_fields)
  {
    std::cerr << "url is empty" << std::endl;
    return web::json::value();
  }
  return this->json_;
}
}  // namespace body

}  // namespace chat
}  // namespace v1
}  // namespace chatgpt_client_cpp
