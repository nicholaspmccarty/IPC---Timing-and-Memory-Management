#include "Msg.h"
#include <iostream>
#include <array>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    const int msqid =
        msgget(123456, S_IRUSR |
            S_IWUSR | S_IROTH |
            IPC_CREAT);
    // Check to ensure msqid is not ­‐1!
    MessageType msg;
    for (int i = 0; (i < 25); i++) {
        msg.my_msg_type = MSG_TYPE;
        sprintf(msg.data, "Testing-­%d", i);
        msgsnd(msqid, &msg,
            MSG_SIZE, 0);
        sleep(1);
    }
    msgctl(msqid, IPC_RMID, NULL);
    return 0;
}