#include <string>
#include <gtest/gtest.h>
#include "chatgpt_client_cpp/messages.hpp"


using namespace chatgpt_client_cpp::v1::messages;

TEST(CreateBuilderTest, Build)
{
  // setup
  // nothing to do

  // exercise
  auto req = create::Builder()
    .thread_id("thread_abc123")
    .body(create::body::MessageBuilder()
        .role("user")
        .content(create::body::TextContentBuilder()
          .text("How does AI work? Explain it in simple terms.")
          .build())
        .build())
    .build();

  // verify
  EXPECT_STREQ("v1/threads/thread_abc123/messages", req.absolute_uri().to_string().c_str());
  EXPECT_STREQ(web::http::methods::POST.c_str(), req.method().c_str());
  ASSERT_STREQ(
      "{"
        "\"content\":"
          "["
            "{"
              "\"text\":\"How does AI work? Explain it in simple terms.\","
              "\"type\":\"text\""
            "}"
          "],"
        "\"role\":\"user\""
      "}",
      req.extract_json().get().serialize().c_str());
}

TEST(ListBuilderTest, Build)
{
  // setup
  // nothing to do

  // exercise
  auto req = list::Builder()
    .thread_id("thread_abc123")
    .build();

  // verify
  EXPECT_STREQ("v1/threads/thread_abc123/messages", req.absolute_uri().to_string().c_str());
  EXPECT_STREQ(web::http::methods::GET.c_str(), req.method().c_str());
}

TEST(RetrieveBuilderTest, Build1)
{
  // setup
  // nothing to do

  // exercise
  auto req = retrieve::Builder()
    .thread_id("thread_abc123")
    .message_id("msg_abc123")
    .build();

  // verify
  EXPECT_STREQ("v1/threads/thread_abc123/messages/msg_abc123", req.absolute_uri().to_string().c_str());
  EXPECT_STREQ(web::http::methods::GET.c_str(), req.method().c_str());
}

TEST(RetrieveBuilderTest, Build2)
{
  // setup
  // nothing to do

  // exercise
  auto req = retrieve::Builder()
    .message_id("msg_abc123")
    .thread_id("thread_abc123")
    .build();

  // verify
  EXPECT_STREQ("v1/threads/thread_abc123/messages/msg_abc123", req.absolute_uri().to_string().c_str());
  EXPECT_STREQ(web::http::methods::GET.c_str(), req.method().c_str());
}

TEST(DeleteBuilderTest, Build1)
{
  // setup
  // nothing to do

  // exercise
  auto req = delete_::Builder()
    .thread_id("thread_abc123")
    .message_id("msg_abc123")
    .build();

  // verify
  EXPECT_STREQ("v1/threads/thread_abc123/messages/msg_abc123", req.absolute_uri().to_string().c_str());
  EXPECT_STREQ(web::http::methods::DEL.c_str(), req.method().c_str());
}

TEST(DeleteBuilderTest, Build2)
{
  // setup
  // nothing to do

  // exercise
  auto req = delete_::Builder()
    .message_id("msg_abc123")
    .thread_id("thread_abc123")
    .build();

  // verify
  EXPECT_STREQ("v1/threads/thread_abc123/messages/msg_abc123", req.absolute_uri().to_string().c_str());
  EXPECT_STREQ(web::http::methods::DEL.c_str(), req.method().c_str());
}
