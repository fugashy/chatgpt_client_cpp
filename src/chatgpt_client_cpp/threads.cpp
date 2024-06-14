#include "chatgpt_client_cpp/threads.hpp"

#include "chatgpt_client_cpp/messages.hpp"
#include "chatgpt_client_cpp/utils.hpp"


namespace chatgpt_client_cpp::v1::threads
{

Threads::Threads(
    const bool enable_destructor,
    const ApiHelper::Pargs& pargs)
  : ApiHelper(enable_destructor, pargs)
{
  Initialize(pargs);
}

ObjectHelper::SharedPtr Threads::InitializeObject(const ApiHelper::Pargs& pargs)
{
  auto req = threads::create::Builder().build();
  auto res = client::Client::GetInstance().Request<client::Client::OptionalJson>(req);
  if (res == std::nullopt)
  {
    throw std::runtime_error("failed to request for creation threads");
  }

  return std::make_shared<ObjectHelper>(res.value());
}

void Threads::DestructObject()
{
  auto req = threads::delete_::Builder()
    .thread_id(this->object_->GetId())
    .build();
  auto res = client::Client::GetInstance().Request<client::Client::OptionalJson>(req);
  if (res == std::nullopt)
  {
    std::cerr << "failed to get response for deletion the thread(" << this->object_->GetId().c_str() << ")" << std::endl;
  }
  if (!res.value()["deleted"].as_bool())
  {
    std::cerr << "failed to delete for thread(" << this->object_->GetId() << ")" << std::endl;
  }
  std::cout << "delete the thread(" << this->object_->GetId() << ")" << std::endl;
}

MessageInterface::MessageByRole Threads::GetMessages()
{
  auto req = messages::list::Builder()
    .thread_id(this->object_->GetId())
    .build();
  auto res = client::Client::GetInstance().Request<client::Client::OptionalJson>(req);
  if (res == std::nullopt)
  {
    std::cerr << "failed to get response for list messages in the thread(" << this->object_->GetId() << ")" << std::endl;
    return MessageByRole();
  }

  MessageByRole out;
  for (auto e : res.value()["data"].as_array())
  {
    out.insert({
        e["role"].as_string(),
        e["content"][0]["text"]["value"].as_string()});
  }
  return out;
}

namespace create
{

Builder::Builder() noexcept(false)
{
  this->req_.set_request_uri("v1/threads");
  this->req_.set_method(web::http::methods::POST);
  this->req_.headers().add("Authorization", utils::GetKey());
  this->req_.headers().add("Content-Type", "application/json");
  this->req_.headers().add("OpenAI-Beta", "assistants=v2");
}

Builder& Builder::body(const web::json::value& body)
{
  this->req_.set_body(body);
  return *this;
}

web::http::http_request Builder::build() noexcept
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

web::json::value Builder::build()
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

web::json::value MessageBuilder::build()
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

web::json::value TextContentBuilder::build()
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
  this->req_.headers().add("Authorization", utils::GetKey());
  this->req_.headers().add("Content-Type", "application/json");
  this->req_.headers().add("OpenAI-Beta", "assistants=v2");
}

Builder& Builder::thread_id(const utility::string_t& thread_id)
{
  this->uri_builder_.append_path(thread_id);
  return *this;
}

web::http::http_request Builder::build()
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
  this->req_.headers().add("Authorization", utils::GetKey());
  this->req_.headers().add("Content-Type", "application/json");
  this->req_.headers().add("OpenAI-Beta", "assistants=v2");
}

Builder& Builder::thread_id(const utility::string_t& thread_id)
{
  this->uri_builder_.append_path(thread_id);
  return *this;
}

web::http::http_request Builder::build()
{
  this->req_.set_request_uri(uri_builder_.to_uri());
  return this->req_;
}


}  // namespace delete_

}  // namespace chatgpt_client_cpp::v1::threads
