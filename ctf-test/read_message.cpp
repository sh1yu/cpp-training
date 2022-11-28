//
// Created by psy on 2022/3/6.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char program[] = "/usr/local/sbin/message";
    char buf[20];
    char authorized[] = "Simon";

    printf("What is your name?\n");
    gets(buf); //可能会引起缓冲区溢出，输入的name为Simon123456789111315171921232527/bin/bash就会覆盖program第一个参数为/bin/bash，从而获得bash

    if (!strncmp(authorized, buf, 5)) {
        printf("Hello %s! Here is your message: \n\n", buf);
        printf("program %s\n", program);
        execve(program, NULL, NULL);
    } else {
        printf("Sorry %s, you're no privilege!", buf);
        exit(EXIT_FAILURE);
    }

    return 0;
}