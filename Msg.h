#include <iostream>
#include <cstdio>
#include <cstring>
#include <sys/msg.h>
#include <sys/stat.h>

#define MSG_SIZE 124
#define MSG_TYPE 42
struct MessageType {
    long int my_msg_type;
    char data[MSG_SIZE];
};