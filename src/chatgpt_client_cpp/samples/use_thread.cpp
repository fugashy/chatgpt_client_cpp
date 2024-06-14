#include "chatgpt_client_cpp/chatgpt_client_cpp.hpp"

using namespace chatgpt_client_cpp;
using namespace chatgpt_client_cpp::v1;


int main(int argc, char** argv)
{
  auto assistants = assistants::Assistants(
      false,
      {{"name", "Math Tutor"}});

  auto threads = threads::Threads(
      false);

  auto msg = messages::Messages(
      {
        {"thread_id", threads.GetObject()->GetId()},
        {"text", "Hello"}
      });

  auto msgs_before = threads.GetMessages();
  std::cout << "messages before asking to AI" << std::endl;
  for (const auto& pair : msgs_before)
  {
    std::cout << "from: " << pair.first << " -> " << pair.second << std::endl;
  }

  auto runs = runs::Runs(
      {
        {"thread_id", threads.GetObject()->GetId()},
        {"assistant_id", assistants.GetObject()->GetId()}
      });
  runs.Wait();

  auto msgs_after = threads.GetMessages();
  std::cout << "messages after asking to AI" << std::endl;
  for (const auto& pair : msgs_after)
  {
    std::cout << "from: " << pair.first << " -> " << pair.second << std::endl;
  }

  return EXIT_SUCCESS;
}
