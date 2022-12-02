cmake_minimum_required(VERSION 3.21)
project(cpp-training)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

###########################################
include_directories(/usr/local/include/)
#link_directories指令的作用主要是指定要链接的库文件的路径，该指令有时候不一定需要。因为find_package和find_library指令可以得到库文件的绝对路径。
link_directories(/usr/local/lib)
#unix_c的头文件
include_directories(unix_c/include)


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

# 模版相关
add_executable(hello-template template-demo/hello-template.cpp)

# unix_c
#FILE(GLOB_RECURSE LIB_FILES src/lib/*.c)
aux_source_directory(unix_c/lib/ UNIX_C_LIB)
#add_executable(unix_c_ls unix_c/ls.c ${UNIX_C_LIB}) // 会出现implicit declaration of function 'CMSG_LEN' is invalid in C99的错误
add_executable(unix_c_ls unix_c/ls.c unix_c/lib/error.c)