#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define SHM_KEY 1234
#define SHM_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    int shmid;
    char *shared_memory;
    char buff[100];

    // Get the shared memory segment
    shmid = shmget(SHM_KEY, SHM_SIZE,IPC_CREAT| 0666);
    if (shmid < 0) {
        perror("shmget");
        return 1;
    }

    // Attach shared memory segment
    shared_memory = (char *)shmat(shmid, NULL, 0);
    if (shared_memory == (char *)(-1)) {
        perror("shmat");
        return 1;
    }

    // Opening  the file
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        printf("Error Opening the file!");
        close(fd);
        return 1;
    }
    
    ssize_t bytes= read(fd, buff,sizeof(buff));
    if (bytes == -1) {
        printf("Error reading from file!");
        close(fd);
        return 1;
    }

    strncpy(shared_memory, buff,sizeof(buff));

    // Detach shared memory segment
    if (shmdt(shared_memory) == -1) {
        perror("shmdt");
        return 1;
    }

    // Close the file
    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}
