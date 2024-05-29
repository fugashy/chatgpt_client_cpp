#ifndef CHATGPT_CLIENT_CPP_CLIENT_HPP_
#define CHATGPT_CLIENT_CPP_CLIENT_HPP_
#include <memory>
#include <functional>
#include <optional>

#include <pplx/pplxtasks.h>
#include <cpprest/http_msg.h>
#include <cpprest/json.h>

namespace chatgpt_client_cpp::client
{

/**
 * @brief A client class for handlingk requests and responses to/from VOICEVOX.
 */
class Client
{
public:
  /**
   * @brief Responses from the client (in JSON format).
   */
  using OptionalJson = std::optional<web::json::value>;

  /**
   * @brief User callback type
   *
   * @tparam T Response type
   */
  template<class T>
  using CallbackType = std::function<void(const T&)>;

  /**
   * @brief Copy constructor (deleted)
   *
   * @param Client
   */
  Client(const Client&) = delete;

  /**
   * @brief Copy constructor (deleted)
   *
   * @param Client
   *
   * @return 
   */
  Client& operator=(const Client&) = delete;

  /**
   * @brief The only interface for obtaining the client.
   *
   * @param uri URI of VOICEVOX
   *
   * @return An instance of the client.
   */
  static Client& GetInstance();

  /**
   * @brief An interface for sending supplies to the server and receiving responses asynchronously.
   *
   * @param req A request for the server
   * @param callback_json A function to call when processing is complete (in JSON format)
   *
   * @return A task handler
   */
  pplx::task<void> Request(
      const web::http::http_request& req,
      const CallbackType<OptionalJson> callback_json);

  /**
   * @brief An interface for sending requests to the server and receiving responses synchronously.
   *
   * @tparam T The response type
   * @param req The request for the server
   *
   * @return The response
   */
  template<class T>
  T Request(const web::http::http_request& req)
  {
    T out;
    auto callback = [&out](const T& in) { out = in; };
    auto task = Request(req, callback);
    task.wait();
    return out;
  }

private:
  /**
   * @brief Constructor
   *
   * @param uri A URI of the server
   */
  Client(const std::string& uri);

  /**
   * @brief Destructor
   */
  ~Client() = default;

  /**
   * @brief A client object
   */
  std::unique_ptr<web::http::client::http_client> client_;
};
}  // namespace chatgpt_client_cpp::client
#endif  // CHATGPT_CLIENT_CPP_CLIENT_HPP_
