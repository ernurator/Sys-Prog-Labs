#ifndef GRPC_LAB_TODO_CLIENT_HH
#define GRPC_LAB_TODO_CLIENT_HH
#include <grpcpp/grpcpp.h>
#include <memory>
#include "todo.grpc.pb.h"

using grpc::Channel;
using protos::TodoManager;
using protos::TodoStatus;

class TodoClient {
 private:
  std::unique_ptr<TodoManager::Stub> stub;

 public:
  TodoClient(std::shared_ptr<Channel> channel)
      : stub(TodoManager::NewStub(channel)) {}

  bool AddTodo(const std::string& title, TodoStatus status);

  bool EditTodo(const std::string& title, TodoStatus new_status);

  void PrintTodos();
};
#endif  // GRPC_LAB_TODO_CLIENT_HH
