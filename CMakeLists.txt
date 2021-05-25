cmake_minimum_required(VERSION 3.19)
project(Encodings)

set(CMAKE_CXX_STANDARD 14)

add_executable(Encodings main.cpp lock.h rw.h read_uncommited.h txn.h)