#include <string>
#include <gtest/gtest.h>
#include "chatgpt_client_cpp/assistants.hpp"


using namespace chatgpt_client_cpp::v1::assistants;

TEST(CreateBuilderTest, Build)
{
  // setup
  // nothing to do

  // exercise
  auto req = create::Builder()
    .body(create::body::Builder()
        .model("gpt-4o")
        .name("AI")
        .description("The AI assistant")
        .instructions("You are an assistant")
        .build())
    .build();

  // verify
  EXPECT_STREQ("v1/assistants", req.absolute_uri().to_string().c_str());
  EXPECT_STREQ(web::http::methods::POST.c_str(), req.method().c_str());
  ASSERT_STREQ(
      "{"
        "\"description\":\"The AI assistant\","
        "\"instructions\":\"You are an assistant\","
        "\"model\":\"gpt-4o\","
        "\"name\":\"AI\","
        "\"tools\":[]"
      "}",
      req.extract_json().get().serialize().c_str());
}

TEST(ListBuilderTest, Build)
{
  // setup
  // nothing to do
  auto builder = list::Builder();

  // exercise
  auto req = builder.build();

  // verify
  EXPECT_STREQ("v1/assistants", req.absolute_uri().to_string().c_str());
  EXPECT_STREQ(web::http::methods::GET.c_str(), req.method().c_str());
}

TEST(RetrieveBuilderTest, Build)
{
  // setup
  // nothing to do

  // exercise
  auto req = retrieve::Builder()
    .assistant_id("assistant_abc123")
    .build();

  // verify
  EXPECT_STREQ("v1/assistants/assistant_abc123", req.absolute_uri().to_string().c_str());
  EXPECT_STREQ(web::http::methods::GET.c_str(), req.method().c_str());
}

TEST(ModifyBuilderTest, Build)
{
  // setup
  // nothing to do

  // exercise
  auto req = modify::Builder()
    .assistant_id("assistant_abc123")
    .body(modify::body::Builder()
        .model("gpt-3.5")
        .build())
    .build();

  // verify
  EXPECT_STREQ("v1/assistants/assistant_abc123", req.absolute_uri().to_string().c_str());
  EXPECT_STREQ(web::http::methods::POST.c_str(), req.method().c_str());
  ASSERT_STREQ(
      "{\"model\":\"gpt-3.5\",\"tools\":[]}",
      req.extract_json().get().serialize().c_str());
}

TEST(DeleteBuilderTest, Build)
{
  // setup
  // nothing to do

  // exercise
  auto req = delete_::Builder()
    .assistant_id("assistant_abc123")
    .build();

  // verify
  EXPECT_STREQ("v1/assistants/assistant_abc123", req.absolute_uri().to_string().c_str());
  EXPECT_STREQ(web::http::methods::DEL.c_str(), req.method().c_str());
  ASSERT_STREQ(
      "null",
      req.extract_json().get().serialize().c_str());
}
