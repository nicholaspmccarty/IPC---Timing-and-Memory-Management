# IPC---Timing-and-Memory-Management

## Prerequisites
- C++ compiler (e.g., g++)
- A Unix-like operating system (Linux or macOS)

## Description
This program is designed to benchmark and compare different Inter-Process Communication (IPC) mechanisms, specifically pipes, shared memory, and message passing. It measures the time it takes to send data from a sender process to a receiver process using these IPC methods and records the results in a CSV file.

The program is part of a lab assignment that focuses on the following tasks:
- Modify each IPC method to write timing data to a CSV file at the end of the program execution.
- Implement the ability to specify the size of the data in terms of the number of bytes and the number of messages to send.
- Encode a timestamp at the start of each message to accurately measure the time taken for the data to reach the receiver.


