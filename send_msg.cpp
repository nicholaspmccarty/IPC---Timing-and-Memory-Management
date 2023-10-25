#include "Msg.h"
#include <iostream>
#include <array>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <fstream>
#include <chrono>
#include <cstdlib>


// helper function called in main method. this function takes params
void send_message(int numBytes, int numMessages) {
    const int msqid = msgget(123456, S_IRUSR | S_IWUSR | S_IROTH | IPC_CREAT);
    MessageType msg;

    std::chrono::system_clock::time_point startTime = std::chrono::system_clock::now();
    
    for (int i = 0; i < numMessages; i++) {
        msg.my_msg_type = MSG_TYPE;

        // Create a message with a timestamp at the start
        auto currentTime = std::chrono::system_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::microseconds>(currentTime.time_since_epoch()).count();
        snprintf(msg.data, MSG_SIZE, "%lld-Testing-%d", static_cast<long long>(timestamp), i);
        msgsnd(msqid, &msg, static_cast<size_t>(numBytes), 0);
    }

    msgctl(msqid, IPC_RMID, NULL);

    std::chrono::system_clock::time_point endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedTime = endTime - startTime;

    // Store the timing data in a temporary variable
    double executionTime = elapsedTime.count();

    // Write the execution time to a CSV file
    std::ofstream out("data1.csv");
    out << numBytes << "," << numMessages << "," << executionTime << "\n";
    out.close();
}


// allows command line to take arguments
int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <numBytes> <numMessages>" << std::endl;
        return 1;
    }

    int numBytes = atoi(argv[1]);
    int numMessages = atoi(argv[2]);

    send_message(numBytes, numMessages); // Send numBytes bytes numMessages times
    return 0;
}