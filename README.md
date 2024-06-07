# chargpt_client_cpp

A CHATGPT client library implemented in C++

# Supported API

- [ ] Audio

- [ ] Chat

  - [x] Chat Completion

  - [ ] Chat Completion Object

  - [ ] Chat Completion Chunk Object

- [ ] Embeddings

- [ ] Fine-Tuning

- [ ] Batch

- [ ] Files

- [ ] Images

- [ ] Models

- [ ] Moderations

- [ ] Assistancts

- [ ] Threads

  - [x] Create

  - [x] Retrive

  - [ ] Modify

  - [x] Delete

- [ ] Messages

- [ ] Runs

- [ ] Run Steps

- [ ] Vector Stores

- [ ] Vector Store Files

- [ ] Vector Store File Batches

- [ ] Streaming

# Operating environment for verification

- macOS Sonoma 14.5

# Required

- C++ 17

- cpprestsdk

  https://github.com/microsoft/cpprestsdk

# How to build

```bash
mkdir build
cd build
cmake ..
make install
```

# Sample code

```cpp
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

  // Here's an example using a synchronous interface to obtain responses.
  // Asynchronous interface is also provided by client class

  // Build a request
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

  // Send a request then get a response
  const auto res = Client::GetInstance().Request<Client::OptionalJson>(req);

  std::cout << "res :" << res.value().serialize() << std::endl;

  return EXIT_SUCCESS;
}
```

# Sample executables

- chatgpt_client_cpp_sample_chat

```bash
chatgpt_client_cpp_sample_chat \
  こんにちは．日本の名所を教えて下さい．

> res :{"choices":[{"finish_reason":"length","index":0,"logprobs":null,"message":{"content":"こんにちは！ 日本にはたくさんの名所がありますが、代表的なものをいくつか紹介しますね。\n\n1. 京都：日本の歴史や文化が 色濃く残る京都は、多くの寺院や神社が点在する観光地として有名です。清水寺や金閣寺、伏見稲荷大社などが人気の観光スポットです。\n\n2. 東京：日本の首都であり、繁華な都市東京にも多くの名所があります。東京タワーや 浅草寺、新宿御苑などが代表的な観光地です。\n\n3. 富士山：日本を代表する観光スポットといえば、やはり富士 山です。日本最高峰の富士山は、美しい形状と四季折々の景色で多くの観光客を魅了しています。\n\nこれ以外にも、日本には多くの素晴らしい","role":"assistant"}}],"created":1717027020,"id":"chatcmpl-9UNS8Jslac0l9vwujR6Imh0YMYgzv","model":"gpt-3.5-turbo-0125","object":"chat.completion","system_fingerprint":null,"usage":{"completion_tokens":300,"prompt_tokens":22,"total_tokens":322}}
```

- chatgpt_client_cpp_sample_chat_with_image_uri

```bash
chatgpt_client_cpp_sample_chat_with_image_uri \
  こんにちは．何が写っていますか
  https://upload.wikimedia.org/wikipedia/commons/4/46/Leadenhall_Market_In_London_-_Feb_2006_rotated.jpg
> argument num: 3
> text        : こんにちは．何が写っていますか
> image url   : https://upload.wikimedia.org/wikipedia/commons/4/46/Leadenhall_Market_In_London_-_Feb_2006_rotated.jpg
> res :{"choices":[{"finish_reason":"stop","index":0,"logprobs":null,"message":{"content":"こんにちは。こ の写真には美しいアーケード商店街が映っています。写真の建物は歴史的で装飾が施されたアーケードで、天井はガラスと鉄の構造になっています。道の両脇に様々な店が並んでいます。また、いくつかの人々が道を歩いている様子も見えます。商業施設や観光地である可能性が高いです。","role":"assistant"}}],"created":1717026752,"id":"chatcmpl-9UNNo4U1Kr5wwbtlilVKwz30G7ZWK","model":"gpt-4o-2024-05-13","object":"chat.completion","system_fingerprint":"fp_aa87380ac5","usage":{"completion_tokens":105,"prompt_tokens":1119,"total_tokens":1224}}
```
