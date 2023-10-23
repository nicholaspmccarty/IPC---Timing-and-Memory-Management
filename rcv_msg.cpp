#include "Msg.h"
#include <iostream>
#include <array>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <fstream>
#include <chrono>

int main() {
    
    std::chrono::system_clock::time_point startTime = std::chrono::system_clock::now(); 
    const int msqid =
        msgget(123456, S_IRUSR);
    // Check to ensure msqid is not ­‐1!
    MessageType msg;
    while (msgrcv(msqid, &msg, MSG_SIZE, MSG_TYPE, 0) != -1) {
        std::cout << msg.data
            << std::endl;

    }
    
    std::chrono::system_clock::time_point endTime = std::chrono::system_clock::now(); // Record end time
    std::chrono::duration<double> elapsedTime = endTime - startTime;

    std::ofstream outputFile("data1.txt");
    outputFile << "Elapsed Time (seconds)\n";
    outputFile << elapsedTime.count() << "\n";
    outputFile.close();

    return 0;
}