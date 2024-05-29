#include "chatgpt_client_cpp/chatgpt_client_cpp.hpp"


using chatgpt_client_cpp::client::Client;
using ReqBuilder = chatgpt_client_cpp::v1::chat::Builder;
using ReqBodyBuilder = chatgpt_client_cpp::v1::chat::body::Builder;;
using chatgpt_client_cpp::v1::chat::body::MessageElementBuilder;;
using chatgpt_client_cpp::v1::chat::body::ContentTextPartBuilder;
using chatgpt_client_cpp::v1::chat::body::ContentImageUriPartBuilder;
using chatgpt_client_cpp::v1::chat::body::ImageUriBuilder;


int main(int argc, char** argv)
{
  std::string text = "こんにちは";
  if (argc > 1)
  {
    text = argv[1];
  }
  std::cout << "input: " << text << std::endl;

  const auto req = ReqBuilder()
    .body(ReqBodyBuilder()
        .model("gpt-3.5-turbo")
        .message(MessageElementBuilder()
          .role("user")
          .content(ContentTextPartBuilder()
              .type("text")
              .text(text)
              .get())
          .get())
        .max_tokens(30)
        .get())
    .get();

  const auto res = Client::GetInstance().Request<Client::OptionalJson>(req);

  std::cout << "res :" << res.value().serialize() << std::endl;

  return EXIT_SUCCESS;
}
