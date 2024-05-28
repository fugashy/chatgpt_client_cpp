#ifndef CHATGPT_CLIENT_CPP_REQUEST_HPP_
#define CHATGPT_CLIENT_CPP_REQUEST_HPP_
#include <memory>

#include <cpprest/http_msg.h>
#include <cpprest/json.h>

namespace chatgpt_client_cpp::request
{

namespace v1
{

class BuilderBase
{
public:
  using SharedPtr = std::shared_ptr<BuilderBase>;

  BuilderBase() noexcept(false);
  virtual ~BuilderBase() = default;

  web::http::http_request get() noexcept;

protected:
  BuilderBase* method(const web::http::method& method);
  BuilderBase* header(const utility::string_t& key, const utility::string_t& value);
  BuilderBase* body(const web::json::value& body);

  web::http::uri_builder uri_builder_;
  web::http::http_request req_;

};

namespace chat
{


}  // namespace chat
}  // namespace v1
}  // namespace chatgpt_client_cpp::request
#endif  // CHATGPT_CLIENT_CPP_REQUEST_HPP_
