#include "chatgpt_client_cpp/messages.hpp"

#include "chatgpt_client_cpp/utils.hpp"

namespace chatgpt_client_cpp::v1::messages
{
namespace create
{

Builder::Builder()
{
  this->uri_builder_.set_path("v1/threads");
  this->req_.set_method(web::http::methods::POST);
  this->req_.headers().add("Authorization", utils::GetKey());
  this->req_.headers().add("Content-Type", "application/json");
  this->req_.headers().add("OpenAI-Beta", "assistants=v2");
}

Builder& Builder::thread_id(const utility::string_t& thread_id)
{
  this->uri_builder_.append_path(thread_id);
  this->uri_builder_.append_path("messages");
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

}  // namespace create

namespace list
{
Builder::Builder()
{
  this->uri_builder_.set_path("v1/threads");
  this->req_.set_method(web::http::methods::GET);
  this->req_.headers().add("Authorization", utils::GetKey());
  this->req_.headers().add("Content-Type", "application/json");
  this->req_.headers().add("OpenAI-Beta", "assistants=v2");
}

Builder& Builder::thread_id(const utility::string_t& thread_id)
{
  this->uri_builder_.append_path(thread_id);
  this->uri_builder_.append_path("messages");
  return *this;
}

web::http::http_request Builder::build()
{
  this->req_.set_request_uri(uri_builder_.to_uri());
  return this->req_;
}
}  // namespace list

namespace retrieve
{
Builder::Builder() noexcept(false)
{
  this->uri_builder_.set_path("v1/threads");
  this->req_.set_method(web::http::methods::GET);
  this->req_.headers().add("Authorization", utils::GetKey());
  this->req_.headers().add("Content-Type", "application/json");
  this->req_.headers().add("OpenAI-Beta", "assistants=v2");
}

Builder& Builder::thread_id(const utility::string_t& thread_id)
{
  this->thread_id_ = thread_id;
  return *this;
}

Builder& Builder::message_id(const utility::string_t& message_id)
{
  this->message_id_ = message_id;
  return *this;
}

web::http::http_request Builder::build()
{
  this->uri_builder_.append_path(this->thread_id_);
  this->uri_builder_.append_path("messages");
  this->uri_builder_.append_path(this->message_id_);
  this->req_.set_request_uri(uri_builder_.to_uri());
  return this->req_;
}
}  // namespace retrieve

namespace modify
{
}  // namespace modify

namespace delete_
{
Builder::Builder() noexcept(false)
{
  this->uri_builder_.set_path("v1/threads");
  this->req_.set_method(web::http::methods::DEL);
  this->req_.headers().add("Authorization", utils::GetKey());
  this->req_.headers().add("Content-Type", "application/json");
  this->req_.headers().add("OpenAI-Beta", "assistants=v2");
}

Builder& Builder::thread_id(const utility::string_t& thread_id)
{
  this->thread_id_ = thread_id;
  return *this;
}

Builder& Builder::message_id(const utility::string_t& message_id)
{
  this->message_id_ = message_id;
  return *this;
}

web::http::http_request Builder::build()
{
  this->uri_builder_.append_path(this->thread_id_);
  this->uri_builder_.append_path("messages");
  this->uri_builder_.append_path(this->message_id_);
  this->req_.set_request_uri(uri_builder_.to_uri());
  return this->req_;
}

}  // namespace delete

}  // namespace chatgpt_client_cpp::v1::messages
