#include "chatgpt_client_cpp/request.hpp"

#include <cstdlib>
#include <sstream>



namespace chatgpt_client_cpp::request
{

namespace v1
{

namespace chat
{

Builder::Builder() noexcept(false)
{
  this->req_.set_request_uri("v1/chat/completions");
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
}

web::http::http_request Builder::get() const noexcept
{
  return req_;
}

Builder* Builder::body(const web::json::value& body)
{
  this->req_.set_body(body);
  return this;
}

}  // namespace chat
}  // namespace v1
}  // namespace chatgpt_client_cpp::request
