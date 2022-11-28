cmake_minimum_required(VERSION 3.21)
project(cpp-training)

set(CMAKE_CXX_STANDARD 11)

###########################################
include_directories(/usr/local/include/)
link_directories(/usr/local/lib)


###########################################
# 基础
add_executable(hello-world basic/hello_world.cpp)

# 网络相关
add_executable(tcp-server net-demo/tcp-server.cpp)
add_executable(tcp-client net-demo/tcp-client.cpp)
add_executable(udp-server net-demo/udp-server.cpp)
add_executable(udp-client net-demo/udp-client.cpp)

# http服务（libevent）
add_executable(http_server http-demo/server.c http-demo/handler.c)
target_link_libraries(http_server event)

# 异步相关
add_executable(sync-timer asio/sync-timer.cpp)
add_executable(async-timer asio/async-timer.cpp)
add_executable(sync-tcp-client asio/sync-tcp-client.cpp)

# ctf安全相关
add_executable(ctf-read_message ctf-test/read_message.cpp)