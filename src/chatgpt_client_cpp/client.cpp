#include "chatgpt_client_cpp/client.hpp"

#include <string>

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

namespace chatgpt_client_cpp::client
{

Client& Client::GetInstance()
{
  static Client instance("https://api.openai.com");
  return instance;
}

Client::Client(const std::string& uri)
  : client_(new web::http::client::http_client(uri))
{
}

pplx::task<void> Client::Request(
    const web::http::http_request& req,
    const CallbackType<OptionalJson> callback)
{
  return pplx::create_task(
      [this, req, callback]()
      {
        return this->client_->request(req);
      })
    .then(
        [callback](const web::http::http_response& res)
        {
          if (res.status_code() != web::http::status_codes::OK)
          {
            std::cerr << "[chatgpt] Unexpected status code" << std::endl;
            callback(std::nullopt);
            return;
          }

          const auto content_type = res.headers().content_type();
          if (content_type == "application/json")
          {
            const web::json::value json = res.extract_json().get();
            callback(json);
          }
          else
          {
            std::cerr << "[chatgpt] Unknown content type: " << content_type << std::endl;
            callback(web::json::value());
          }
        });
}

}  // namespace chatgpt_client_cpp::client
