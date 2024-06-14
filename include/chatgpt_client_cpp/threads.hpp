#ifndef CHATGPT_CLIENT_CPP_THREADS_HPP_
#define CHATGPT_CLIENT_CPP_THREADS_HPP_
#include <cpprest/http_msg.h>
#include <cpprest/json.h>

#include "chatgpt_client_cpp/client.hpp"
#include "chatgpt_client_cpp/helper_base.hpp"

namespace chatgpt_client_cpp::v1::threads
{

class Threads final : public ApiHelper, public MessageInterface
{
public:
  Threads(
      const bool enable_destructor,
      const ApiHelper::Pargs& pargs = ApiHelper::Pargs());
  ~Threads() = default;

  MessageInterface::MessageByRole GetMessages() override;

protected:
  ObjectHelper::SharedPtr InitializeObject(const ApiHelper::Pargs& pargs) override;
  void DestructObject() override;

private:
};

namespace create
{

class Builder
{
public:
  Builder() noexcept(false);
  ~Builder() = default;

  Builder& body(const web::json::value& body);
  web::http::http_request build() noexcept;

private:
  web::http::http_request req_;
};

namespace body
{
class Builder
{
public:
  Builder();
  ~Builder() = default;

  Builder& message(const web::json::value& message);
  Builder& tool_resources(const web::json::value& tool_resources);
  Builder& metadata(const web::json::value& tool_resources);
  web::json::value build();

private:
  web::json::value json_;
};

class MessageBuilder
{
public:
  MessageBuilder();
  ~MessageBuilder() = default;

  MessageBuilder& role(const utility::string_t& role);
  MessageBuilder& content(const web::json::value& content);

  MessageBuilder& attachment(const web::json::value& attachment)
  {
    std::cerr << "attachment is not implemented..." << std::endl;
    return *this;
  }

  MessageBuilder& metadata(const web::json::value& metadata)
  {
    std::cerr << "metadata is not implemented..." << std::endl;
    return *this;
  }

  web::json::value build();

private:
  web::json::value json_;
};

class TextContentBuilder
{
public:
  TextContentBuilder();
  ~TextContentBuilder() = default;

  TextContentBuilder& text(const utility::string_t& text);
  web::json::value build();

private:
  web::json::value json_;
};


}  // namespace body
}  // namespace create

namespace retrieve
{

class Builder
{
public:
  Builder();
  ~Builder() = default;

  Builder& thread_id(const utility::string_t& thread_id);
  web::http::http_request build();

private:
  web::http::uri_builder uri_builder_;
  web::http::http_request req_;
};

}  // namespace retrieve

namespace delete_ {

class Builder
{
public:
  Builder();
  ~Builder() = default;

  Builder& thread_id(const utility::string_t& thread_id);
  web::http::http_request build();

private:
  web::http::uri_builder uri_builder_;
  web::http::http_request req_;
};

}  // namespace delete_
}  // namespace chatgpt_client_cpp::v1::threads
#endif  // CHATGPT_CLIENT_CPP_THREADS_HPP_
