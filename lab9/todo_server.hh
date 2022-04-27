#ifndef GRPC_LAB_TODO_SERVER_HH
#define GRPC_LAB_TODO_SERVER_HH

#include <map>
#include "todo.grpc.pb.h"

using grpc::ServerContext;
using grpc::Status;
using protos::Empty;
using protos::TodoItem;
using protos::TodoList;
using protos::TodoManager;
using protos::TodoResponse;
using protos::TodoStatus;

class TodoServerImpl final : public TodoManager::Service {
 private:
  std::map<std::string, TodoStatus> todos;

 public:
  Status AddTodo(ServerContext* context, const TodoItem* request,
                 TodoResponse* response);

  Status EditTodo(ServerContext* context, const TodoItem* request,
                  TodoResponse* response);

  Status GetTodos(ServerContext* context, const Empty* request,
                  TodoList* response);
};

#endif  // GRPC_LAB_TODO_SERVER_HH
