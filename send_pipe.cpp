#include <iostream>
#include <cstring>
#include <ext/stdio_filebuf.h>
#include <unistd.h>
#include <sys/wait.h>
#include <chrono>

#define READ 0
#define WRITE 1

void child(int pipefd[]);
void parent(int pipefd[]);

int main() {
    int pipefd[2];
    pipe(pipefd); // check return to ensure success
    std::chrono::system_clock::time_point startTime = std::chrono::system_clock::now();
    pid_t pid = fork();
    if (pid == 0) {
        child(pipefd);
    } else {
        parent(pipefd);
        int exitCode = 0;
        waitpid(pid,
            &exitCode, 0);
    }
    std::chrono::system_clock::time_point endTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedTime = endTime - startTime;
    double executionTime = elapsedTime.count();
    std::ofstream out("pipe.csv");
    out<< "5" << "," << "5" << "," << executionTime << "\n";
    out.close();
    return 0;
}

void parent(int pipefd[]) {
    close(pipefd[READ]);
    std::filebuf* fb = new __gnu_cxx::stdio_filebuf<char>(pipefd[WRITE], std::ios::out, 1);
    std::ostream* os = new std::ostream(fb);
    for (int i = 0; (i < 10); i++) {
        (*os) << "Testing #"
            << i << std::endl;
    }
    delete os;
    close(pipefd[WRITE]);
}

void child(int pipefd[]) {
    close(pipefd[WRITE]);
    std::filebuf* fb = new __gnu_cxx::stdio_filebuf<char>(pipefd[READ], std::ios::in, 1);
    std::istream* is = new std::istream(fb);
    std::string line;
    while (!is->eof() && is->good()) {
        getline(*is, line);
        std::cout << "* "
            << line << std::endl;
    }
    delete is;
    close(pipefd[READ]);
}