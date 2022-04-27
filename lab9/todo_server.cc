#include "todo_server.hh"
#include <grpcpp/grpcpp.h>
#include <iostream>
#include <memory>
#include <string>

::grpc::Status TodoServerImpl::AddTodo(::grpc::ServerContext* context,
                                       const ::protos::TodoItem* request,
                                       ::protos::TodoResponse* response) {
  // TODO:
  // 1) if an item already exists with the request's title or the request's
  //    status is protos::TodoStatus::COMPLETED, then set the response's
  //    success = false
  // 2) otherwise add the item this server's map of Todos and set the
  //    response's success = true

  return ::grpc::Status::OK;
}

::grpc::Status TodoServerImpl::EditTodo(::grpc::ServerContext* context,
                                        const ::protos::TodoItem* request,
                                        ::protos::TodoResponse* response) {
  // TODO: the reverse of AddTodo
  // 1) if an item already exists with the request's title, then update
  //    the item's status in the map of Todos and set the response's
  //    success = true.
  //    If the status is updated to COMPLETED, then delete the item from
  //    the server's map of Todos.
  // 2) if the item doesn't exist, then set success = false

  return ::grpc::Status::OK;
}

::grpc::Status TodoServerImpl::GetTodos(::grpc::ServerContext* context,
                                        const ::protos::Empty* request,
                                        ::protos::TodoList* response) {
  // copies internal map of todos
  // into a TodoList message
  for (auto const& item : todos) {
    auto add_item = response->add_items();
    add_item->set_title(item.first);
    add_item->set_status(item.second);
  }
  return ::grpc::Status::OK;
}

int main() {
  std::string server_address("0.0.0.0:8080");
  TodoServerImpl service;

  grpc::ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
  return 0;
}
