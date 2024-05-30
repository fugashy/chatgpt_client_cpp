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
  std::string image_url = "https://upload.wikimedia.org/wikipedia/commons/thumb/d/dd/Gfp-wisconsin-madison-the-nature-boardwalk.jpg/2560px-Gfp-wisconsin-madison-the-nature-boardwalk.jpg";
  if (argc > 1)
  {
    text = argv[1];
  }
  if (argc > 2)
  {
    image_url = argv[2];
  }
  std::cout << "argument num: " << argc << std::endl;
  std::cout << "text        : " << text << std::endl;
  std::cout << "image url   : " << image_url << std::endl;

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
                .url(image_url)
                .get())
              .get())
          .get())
        .max_tokens(300)
        .get())
    .get();

  const auto res = Client::GetInstance().Request<Client::OptionalJson>(req);

  std::cout << "res :" << res.value().serialize() << std::endl;

  return EXIT_SUCCESS;
}
