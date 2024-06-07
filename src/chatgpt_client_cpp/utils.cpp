#include "chatgpt_client_cpp/utils.hpp"

#include <sstream>
#include <cstdlib>


namespace chatgpt_client_cpp::utils
{

std::string GetKey() noexcept(false)
{
  const std::string key = std::getenv("OPENAI_API_KEY");
  if (key.empty())
  {
    throw std::runtime_error("OPENAI_API_KEY is empty");
  }
  std::stringstream ss;
  ss << "Bearer " << key;

  return ss.str();
}

}  // namespace chatgpt_client_cpp::utils
