#ifndef CHATGPT_CLIENT_CPP_ASSISTANTS_HPP_
#define CHATGPT_CLIENT_CPP_ASSISTANTS_HPP_
#include <cpprest/http_msg.h>
#include <cpprest/json.h>


namespace chatgpt_client_cpp::v1::assistants
{
namespace create
{
class Builder
{
public:
  Builder();
  ~Builder() = default;

  Builder& body(const web::json::value& body);
  web::http::http_request build();

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
  web::json::value build();
  Builder& model(const utility::string_t& model);
  Builder& name(const utility::string_t& name);
  Builder& description(const utility::string_t& description);
  Builder& instructions(const utility::string_t& instructions);
  Builder& response_format(const utility::string_t& response_format);

  Builder& tool(const web::json::value& tool)
  {
    std::cerr << "tool is not implemented..." << std::endl;
    return *this;
  }

  Builder& metadata(const web::json::value& tool)
  {
    std::cerr << "metadata is not implemented..." << std::endl;
    return *this;
  }

  Builder& temperature(const double temperature)
  {
    std::cerr << "temperature is not implemented..." << std::endl;
    return *this;
  }

  Builder& top_p(const double top_p)
  {
    std::cerr << "top_p is not implemented..." << std::endl;
    return *this;
  }

private:
  web::json::value json_;
};
}  // namespace body
}  // namespace create

namespace list
{

class Builder
{
public:
  Builder();
  ~Builder() = default;
  web::http::http_request build();
  // optional parameters are not implemented...

private:
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

  Builder& assistant_id(const utility::string_t& assistant_id);
  web::http::http_request build();

private:
  web::http::uri_builder uri_builder_;
  web::http::http_request req_;
};

}  // namespace retrive

namespace modify
{

class Builder
{
public:
  Builder();
  ~Builder() = default;

  Builder& assistant_id(const utility::string_t& assistant_id);
  Builder& body(const web::json::value& body);
  web::http::http_request build();

private:
  web::http::uri_builder uri_builder_;
  web::http::http_request req_;
};

namespace body
{
using Builder = chatgpt_client_cpp::v1::assistants::create::body::Builder;
}  // namespace body
}  // namespace modify

namespace delete_
{

class Builder
{
public:
  Builder();
  ~Builder() = default;

  Builder& assistant_id(const utility::string_t& assistant_id);
  web::http::http_request build();

private:
  web::http::uri_builder uri_builder_;
  web::http::http_request req_;
};

}  // namespace delete_
}  // namespace chatgpt_client_cpp::v1::assistants
#endif  // CHATGPT_CLIENT_CPP_ASSISTANTS_HPP_
