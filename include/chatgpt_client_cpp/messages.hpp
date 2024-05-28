#ifndef CHATGPT_CLIENT_CPP_MESSAGES_HPP_
#define CHATGPT_CLIENT_CPP_MESSAGES_HPP_
#include <cpprest/json.h>

namespace chatgpt_client_cpp::messages
{

class MessageBuilder
{
public:
  MessageBuilder();
private:
 web::json::value message_;
};


class ContentTextPartBuilder
{
public:
  ContentTextPartBuilder() = default;
  ~ContentTextPartBuilder() = default;

  ContentTextPartBuilder* type(const utility::string_t& type);
  ContentTextPartBuilder* text(const utility::string_t& text);

  web::json::value get() const;

private:
  web::json::value json_;
};


}  // namespace chatgpt_client_cpp::messages
#endif  // CHATGPT_CLIENT_CPP_MESSAGES_HPP_
