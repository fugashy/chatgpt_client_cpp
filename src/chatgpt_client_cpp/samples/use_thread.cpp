#include "chatgpt_client_cpp/chatgpt_client_cpp.hpp"

using namespace chatgpt_client_cpp;
using namespace chatgpt_client_cpp::v1;


class Assistant
{
public:
  Assistant(
      const std::string& name,
      const bool delete_when_terminated = false) noexcept(false)
    : delete_when_terminated_(delete_when_terminated)
  {
    // 目的の名前のアシスタントを得て実体化する
    // ない場合は作る
    // 実際のところ，同名のアシスタントは作成できる（IDで区別している）
    // しかし，わかりにくいので名前で区別するようにすることにする
    auto req = assistants::list::Builder().build();
    auto res = client::Client::GetInstance().Request<client::Client::OptionalJson>(req);
    if (res == std::nullopt)
    {
      throw std::runtime_error("failed to get response for list the assistant)");
    }
    for (auto e : res.value()["data"].as_array())
    {
      if (e["name"].as_string() == name)
      {
        id_ = e["id"].as_string();
        res_ = e;
      }
    }

    if (!id_.empty()) return;

    Create(name, "gpt-4o", "A Math Tutor", "You are a math tutor");
  }

  ~Assistant()
  {
    if (!delete_when_terminated_)
    {
      std::cout << "skip deletion of the assistant(" << id_.c_str() << ")" << std::endl;
      return;
    }

    auto req = assistants::delete_::Builder()
      .assistant_id(id_)
      .build();
    auto res = client::Client::GetInstance().Request<client::Client::OptionalJson>(req);
    if (res == std::nullopt)
    {
      std::cerr << "failed to get response for deletion the assistant(" << id_.c_str() << ")" << std::endl;
    }
    if (!res.value()["deleted"].as_bool())
    {
      std::cerr << "failed to delete for assistant(" << id_.c_str() << ")" << std::endl;
    }
    std::cout << "delete the assistant(" << id_.c_str() << ")" << std::endl;
  }

  std::string id() const { return id_; }

private:
  void Create(
      const std::string& name,
      const std::string& model,
      const std::string& description,
      const std::string& instructions)
  {
    auto req = assistants::create::Builder()
      .body(assistants::create::body::Builder()
          .model(model)
          .name(name)
          .description(description)
          .instructions(instructions)
          .build())
      .build();
    auto res = client::Client::GetInstance().Request<client::Client::OptionalJson>(req);
    if (res == std::nullopt)
    {
      throw std::runtime_error("failed to request for creation assistants");
    }

    res_ = res.value();
    id_ = res.value()["id"].as_string();
    std::cout << "create a assistant(" << id_.c_str() << ")" << std::endl;
  }

  const bool delete_when_terminated_;
  web::json::value res_;
  std::string id_;
};


// スレッド
class Thread
{
public:
  Thread() noexcept(false)
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
  auto assistant = Assistant("Math Tutor");
  auto thread = Thread();
  auto msg = Message(thread.id(), "Hello");
  auto msgs_before = thread.GetMessages();
  for (const auto& pair : msgs_before)
  {
    std::cout << "from: " << pair.first << " -> " << pair.second << std::endl;
  }
  auto run = Run(thread.id(), assistant.id());
  run.Wait();
  auto msgs_after = thread.GetMessages();
  for (const auto& pair : msgs_after)
  {
    std::cout << "from: " << pair.first << " -> " << pair.second << std::endl;
  }

  return EXIT_SUCCESS;
}
