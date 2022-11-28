#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h> // Core BSD socket functions and data structures.
#include <netinet/in.h> // AF_INET and AF_INET6 address families and their corresponding protocol families PF_INET and PF_INET6.
#include <arpa/inet.h>  // Functions for manipulating numeric IP addresses.

int main() {

    int server_sockfd;
    int client_sockfd;
    int len;
    struct sockaddr_in my_addr{};
    struct sockaddr_in remote_addr{};
    int sin_size;
    char buf[BUFSIZ];

    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET; //IP通信
    my_addr.sin_addr.s_addr = INADDR_ANY; //服务器IP地址
    my_addr.sin_port = htons(8000);

    //创建服务器端套接字，ipv4, tcp
    if ((server_sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket error");
        return 1;
    }

    // 将套接字绑定到服务器的网络地址上
    if (bind(server_sockfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr)) < 0) {
        perror("bind error");
        return 1;
    }

    // 监听连接请求，监听队列长度为5
    if (listen(server_sockfd, 5) < 0) {
        perror("listen error");
        return 1;
    }

    sin_size = sizeof(struct sockaddr_in);

    // 等待客户端连接
    if ((client_sockfd = accept(server_sockfd, (struct sockaddr *) &remote_addr, (socklen_t *)&sin_size)) < 0) {
        perror("accept error");
        return 1;
    }

    printf("accept client %s\n", inet_ntoa(remote_addr.sin_addr));
    send(client_sockfd, "Welcome to my server\n", 21, 0);

    while((len = (int)recv(client_sockfd, buf, BUFSIZ, 0))>0) {
        buf[len] = '\0';
        printf("%s\n", buf);
        if (send(client_sockfd, buf, len, 0)<0){
            perror("write error");
            return 1;
        }
    }

    close(client_sockfd);
    close(server_sockfd);

    return 0;
}
