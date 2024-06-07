#include "chatgpt_client_cpp/threads.hpp"

#include <cstdlib>
#include <sstream>

namespace chatgpt_client_cpp::v1::threads
{

namespace create
{

Builder::Builder() noexcept(false)
{
  this->req_.set_request_uri("v1/threads");
  this->req_.set_method(web::http::methods::POST);

  const std::string key = std::getenv("OPENAI_API_KEY");
  if (key.empty())
  {
    throw std::runtime_error("OPENAI_API_KEY is empty");
  }
  std::stringstream ss;
  ss << "Bearer " << key;

  this->req_.headers().add("Authorization", ss.str());
  this->req_.headers().add("Content-Type", "application/json");

  this->req_.headers().add("OpenAI-Beta", "assistants=v2");
}

Builder& Builder::body(const web::json::value& body)
{
  this->req_.set_body(body);
  return *this;
}

web::http::http_request Builder::get() noexcept
{
  return this->req_;
}

namespace body
{
Builder::Builder()
{
  this->json_["messages"] = web::json::value::array();
}

Builder& Builder::message(const web::json::value& message)
{
  this->json_["messages"][this->json_["messages"].size()] = message;
  return *this;
}

Builder& Builder::tool_resources(const web::json::value& tool_resources)
{
  std::cerr << "not implemented..." << std::endl;
  return *this;
}

Builder& Builder::metadata(const web::json::value& metadata)
{
  std::cerr << "not implemented..." << std::endl;
  return *this;
}

web::json::value Builder::get()
{
  return this->json_;
}

MessageBuilder::MessageBuilder()
{
  this->json_["content"] = web::json::value::array();
}

MessageBuilder& MessageBuilder::role(const utility::string_t& role)
{
  this->json_["role"] = web::json::value::string(role);
  return *this;
}

MessageBuilder& MessageBuilder::content(const web::json::value& content)
{
  this->json_["content"][this->json_["content"].size()] = content;
  return *this;
}

web::json::value MessageBuilder::get()
{
  return this->json_;
}

TextContentBuilder::TextContentBuilder()
{
  this->json_["type"] = web::json::value::string("text");
}

TextContentBuilder& TextContentBuilder::text(const utility::string_t& text)
{
  this->json_["text"] = web::json::value::string(text);
  return *this;
}

web::json::value TextContentBuilder::get()
{
  return this->json_;
}


}  // namespace body
}  // namespace create

namespace retrieve
{

Builder::Builder() noexcept(false)
{
  this->uri_builder_.set_path("v1/threads");
  this->req_.set_method(web::http::methods::GET);

  const std::string key = std::getenv("OPENAI_API_KEY");
  if (key.empty())
  {
    throw std::runtime_error("OPENAI_API_KEY is empty");
  }
  std::stringstream ss;
  ss << "Bearer " << key;

  this->req_.headers().add("Authorization", ss.str());
  this->req_.headers().add("Content-Type", "application/json");

  this->req_.headers().add("OpenAI-Beta", "assistants=v2");
}

Builder& Builder::thread_id(const utility::string_t& thread_id)
{
  this->uri_builder_.append_path(thread_id);
  return *this;
}

web::http::http_request Builder::get()
{
  this->req_.set_request_uri(uri_builder_.to_uri());
  return this->req_;
}

}  // namespace retrieve

namespace delete_
{

Builder::Builder() noexcept(false)
{
  this->uri_builder_.set_path("v1/threads");
  this->req_.set_method(web::http::methods::DEL);

  const std::string key = std::getenv("OPENAI_API_KEY");
  if (key.empty())
  {
    throw std::runtime_error("OPENAI_API_KEY is empty");
  }
  std::stringstream ss;
  ss << "Bearer " << key;

  this->req_.headers().add("Authorization", ss.str());
  this->req_.headers().add("Content-Type", "application/json");

  this->req_.headers().add("OpenAI-Beta", "assistants=v2");
}

Builder& Builder::thread_id(const utility::string_t& thread_id)
{
  this->uri_builder_.append_path(thread_id);
  return *this;
}

web::http::http_request Builder::get()
{
  this->req_.set_request_uri(uri_builder_.to_uri());
  return this->req_;
}


}  // namespace delete_

}  // namespace chatgpt_client_cpp::v1::threads
