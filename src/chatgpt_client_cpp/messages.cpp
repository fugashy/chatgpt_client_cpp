#include "chatgpt_client_cpp/messages.hpp"


namespace chatgpt_client_cpp::messages
{

ChatBodyBuilder::ChatBodyBuilder()
{
  this->json_["messages"] = web::json::value::array();
}

ChatBodyBuilder& ChatBodyBuilder::model(const utility::string_t& model)
{
  this->json_["model"] = web::json::value::string(model);
  return *this;
}

ChatBodyBuilder& ChatBodyBuilder::message(const web::json::value& message)
{
  this->json_["messages"][this->json_["messages"].size()] = message;
  return *this;
}

ChatBodyBuilder& ChatBodyBuilder::max_tokens(const uint32_t max_tokens)
{
  this->json_["max_tokens"] = web::json::value::number(max_tokens);
  return *this;
}

web::json::value ChatBodyBuilder::get()
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

web::json::value MessageElementBuilder::get()
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

web::json::value ContentTextPartBuilder::get() const
{
  const bool has_text_part = this->json_.has_field("type") && this->json_.has_field("text");
  if (!has_text_part)
  {
    std::cerr << "Please set both of type and text" << std::endl;
    return this->json_;
  }
  return this->json_;
}

ContentImageUriPartBuilder& ContentImageUriPartBuilder::type(const utility::string_t& type)
{
  this->json_["type"] = web::json::value::string(type);
  return *this;
}

ContentImageUriPartBuilder& ContentImageUriPartBuilder::image_uri(const web::json::value& image_uri)
{
  this->json_["image_uri"] = image_uri;
  return *this;
}

web::json::value ContentImageUriPartBuilder::get() const
{
  const bool has_required_fields = this->json_.has_field("type") && this->json_.has_field("image_uri");
  if (!has_required_fields)
  {
    std::cerr << "Set both of type and image_uri" << std::endl;
    return web::json::value();
  }
  return this->json_;
}

ImageUriBuilder& ImageUriBuilder::uri(const utility::string_t& type)
{
  this->json_["uri"] = web::json::value::string(type);
  return *this;
}

ImageUriBuilder& ImageUriBuilder::detail(const utility::string_t& type)
{
  this->json_["detail"] = web::json::value::string(type);
  return *this;
}

web::json::value ImageUriBuilder::get() const
{
  const bool has_required_fields = this->json_.has_field("uri");
  if (!has_required_fields)
  {
    std::cerr << "uri is empty" << std::endl;
    return web::json::value();
  }
  return this->json_;
}

}  // namespace chatgpt_client_cpp::messages
