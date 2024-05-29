#ifndef CHATGPT_CLIENT_CPP_REQUEST_HPP_
#define CHATGPT_CLIENT_CPP_REQUEST_HPP_
#include <memory>

#include <cpprest/http_msg.h>
#include <cpprest/json.h>

namespace chatgpt_client_cpp::request
{

namespace v1
{

namespace chat {

class Builder
{
public:
  using SharedPtr = std::shared_ptr<Builder>;

  Builder() noexcept(false);
  virtual ~Builder() = default;

  web::http::http_request get() const noexcept;

  Builder* body(const web::json::value& body);

private:
  web::http::http_request req_;
};


}  // namespace chat
}  // namespace v1
}  // namespace chatgpt_client_cpp::request
#endif  // CHATGPT_CLIENT_CPP_REQUEST_HPP_
