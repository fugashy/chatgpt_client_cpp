#include <string>
#include <gtest/gtest.h>
#include "chatgpt_client_cpp/runs.hpp"


using namespace chatgpt_client_cpp::v1::runs;

TEST(CreateBuilderTest, Build)
{
  // setup
  // nothing to do

  // exercise
  auto req = create::Builder()
    .thread_id("thread_abc123")
    .body(create::body::Builder()
        .assistant_id("asst_abc123")
        .build())
    .build();

  // verify
  EXPECT_STREQ("v1/threads/thread_abc123/runs", req.absolute_uri().to_string().c_str());
  EXPECT_STREQ(web::http::methods::POST.c_str(), req.method().c_str());
  ASSERT_STREQ(
      "{\"assistant_id\":\"asst_abc123\"}",
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
  EXPECT_STREQ("v1/threads/thread_abc123/runs", req.absolute_uri().to_string().c_str());
  EXPECT_STREQ(web::http::methods::GET.c_str(), req.method().c_str());
}

TEST(RetrieveBuilderTest, Build1)
{
  // setup
  // nothing to do

  // exercise
  auto req = retrieve::Builder()
    .thread_id("thread_abc123")
    .run_id("run_abc123")
    .build();

  // verify
  EXPECT_STREQ("v1/threads/thread_abc123/runs/run_abc123", req.absolute_uri().to_string().c_str());
  EXPECT_STREQ(web::http::methods::GET.c_str(), req.method().c_str());
}

TEST(RetrieveBuilderTest, Build2)
{
  // setup
  // nothing to do

  // exercise
  auto req = retrieve::Builder()
    .run_id("run_abc123")
    .thread_id("thread_abc123")
    .build();

  // verify
  EXPECT_STREQ("v1/threads/thread_abc123/runs/run_abc123", req.absolute_uri().to_string().c_str());
  EXPECT_STREQ(web::http::methods::GET.c_str(), req.method().c_str());
}

TEST(CancelBuilderTest, Build2)
{
  // setup
  // nothing to do

  // exercise
  auto req = cancel::Builder()
    .run_id("run_abc123")
    .thread_id("thread_abc123")
    .build();

  // verify
  EXPECT_STREQ("v1/threads/thread_abc123/runs/run_abc123", req.absolute_uri().to_string().c_str());
  EXPECT_STREQ(web::http::methods::POST.c_str(), req.method().c_str());
}
