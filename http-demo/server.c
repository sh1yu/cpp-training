#include <stdlib.h>
#include <unistd.h>    //getopt, fork
#include <signal.h>

#include "handler.h"


//显示help
void show_help();

//退出信号处理
void signal_handler(int sig);

struct event_base *base;

int main(int argc, char *argv[]) {
    signal(SIGHUP, signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);

    char *httpd_option_listen = "0.0.0.0";
    int httpd_option_port = 8080;
    int httpd_option_daemon = 0;
    int httpd_option_timeout = 120; //in seconds

    int c;
    while ((c = getopt(argc, argv, "l:p:dt:h")) != -1) {
        switch (c) {
            case 'l':
                httpd_option_listen = optarg;
                break;
            case 'p':
                httpd_option_port = atoi(optarg);
                break;
            case 'd':
                httpd_option_daemon = 1;
                break;
            case 't':
                httpd_option_timeout = atoi(optarg);
                break;
            case 'h':
            default:
                show_help();
                exit(EXIT_SUCCESS);
        }
    }

    if (httpd_option_daemon) {
        pid_t pid;
        pid = fork();
        if (pid < 0) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }
        if (pid > 0) {
            //退出父进程
            exit(EXIT_SUCCESS);
        }
    }

    //event base初始化
    base = event_base_new();
    //evhttp初始化，并绑定端口
    struct evhttp *httpd = evhttp_new(base);
    evhttp_bind_socket(httpd, httpd_option_listen, httpd_option_port);

    //设置http服务的超时和handler
    evhttp_set_timeout(httpd, httpd_option_timeout);
    evhttp_set_gencb(httpd, http_handler, NULL);
    // evhttp_set_cb(httpd, "/", sepecific_handler, NULL);

    //开始事件分发
    event_base_dispatch(base);

    return 0;
}

void show_help() {
    char *help = "writen by Min\n\n"
                 "-l <ip_addr> interface to listen on, default is 0.0.0.0\n"
                 "-p <num>     port number to listen on, default is 8080\n"
                 "-d           run as a daemon\n"
                 "-t <second>  timeout for a http request, default is 120 seconds\n"
                 "-h           print this help and exit\n"
                 "\n";
    fprintf(stderr, "%s", help);
}

//结束信号处理，退出event base
void signal_handler(int sig) {
    switch (sig) {
        case SIGTERM:
        case SIGHUP:
        case SIGQUIT:
        case SIGINT:
            event_base_loopbreak(base);
            break;
    }
}