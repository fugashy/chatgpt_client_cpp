#include "chatgpt_client_cpp/assistants.hpp"

#include "chatgpt_client_cpp/utils.hpp"

namespace chatgpt_client_cpp::v1::assistants
{
namespace create
{

Builder::Builder()
{
  this->req_.set_request_uri("v1/assistants");
  this->req_.set_method(web::http::methods::POST);
  this->req_.headers().add("Authorization", utils::GetKey());
  this->req_.headers().add("Content-Type", "application/json");
}

Builder& Builder::body(const web::json::value& body)
{
  this->req_.set_body(body);
  return *this;
}

web::http::http_request Builder::build()
{
  return this->req_;
}

namespace body
{

web::json::value Builder::build()
{
  return this->json_;
}

Builder& Builder::model(const utility::string_t& model)
{
  this->json_["model"] = web::json::value::string(model);
  return *this;
}

Builder& Builder::name(const utility::string_t& name)
{
  this->json_["name"] = web::json::value::string(name);
  return *this;
}

Builder& Builder::description(const utility::string_t& description)
{
  this->json_["description"] = web::json::value::string(description);
  return *this;
}

Builder& Builder::instructions(const utility::string_t& instructions)
{
  this->json_["instructions"] = web::json::value::string(instructions);
  return *this;
}

Builder& Builder::response_format(const utility::string_t& response_format)
{
  this->json_["response_format"] = web::json::value::string(response_format);
  return *this;
}

}  // namespace body
}  // namespace create

namespace list
{
Builder::Builder()
{
  this->req_.set_request_uri("v1/assistants");
  this->req_.set_method(web::http::methods::GET);
  this->req_.headers().add("Authorization", utils::GetKey());
  this->req_.headers().add("Content-Type", "application/json");
  this->req_.headers().add("OpenAI-Beta", "assistants=v2");

  // 空のボディをセットしないとextract_jsonが終了しない
  this->req_.set_body(web::json::value());
}

web::http::http_request Builder::build()
{
  return this->req_;
}

}  // namespace list

namespace retrieve
{

Builder::Builder() noexcept(false)
{
  this->uri_builder_.set_path("v1/assistants");
  this->req_.set_method(web::http::methods::GET);
  this->req_.headers().add("Authorization", utils::GetKey());
  this->req_.headers().add("Content-Type", "application/json");
  this->req_.headers().add("OpenAI-Beta", "assistants=v2");

  // 空のボディをセットしないとextract_jsonが終了しない
  this->req_.set_body(web::json::value());
}

Builder& Builder::assistant_id(const utility::string_t& assistant_id)
{
  this->uri_builder_.append_path(assistant_id);
  return *this;
}

web::http::http_request Builder::build()
{
  this->req_.set_request_uri(uri_builder_.to_uri());
  return this->req_;
}

}  // namespace retrieve

namespace modify
{
Builder::Builder()
{
  this->uri_builder_.set_path("v1/assistants");
  this->req_.set_method(web::http::methods::POST);
  this->req_.headers().add("Authorization", utils::GetKey());
  this->req_.headers().add("Content-Type", "application/json");
  this->req_.headers().add("OpenAI-Beta", "assistants=v2");
}

Builder& Builder::assistant_id(const utility::string_t& assistant_id)
{
  this->uri_builder_.append_path(assistant_id);
  return *this;
}

Builder& Builder::body(const web::json::value& body)
{
  this->req_.set_body(body);
  return *this;
}

web::http::http_request Builder::build()
{
  this->req_.set_request_uri(uri_builder_.to_uri());
  return this->req_;
}

}  // namespace modify

namespace delete_
{
Builder::Builder() noexcept(false)
{
  this->uri_builder_.set_path("v1/assistants");
  this->req_.set_method(web::http::methods::DEL);
  this->req_.headers().add("Authorization", utils::GetKey());
  this->req_.headers().add("Content-Type", "application/json");
  this->req_.headers().add("OpenAI-Beta", "assistants=v2");

  this->req_.set_body(web::json::value());
}

Builder& Builder::assistant_id(const utility::string_t& assistant_id)
{
  this->uri_builder_.append_path(assistant_id);
  return *this;
}

web::http::http_request Builder::build()
{
  this->req_.set_request_uri(uri_builder_.to_uri());
  return this->req_;
}
}  // namespace delete_
}  // namespace chatgpt_client_cpp::v1::assistants
