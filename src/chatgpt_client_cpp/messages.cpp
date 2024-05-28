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

}  // namespace chatgpt_client_cpp::messages
