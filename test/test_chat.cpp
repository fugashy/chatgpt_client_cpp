#include <string>
#include <gtest/gtest.h>
#include "chatgpt_client_cpp/chat.hpp"


using chatgpt_client_cpp::v1::chat::Builder;
using BodyBuilder = chatgpt_client_cpp::v1::chat::body::Builder;;
using chatgpt_client_cpp::v1::chat::body::MessageElementBuilder;;
using chatgpt_client_cpp::v1::chat::body::ContentTextPartBuilder;
using chatgpt_client_cpp::v1::chat::body::ContentImageUriPartBuilder;
using chatgpt_client_cpp::v1::chat::body::ImageUriBuilder;


TEST(ContentTextPartBuilderTest, BuildRequiredContent)
{
  // setup
  // nothing to do

  // exercise
  auto request = ContentTextPartBuilder()
    .type("text")
    .text("hello")
    .get();

  // verify
  ASSERT_TRUE(request.has_field("type"));
  EXPECT_STREQ("text", request["type"].as_string().c_str());
  ASSERT_TRUE(request.has_field("text"));
  EXPECT_STREQ("hello", request["text"].as_string().c_str());
  ASSERT_STREQ(
      "{\"text\":\"hello\",\"type\":\"text\"}",
      request.serialize().c_str());
}


TEST(ContentImageUriPartBuilderTest, BuildRequiredContent)
{
  // setup
  // nothing to do

  // exercise
  auto request = ContentImageUriPartBuilder()
    .type("image_uri")
    .image_uri(ImageUriBuilder()
        .uri("https://hoge.com")
        .detail("dummy")
        .get())
    .get();

  // verify
  ASSERT_TRUE(request.has_field("type"));
  EXPECT_STREQ("image_uri", request["type"].as_string().c_str());
  ASSERT_TRUE(request.has_field("image_uri"));
  EXPECT_STREQ("https://hoge.com", request["image_uri"]["uri"].as_string().c_str());
  EXPECT_STREQ("dummy", request["image_uri"]["detail"].as_string().c_str());
  ASSERT_STREQ(
      "{\"image_uri\":{\"detail\":\"dummy\",\"uri\":\"https://hoge.com\"},\"type\":\"image_uri\"}",
      request.serialize().c_str());
}

TEST(MessageElementBuilderTest, BuildRequiredContent)
{
  // setup
  // nothing to do

  // exercise
  const auto request = MessageElementBuilder()
    .role("user")
    .content(ContentTextPartBuilder()
        .type("text")
        .text("hello")
        .get())
    .content(ContentImageUriPartBuilder()
        .type("image_uri")
        .image_uri(ImageUriBuilder()
          .uri("https://hoge.com")
          .detail("dummy")
          .get())
        .get())
    .get();

  // verify
  std::cerr << request.serialize().c_str() << std::endl;
}

TEST(BodyBuilderTest, BuildRequiredContent)
{
  // setup
  // nothing to do

  // exercise
  const auto request = BodyBuilder()
    .model("gpt-4-turbo")
    .message(MessageElementBuilder()
      .role("user")
      .content(ContentTextPartBuilder()
          .type("text")
          .text("hello")
          .get())
      .content(ContentImageUriPartBuilder()
          .type("image_uri")
          .image_uri(ImageUriBuilder()
            .uri("https://hoge.com")
            .detail("dummy")
            .get())
          .get())
      .get())
    .max_tokens(30)
    .get();

  // verify
  std::cerr << request.serialize().c_str() << std::endl;
}

TEST(ChatRequestTest, BuildRequired)
{
  // setup
  // nothing to do

  // exercise
  const auto req = Builder()
    .body(BodyBuilder()
        .model("gpt-4-turbo")
        .message(MessageElementBuilder()
          .role("user")
          .content(ContentTextPartBuilder()
              .type("text")
              .text("hello")
              .get())
          .content(ContentImageUriPartBuilder()
              .type("image_uri")
              .image_uri(ImageUriBuilder()
                .uri("https://hoge.com")
                .detail("dummy")
                .get())
              .get())
          .get())
        .max_tokens(30)
        .get())
    .get();

  // verify
  EXPECT_STREQ(web::http::methods::POST.c_str(), req.method().c_str());
  EXPECT_STREQ("v1/chat/completions", req.request_uri().to_string().c_str());
  web::http::http_headers req_headers = req.headers();
  EXPECT_EQ(3, req_headers.size());
  // TODO(fugashy) inspect headers
}

