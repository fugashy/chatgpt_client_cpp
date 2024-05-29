#include "chatgpt_client_cpp/chatgpt_client_cpp.hpp"


using chatgpt_client_cpp::client::Client;
using ReqBuilder = chatgpt_client_cpp::v1::chat::Builder;
using ReqBodyBuilder = chatgpt_client_cpp::v1::chat::body::Builder;;
using chatgpt_client_cpp::v1::chat::body::MessageElementBuilder;;
using chatgpt_client_cpp::v1::chat::body::ContentTextPartBuilder;
using chatgpt_client_cpp::v1::chat::body::ContentImageUrlPartBuilder;
using chatgpt_client_cpp::v1::chat::body::ImageUrlBuilder;


int main(int argc, char** argv)
{
  std::string text = "なにが写っていますか";
  if (argc > 1)
  {
    text = argv[1];
  }
  std::cout << "input: " << text << std::endl;

  const auto req = ReqBuilder()
    .body(ReqBodyBuilder()
        .model("gpt-4o")
        .message(MessageElementBuilder()
          .role("user")
          .content(ContentTextPartBuilder()
              .type("text")
              .text(text)
              .get())
          .content(ContentImageUrlPartBuilder()
              .type("image_url")
              .image_url(ImageUrlBuilder()
                .url("https://upload.wikimedia.org/wikipedia/commons/thumb/d/dd/Gfp-wisconsin-madison-the-nature-boardwalk.jpg/2560px-Gfp-wisconsin-madison-the-nature-boardwalk.jpg")
                .get())
              .get())
          .get())
        .max_tokens(30)
        .get())
    .get();

  const auto res = Client::GetInstance().Request<Client::OptionalJson>(req);

  std::cout << "res :" << res.value().serialize() << std::endl;

  return EXIT_SUCCESS;
}
