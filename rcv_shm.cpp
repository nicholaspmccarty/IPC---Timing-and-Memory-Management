#include <iostream>
#include <array>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>

// Shared memory key
#define SHM_KEY 12345
#define MEM_SIZE 1024

// Read data from shared memory
int main(int argc, char* argv[]) {
    const int shm_key = shmget(SHM_KEY, MEM_SIZE, S_IRUSR);
    int* sharedMem =
        reinterpret_cast<int*>(shmat(shm_key,
            NULL, SHM_RDONLY));
    for (int i = 0; (i < 25); i++) {
        std::cout << *sharedMem
            << std::endl;
        sleep(1);
    }
    shmdt(sharedMem);
    return 0;
}