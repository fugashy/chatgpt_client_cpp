#include "chatgpt_client_cpp/runs.hpp"

#include "chatgpt_client_cpp/utils.hpp"


namespace chatgpt_client_cpp::v1::runs
{

Runs::Runs(
    const ApiHelper::Pargs& pargs)
  : ApiHelper(false, pargs)
{
  Initialize(pargs);
}

ObjectHelper::SharedPtr Runs::InitializeObject(const ApiHelper::Pargs& pargs)
{
  auto req = runs::create::Builder()
    .thread_id(pargs.at("thread_id"))
    .body(runs::create::body::Builder()
        .assistant_id(pargs.at("assistant_id"))
        .build())
    .build();
  auto res = client::Client::GetInstance().Request<client::Client::OptionalJson>(req);
  if (res == std::nullopt)
  {
    throw std::runtime_error("failed to get response for creation the run");
  }

  return std::make_shared<ObjectHelper>(res.value());
}

bool Runs::Wait()
{
  bool wait = true;
  do
  {
    auto req = runs::retrieve::Builder()
      .thread_id(object_->GetThreadId())
      .run_id(object_->GetId())
      .build();
    auto res = client::Client::GetInstance().Request<client::Client::OptionalJson>(req);
    if (res == std::nullopt)
    {
      std::cerr << "failed to retrieve runs in thread(" << object_->GetThreadId() << ")" << std::endl;
      return false;
    }

    if(res.value()["status"].as_string() == "completed") wait = false;
  }
  while (wait);

  return true;
}

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
  return *this;
}

Builder& Builder::body(const web::json::value& body)
{
  this->req_.set_body(body);
  return *this;
}

web::http::http_request Builder::build()
{
  this->uri_builder_.append_path("runs");
  this->req_.set_request_uri(uri_builder_.to_uri());
  return this->req_;
}

namespace body
{

Builder& Builder::assistant_id(const utility::string_t& assistant_id)
{
  this->json_["assistant_id"] = web::json::value::string(assistant_id);
  return *this;
}

web::json::value Builder::build()
{
  return this->json_;
}

}  // namespace body
}  // namespace create

namespace list
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
  this->uri_builder_.append_path("runs");
  return *this;
}

web::http::http_request Builder::build()
{
  this->req_.set_request_uri(uri_builder_.to_uri());
  return this->req_;
}

}

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

Builder& Builder::run_id(const utility::string_t& run_id)
{
  this->run_id_ = run_id;
  return *this;
}

web::http::http_request Builder::build()
{
  this->uri_builder_.append_path(this->thread_id_);
  this->uri_builder_.append_path("runs");
  this->uri_builder_.append_path(this->run_id_);
  this->req_.set_request_uri(uri_builder_.to_uri());
  return this->req_;
}

}

namespace cancel
{

Builder::Builder() noexcept(false)
{
  this->uri_builder_.set_path("v1/threads");
  this->req_.set_method(web::http::methods::POST);
  this->req_.headers().add("Authorization", utils::GetKey());
  this->req_.headers().add("Content-Type", "application/json");
  this->req_.headers().add("OpenAI-Beta", "assistants=v2");
}

Builder& Builder::thread_id(const utility::string_t& thread_id)
{
  this->thread_id_ = thread_id;
  return *this;
}

Builder& Builder::run_id(const utility::string_t& run_id)
{
  this->run_id_ = run_id;
  return *this;
}

web::http::http_request Builder::build()
{
  this->uri_builder_.append_path(this->thread_id_);
  this->uri_builder_.append_path("runs");
  this->uri_builder_.append_path(this->run_id_);
  this->req_.set_request_uri(uri_builder_.to_uri());
  return this->req_;
}

}


}  // namespace chatgpt_client_cpp::v1::runs
