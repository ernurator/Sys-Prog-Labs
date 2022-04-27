cmake_minimum_required(VERSION 3.10)
project(grpc_lab)

set(CMAKE_CXX_STANDARD 14)

# Find Protobuf installation
# Looks for protobuf-config.cmake file installed by Protobuf's cmake installation.
include(FindProtobuf)
find_package(Protobuf REQUIRED)
message(STATUS "Using protobuf ${protobuf_VERSION}")

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)

set(_GRPC_PLUGIN /usr/bin/grpc_cpp_plugin)
set(_GRPC_GRPCPP_UNSECURE -pthread -lgrpc++)

# Proto files
get_filename_component(todo_proto "todo.proto" ABSOLUTE)
get_filename_component(todo_proto_path "${todo_proto}" PATH)

# Generated sources
set(todo_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/todo.pb.cc")
set(todo_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/todo.pb.h")
set(todo_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/todo.grpc.pb.cc")
set(todo_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/todo.grpc.pb.h")

add_custom_command(
        OUTPUT "${todo_proto_srcs}" "${todo_proto_hdrs}" "${todo_grpc_srcs}" "${todo_grpc_hdrs}"
        COMMAND ${_PROTOBUF_PROTOC}
        ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${todo_proto_path}"
        --plugin="protoc-gen-grpc=${_GRPC_PLUGIN}"
        "${todo_proto}"
        DEPENDS "${todo_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_executable(todo_client ${todo_proto_srcs} ${todo_grpc_srcs} todo_client.cc)
target_link_libraries(todo_client ${_PROTOBUF_LIBPROTOBUF} ${_GRPC_GRPCPP_UNSECURE})

add_executable(todo_server ${todo_proto_srcs} ${todo_grpc_srcs} todo_server.cc)
target_link_libraries(todo_server ${_PROTOBUF_LIBPROTOBUF} ${_GRPC_GRPCPP_UNSECURE})
