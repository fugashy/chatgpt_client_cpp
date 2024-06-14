#ifndef CHATGPT_CLIENT_CPP_RUNS_HPP_
#define CHATGPT_CLIENT_CPP_RUNS_HPP_
#include <cpprest/http_msg.h>
#include <cpprest/json.h>

#include "chatgpt_client_cpp/client.hpp"
#include "chatgpt_client_cpp/helper_base.hpp"

namespace chatgpt_client_cpp::v1::runs
{

class Runs final : public ApiHelper, public WaitInterface
{
public:
  Runs(
      const ApiHelper::Pargs& pargs = ApiHelper::Pargs());
  ~Runs() = default;

  bool Wait() override;

protected:
  ObjectHelper::SharedPtr InitializeObject(const ApiHelper::Pargs& pargs) override;
  void DestructObject() override {};

private:
};

namespace create
{
class Builder
{
public:
  Builder();
  ~Builder() = default;

  Builder& thread_id(const utility::string_t& thread_id);
  Builder& body(const web::json::value& body);
  web::http::http_request build();
  // optional parameters are not implemented yet...
private:
  web::http::uri_builder uri_builder_;
  web::http::http_request req_;
};

namespace body
{

class Builder
{
public:
  Builder() = default;
  ~Builder() = default;
  Builder& assistant_id(const utility::string_t& assistant_id);
  web::json::value build();

private:
  web::json::value json_;
};

}  // body
}  // namespace create

namespace create_thread_and_run
{
}

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

}

namespace retrieve
{
class Builder
{
public:
  Builder();
  ~Builder() = default;

  Builder& thread_id(const utility::string_t& thread_id);
  Builder& run_id(const utility::string_t& assistant_id);
  web::http::http_request build();

  // optional parameters are not implemented yet...
private:
  web::http::uri_builder uri_builder_;
  web::http::http_request req_;

  utility::string_t thread_id_;
  utility::string_t run_id_;
};
}  // namespace retrieve
namespace modify
{
}  // namespace modify
namespace submit_tool_outputs
{
}  // namespace submit_tool_outputs
namespace cancel
{
class Builder
{
public:
  Builder();
  ~Builder() = default;

  Builder& thread_id(const utility::string_t& thread_id);
  Builder& run_id(const utility::string_t& assistant_id);
  web::http::http_request build();

private:
  web::http::uri_builder uri_builder_;
  web::http::http_request req_;

  utility::string_t thread_id_;
  utility::string_t run_id_;
};
}  // namespace cancel
}  // namespace chatgpt_client_cpp::v1::runs
#endif  // CHATGPT_CLIENT_CPP_RUNS_HPP_
