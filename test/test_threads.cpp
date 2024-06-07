#include <string>
#include <gtest/gtest.h>
#include "chatgpt_client_cpp/threads.hpp"


using namespace chatgpt_client_cpp::v1::threads;

TEST(TextContentBuilderTest, Build)
{
  // setup
  // nothing to do

  // exercise
  auto req = create::body::TextContentBuilder()
    .text("hello ai")
    .build();

  // verify
  ASSERT_STREQ(
      "{\"text\":\"hello ai\",\"type\":\"text\"}",
      req.serialize().c_str());
}

TEST(MessageBuilderTest, Build)
{
  // setup
  // nothing to do

  // exercise
  auto req = create::body::MessageBuilder()
    .role("user")
    .content(create::body::TextContentBuilder()
        .text("hello ai")
        .build())
    .build();

  // verify
  ASSERT_STREQ(
      "{"
        "\"content\":"
          "["
            "{\"text\":\"hello ai\",\"type\":\"text\"}"
          "],"
        "\"role\":"
          "\"user\""
      "}",
      req.serialize().c_str());
}

TEST(BodyBuilderTest, Build)
{
  // setup
  // nothing to do

  // exercise
  auto req = create::body::Builder()
    .message(create::body::MessageBuilder()
      .role("user")
      .content(create::body::TextContentBuilder()
        .text("hello ai")
        .build())
      .build())
    .message(create::body::MessageBuilder()
      .role("assistant")
      .content(create::body::TextContentBuilder()
        .text("you are ai")
        .build())
      .build())
    .build();

  // verify
  ASSERT_STREQ(
      "{"
        "\"messages\":"
          "["
            "{\"content\":[{\"text\":\"hello ai\",\"type\":\"text\"}],\"role\":\"user\"},"
            "{\"content\":[{\"text\":\"you are ai\",\"type\":\"text\"}],\"role\":\"assistant\"}"
          "]"
      "}",
      req.serialize().c_str());
}

TEST(CreateThreadBuilderTest, Build)
{
  // setup
  // nothing to do

  // exercise
  auto req = create::Builder()
    .body(create::body::Builder()
      .message(create::body::MessageBuilder()
        .role("user")
        .content(create::body::TextContentBuilder()
          .text("hello ai")
          .build())
        .build())
      .message(create::body::MessageBuilder()
        .role("assistant")
        .content(create::body::TextContentBuilder()
          .text("you are ai")
          .build())
        .build())
      .build())
    .build();

  // verify
  EXPECT_STREQ(web::http::methods::POST.c_str(), req.method().c_str());
  EXPECT_STREQ("v1/threads", req.request_uri().to_string().c_str());
  for (auto it = req.headers().begin(); it != req.headers().end(); ++it)
  {
    std::cerr << it->first << ": " << it->second << std::endl;
  }
  const auto body = req.extract_json().get().serialize();
  EXPECT_STREQ(
      "{\"messages\":[{\"content\":[{\"text\":\"hello ai\",\"type\":\"text\"}],\"role\":\"user\"},{\"content\":[{\"text\":\"you are ai\",\"type\":\"text\"}],\"role\":\"assistant\"}]}",
      body.c_str());
}

TEST(RetrieveBuilderTest, Build)
{
  // setup
  const char* const thread_id = "thread_abc123";

  // exercise
  auto req = retrieve::Builder()
    .thread_id(thread_id)
    .build();

  // verify
  EXPECT_STREQ(web::http::methods::GET.c_str(), req.method().c_str());
  EXPECT_STREQ("v1/threads/thread_abc123", req.request_uri().to_string().c_str());
}
