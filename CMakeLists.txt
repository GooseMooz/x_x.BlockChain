cmake_minimum_required(VERSION 3.29)
project(BlockChain)

set(CMAKE_CXX_STANDARD 14)

set(OPENSSL_ROOT_DIR "C:/Program Files/FireDaemon OpenSSL 3")
set(OPENSSL_INCLUDE_DIR "C:/Program Files/FireDaemon OpenSSL 3/include")
set(OPENSSL_LIBRARIES "C:/Program Files/FireDaemon OpenSSL 3/lib")

find_package(OpenSSL REQUIRED)

include_directories(${OPENSSL_INCLUDE_DIR})

add_executable(BlockChain main.cpp)

target_link_libraries(BlockChain OpenSSL::SSL OpenSSL::Crypto)