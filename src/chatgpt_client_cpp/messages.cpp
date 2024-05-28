#include "chatgpt_client_cpp/messages.hpp"


namespace chatgpt_client_cpp::messages
{

ContentTextPartBuilder* ContentTextPartBuilder::type(const utility::string_t& type)
{
  this->json_["type"] = web::json::value::string(type);
  return this;
}

ContentTextPartBuilder* ContentTextPartBuilder::text(const utility::string_t& text)
{
  this->json_["text"] = web::json::value::string(text);
  return this;
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

ContentImageUriPartBuilder* ContentImageUriPartBuilder::type(const utility::string_t& type)
{
  this->json_["type"] = web::json::value::string(type);
  return this;
}

ContentImageUriPartBuilder* ContentImageUriPartBuilder::image_uri(const web::json::value& image_uri)
{
  this->json_["image_uri"] = image_uri;
  return this;
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

ImageUriBuilder* ImageUriBuilder::uri(const utility::string_t& type)
{
  this->json_["uri"] = web::json::value::string(type);
  return this;
}

ImageUriBuilder* ImageUriBuilder::detail(const utility::string_t& type)
{
  this->json_["detail"] = web::json::value::string(type);
  return this;
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
