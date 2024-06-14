#ifndef CHATGPT_CLIENT_CPP_HELPER_BASE_HPP_
#define CHATGPT_CLIENT_CPP_HELPER_BASE_HPP_
#include <memory>
#include <string>

#include <cpprest/json.h>


namespace chatgpt_client_cpp::v1
{

class ObjectHelper
{
public:
  using SharedPtr = std::shared_ptr<ObjectHelper>;

  ObjectHelper(const web::json::value& response)
    : object_(response)
  {}
  ~ObjectHelper() = default;

  std::string GetId() const { return this->object_.at("id").as_string(); }
  std::string GetThreadId() const { return this->object_.at("thread_id").as_string(); }

private:
  const web::json::value object_;
};

class ApiHelper
{
public:
  using Pargs = std::map<std::string, std::string>;

  explicit ApiHelper(
      const bool enable_destructor,
      const Pargs& pargs)
    : enable_destructor_(enable_destructor) {}

  void Initialize(const Pargs& pargs)
  {
    this->object_ = InitializeObject(pargs);
  }

  virtual ~ApiHelper()
  {
    Destruct();
  }

  void Destruct()
  {
    if (!enable_destructor_) return;
    DestructObject();
  }

  ObjectHelper::SharedPtr GetObject() const { return object_; }

protected:
  virtual ObjectHelper::SharedPtr InitializeObject(const Pargs& pargs) noexcept(false) = 0;

  virtual void DestructObject() = 0;

  ObjectHelper::SharedPtr object_;

private:
  const bool enable_destructor_;
};

class MessageInterface
{
public:
  using MessageByRole = std::map<std::string, std::string>;
  virtual MessageByRole GetMessages() = 0;
};

class WaitInterface
{
public:
  virtual bool Wait() = 0;
};


}  // namespace chatgpt_client_cpp::v1
#endif  // CHATGPT_CLIENT_CPP_HELPER_BASE_HPP_
