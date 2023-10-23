#include "Msg.h"
#include <iostream>
#include <array>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>

int main() {
    const int msqid =
        msgget(123456, S_IRUSR);
    // Check to ensure msqid is not ­‐1!
    MessageType msg;
    while (msgrcv(msqid, &msg, MSG_SIZE, MSG_TYPE, 0) != -1) {
        std::cout << msg.data
            << std::endl;
    }
    return 0;
}