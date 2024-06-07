#ifndef CHATGPT_CLIENT_CPP_MESSAGES_HPP_
#define CHATGPT_CLIENT_CPP_MESSAGES_HPP_
#include <cpprest/http_msg.h>
#include <cpprest/json.h>

#include "chatgpt_client_cpp/threads.hpp"

namespace chatgpt_client_cpp::v1::messages
{
namespace create
{
class Builder
{
private:
  Builder();
  ~Builder() = default;

  Builder& thread_id(const utility::string_t& thread_id);
  Builder& body(const web::json::value& body);
  web::http::http_request build();

private:
  web::http::uri_builder uri_builder_;
  web::http::http_request req_;
};

namespace body
{
using MessageBuilder = chatgpt_client_cpp::v1::threads::create::body::MessageBuilder;
}  // namespace body

}  // namespace create
namespace list
{
class Builder
{
public:
  Builder();
  ~Builder() = default;

  Builder& thread_id(const utility::string_t& thread_id);
  web::http::http_request build();
  // optional parameters are not implemented...

private:
  web::http::uri_builder uri_builder_;
  web::http::http_request req_;
};
}  // namespace list
namespace retrieve
{
class Builder
{
public:
  Builder();
  ~Builder() = default;

  Builder& thread_id(const utility::string_t& thread_id);
  Builder& message_id(const utility::string_t& message_id);
  web::http::http_request build();

private:
  web::http::uri_builder uri_builder_;
  web::http::http_request req_;
};
}  // namespace retrieve
namespace modify
{
}  // namespace modify
namespace delete_
{
class Builder
{
public:
  Builder();
  ~Builder() = default;

  Builder& thread_id(const utility::string_t& thread_id);
  Builder& message_id(const utility::string_t& message_id);
  web::http::http_request build();

private:
  web::http::uri_builder uri_builder_;
  web::http::http_request req_;
};
}  // namespace delete_
}  // namespace chatgpt_client_cpp::v1::messages
#endif  // CHATGPT_CLIENT_CPP_MESSAGES_HPP_
