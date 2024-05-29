#include <string>
#include <gtest/gtest.h>
#include "chatgpt_client_cpp/messages.hpp"


using chatgpt_client_cpp::messages::ChatBodyBuilder;;
using chatgpt_client_cpp::messages::MessageElementBuilder;;
using chatgpt_client_cpp::messages::ContentTextPartBuilder;
using chatgpt_client_cpp::messages::ContentImageUriPartBuilder;
using chatgpt_client_cpp::messages::ImageUriBuilder;


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

TEST(ChatBodyBuilderTest, BuildRequiredContent)
{
  // setup
  // nothing to do

  // exercise
  const auto request = ChatBodyBuilder()
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
