#include <iostream>
#include <array>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>

// Shared memory key
#define SHM_KEY 12345
#define MEM_SIZE 1024
// Write data into shared memory
int main(int, char**) {
    const int shm_key = shmget(SHM_KEY,
        MEM_SIZE, S_IRUSR | S_IWUSR | IPC_CREAT);
    int* sharedMem = reinterpret_cast<int*>(shmat(shm_key, NULL, 0));
    for (int i = 0; (i < 25); i++) {
        *sharedMem = i;
        sleep(1);
    }
    shmdt(sharedMem);
    shmctl(shm_key, IPC_RMID, NULL);
    return 0;
}