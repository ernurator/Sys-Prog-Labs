#!/bin/bash

# update
sudo apt-get update

# install cmake
sudo apt install -y cmake

# install grpc
sudo apt install -y libgrpc++-dev

# install protobuf
sudo apt install -y protobuf-compiler
sudo apt install -y libprotobuf-dev
sudo apt-get install -y protobuf-compiler-grpc

# install package config
sudo apt install -y pkg-config
