#include "chatgpt_client_cpp/chatgpt_client_cpp.hpp"

using namespace chatgpt_client_cpp;
using namespace chatgpt_client_cpp::v1;


// スレッド
class Thread
{
public:
  Thread(const bool delete_when_terminated = false) noexcept(false)
    : delete_when_terminated_(delete_when_terminated)
  {
    auto req = threads::create::Builder().build();
    auto res = client::Client::GetInstance().Request<client::Client::OptionalJson>(req);
    if (res == std::nullopt)
    {
      throw std::runtime_error("failed to request for creation threads");
    }

    res_ = res.value();
    id_ = res.value()["id"].as_string();
    std::cout << "create a thread(" << id_.c_str() << ")" << std::endl;
  }

  ~Thread()
  {
    if (!delete_when_terminated_) return;

    auto req = threads::delete_::Builder()
      .thread_id(id_)
      .build();
    auto res = client::Client::GetInstance().Request<client::Client::OptionalJson>(req);
    if (res == std::nullopt)
    {
      std::cerr << "failed to get response for deletion the thread(" << id_.c_str() << ")" << std::endl;
    }
    if (!res.value()["deleted"].as_bool())
    {
      std::cerr << "failed to delete for thread(" << id_.c_str() << ")" << std::endl;
    }
    std::cout << "delete the thread(" << id_.c_str() << ")" << std::endl;
  }

  std::map<std::string, std::string> GetMessages() const
  {
    auto req = messages::list::Builder()
      .thread_id(id_)
      .build();
    auto res = client::Client::GetInstance().Request<client::Client::OptionalJson>(req);
    if (res == std::nullopt)
    {
      std::cerr << "failed to get response for list messages in the thread(" << id_.c_str() << ")" << std::endl;
      return std::map<std::string, std::string>();
    }
    std::map<std::string, std::string> out;
    for (auto e : res.value()["data"].as_array())
    {
      out.insert({
          e["role"].as_string(),
          e["content"][0]["text"]["value"].as_string()});
    }
    return out;
  }

  std::string id() const { return id_; }

private:
  const bool delete_when_terminated_;
  web::json::value res_;
  std::string id_;
};


class Message
{
public:
  Message(const std::string& thread_id, const std::string& text)
  {
    auto req = messages::create::Builder()
      .thread_id(thread_id)
      .body(messages::create::body::MessageBuilder()
          .role("user")
          .content(messages::create::body::TextContentBuilder()
            .text(text)
            .build())
          .build())
      .build();
    auto res = client::Client::GetInstance().Request<client::Client::OptionalJson>(req);
    if (res == std::nullopt)
    {
      throw std::runtime_error("failed to get response for creation the message");
    }
    id_ = res.value()["id"].as_string();
  }

  ~Message() = default;
  std::string id() const { return id_; }


private:
  std::string id_;
};


class Run
{
public:
  Run(const std::string& thread_id, const std::string& assistant_id)
  {
    auto req = runs::create::Builder()
      .thread_id(thread_id)
      .body(runs::create::body::Builder()
          .assistant_id(assistant_id)
          .build())
      .build();
    auto res = client::Client::GetInstance().Request<client::Client::OptionalJson>(req);
    if (res == std::nullopt)
    {
      throw std::runtime_error("failed to get response for creation the run");
    }
    id_ = res.value()["id"].as_string();
    thread_id_ = thread_id;
  }

  void Wait()
  {
    bool wait = true;
    do
    {
      auto req = runs::retrieve::Builder()
        .thread_id(thread_id_)
        .run_id(id_)
        .build();
      auto res = client::Client::GetInstance().Request<client::Client::OptionalJson>(req);
      if(res.value()["status"].as_string() == "completed") wait = false;
    }
    while (wait);
  }

  std::string id() const { return id_; }

private:
  std::string id_;
  std::string thread_id_;
};


int main(int argc, char** argv)
{
  auto assistants = assistants::Assistants(
      false,
      {{"name", "Math Tutor"}});
  auto thread = Thread();
  auto msg = Message(thread.id(), "Hello");
  auto msgs_before = thread.GetMessages();
  std::cout << "messages before asking to AI" << std::endl;
  for (const auto& pair : msgs_before)
  {
    std::cout << "from: " << pair.first << " -> " << pair.second << std::endl;
  }
  auto run = Run(thread.id(), assistants.GetObject()->GetId());
  run.Wait();
  auto msgs_after = thread.GetMessages();
  std::cout << "messages after asking to AI" << std::endl;
  for (const auto& pair : msgs_after)
  {
    std::cout << "from: " << pair.first << " -> " << pair.second << std::endl;
  }

  return EXIT_SUCCESS;
}
