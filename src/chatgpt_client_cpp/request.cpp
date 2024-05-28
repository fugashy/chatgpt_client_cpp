#include "chatgpt_client_cpp/request.hpp"

#include <cstdlib>
#include <sstream>



namespace chatgpt_client_cpp::request
{

namespace v1
{

BuilderBase::BuilderBase() noexcept(false)
  : uri_builder_("v1")
{
  this->method(web::http::methods::POST);

  const std::string key = std::getenv("OPENAI_API_KEY");
  if (key.empty())
  {
    throw std::runtime_error("OPENAI_API_KEY is empty");
  }
  std::stringstream ss;
  ss << "Bearer " << key;

  this
    ->header("Content-Type", "application/json")
    ->header("Authorization", ss.str());
}

web::http::http_request BuilderBase::get() noexcept
{
  req_.set_request_uri(uri_builder_.to_uri());
  return req_;
}

BuilderBase* BuilderBase::method(const web::http::method& method)
{
  this->req_.set_method(method);
  return this;
}

BuilderBase* BuilderBase::header(const utility::string_t& key, const utility::string_t& value)
{
  this->req_.headers().add(key, value);
  return this;
}

BuilderBase* BuilderBase::body(const web::json::value& body)
{
  this->req_.set_body(body);
  return this;
}

}  // namespace v1
}  // namespace chatgpt_client_cpp::request
