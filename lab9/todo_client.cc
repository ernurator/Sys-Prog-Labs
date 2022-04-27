#include "todo_client.hh"
#include <grpcpp/grpcpp.h>
#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include "todo.grpc.pb.h"

using grpc::ClientContext;
using grpc::Status;
using protos::Empty;
using protos::TodoItem;
using protos::TodoList;
using protos::TodoResponse;
using protos::TodoStatus;

bool TodoClient::AddTodo(const std::string& title, TodoStatus status) {
  // create a TodoItem from the title and status
  TodoItem request;
  request.set_title(title);
  request.set_status(status);

  // create a container for the server response
  TodoResponse response;
  ClientContext ctx;
  Status resp_code = this->stub->AddTodo(&ctx, request, &response);

  // act upon the status
  if (resp_code.ok()) {
    // if the response had no networking errors
    // return the underlying true/false success value
    return response.success();
  }

  printf("%d: %s\n", resp_code.error_code(), resp_code.error_message().c_str());
  return false;
}

bool TodoClient::EditTodo(const std::string& title, TodoStatus new_status) {
  // create a TodoItem from the title and status
  TodoItem request;
  request.set_title(title);
  request.set_status(new_status);

  // create a container for the server response
  TodoResponse response;
  ClientContext ctx;
  Status resp_code = this->stub->EditTodo(&ctx, request, &response);

  // act upon the status
  if (resp_code.ok()) {
    // if the response had no networking errors
    // return the underlying true/false success value
    return response.success();
  }

  printf("%d: %s\n", resp_code.error_code(), resp_code.error_message().c_str());
  return false;
}

void TodoClient::PrintTodos() {
  Empty request;
  TodoList response;
  ClientContext ctx;
  Status resp_code = this->stub->GetTodos(&ctx, request, &response);

  if (resp_code.ok()) {
    int num_items = response.items_size();

    fprintf(stdout, "Printing Todo Items\n");
    // TODO:
    // Print out all items in the Todo list!
    //
    // You may want to consult the documentation for repeated fields in Protobufs:
    // https://developers.google.com/protocol-buffers/docs/reference/cpp-generated#repeatednumeric
    //
    // Each item printed should have the format
    // "Item <i>: <title> with status <status>",
    // where i is the index in the list,
    // title is the item's title, and
    // status is the item's status.
    //
    // (Hint: for converting the TodoStatus enum to a string, use
    //  protos::TodoStatus_Name)
  } else {
    fprintf(stderr, "Error printing todo list\n");
    fprintf(stderr, "%d: %s\n", resp_code.error_code(),
            resp_code.error_message().c_str());
  }
}

int main(int argc, char* argv[]) {
  TodoClient todolist(grpc::CreateChannel("localhost:8080",
                                          grpc::InsecureChannelCredentials()));

  if (argc != 2) {
    // runs a simple test: adds 2 items and then edits the first one
    todolist.AddTodo("first item", TodoStatus::NOT_STARTED);
    todolist.AddTodo("second item", TodoStatus::NOT_STARTED);
    todolist.EditTodo("first item", TodoStatus::IN_PROGRESS);
  } else {
    // open testing file
    std::ifstream file(argv[1]);
    std::string line;

    while (std::getline(file, line)) {
      std::istringstream ss(line);
      std::string cmd, title, status_str;
      ss >> cmd >> title >> status_str;

      TodoStatus status;
      if (!protos::TodoStatus_Parse(status_str, &status)) {
        fprintf(stderr, "Invalid input file -- bad status type\n");
        return -1;
      }

      if (cmd == "add") {
        todolist.AddTodo(title, status);
      } else if (cmd == "edit") {
        todolist.EditTodo(title, status);
      } else {
        fprintf(stderr, "Invalid input file -- bad status type\n");
        return -1;
      }
    }
  }

  todolist.PrintTodos();
  return 0;
}
