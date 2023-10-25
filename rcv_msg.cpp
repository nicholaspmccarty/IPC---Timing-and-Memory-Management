#include "Msg.h"
#include <iostream>
#include <array>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <fstream>
#include <chrono>
#include <cstdlib>

void receive_message(int numBytes, int numMessages) {
    const int msqid = msgget(123456, S_IRUSR);
    // Check to ensure msqid is not -1!
    MessageType msg;

    std::chrono::system_clock::time_point startTime = std::chrono::system_clock::now();
    
    for (int i = 0; i < numMessages; i++) {
        if (msgrcv(msqid, &msg, static_cast<size_t>(numBytes), MSG_TYPE, 0) != -1) {
            // Extract the timestamp from the received message
            long long timestamp;
            sscanf(msg.data, "%lld-", &timestamp);
            std::cout << "Received message with timestamp: " << timestamp << ", Data: " << msg.data + 18 << std::endl;
        }
    }

    std::chrono::system_clock::time_point endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedTime = endTime - startTime;

    // Store the timing data in a temporary variable
    double executionTime = elapsedTime.count();

    // Write the execution time to a CSV file
    std::ofstream outputFile("data2.csv");
    outputFile<< numBytes << "," << numMessages << "," << executionTime << "\n";
    outputFile.close();
}

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <numBytes> <numMessages>" << std::endl;
        return 1;
    }

    int numBytes = atoi(argv[1]);
    int numMessages = atoi(argv[2]);

    receive_message(numBytes, numMessages); // Receive numBytes bytes numMessages times
    return 0;
}