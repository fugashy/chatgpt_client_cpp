#include "chatgpt_client_cpp/chatgpt_client_cpp.hpp"

using namespace chatgpt_client_cpp;
using namespace chatgpt_client_cpp::v1;


int main(int argc, char** argv)
{

  auto req_create = threads::create::Builder()
    .body(threads::create::body::Builder()
      .message(threads::create::body::MessageBuilder()
        .role("user")
        .content(threads::create::body::TextContentBuilder()
          .text("hello ai")
          .get())
        .get())
      .message(threads::create::body::MessageBuilder()
        .role("assistant")
        .content(threads::create::body::TextContentBuilder()
          .text("you are ai")
          .get())
        .get())
      .get())
    .get();

  auto res_create = client::Client::GetInstance().
    Request<client::Client::OptionalJson>(req_create);
  if (res_create == std::nullopt)
  {
    std::cerr << "failed to request for creation threads" << std::endl;
    return EXIT_FAILURE;
  }
  std::cout << "res create :" << res_create.value().serialize() << std::endl;
  const auto thread_id = res_create.value()["id"].as_string();
  std::cout << "thread id: " << thread_id << std::endl;

  auto req_retrieve = threads::retrieve::Builder()
    .thread_id(thread_id)
    .get();
  auto res_retrieve = client::Client::GetInstance().
    Request<client::Client::OptionalJson>(req_retrieve);
  if (res_retrieve == std::nullopt)
  {
    std::cerr << "failed to request for get threads" << std::endl;
    return EXIT_FAILURE;
  }

  auto req_delete = threads::delete_::Builder()
    .thread_id(thread_id)
    .get();
  auto res_delete = client::Client::GetInstance().
    Request<client::Client::OptionalJson>(req_delete);
  if (res_delete == std::nullopt)
  {
    std::cerr << "failed to request for delete threads" << std::endl;
    return EXIT_FAILURE;
  }
  std::cout << "deleted: " << res_delete.value()["deleted"].as_bool() << std::endl;

  return EXIT_SUCCESS;
}
