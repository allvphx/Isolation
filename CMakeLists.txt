cmake_minimum_required(VERSION 3.19)
project(Encodings)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(Encodings main.cpp res_lock/lock.h isolation_levels/read_uncommited.h transaction/txn.h isolation_levels/read_commited.h isolation_levels/storage.h transaction/transaction.h isolation_levels/2pl_serializable.h transaction/RC_test.cpp transaction/2PL_test.cpp isolation_levels/mvcc_mvto.h res_lock/timestamp.h res_lock/cas.h transaction/mvcc_test.cpp)