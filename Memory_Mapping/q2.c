#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define FileLen 100

void* replaceIntegersInMap(void* arg) {
    char* mapPointer = (char*)arg;

    for (size_t i = 0; i < 50; ++i) {
        if (mapPointer[i]>='0' && mapPointer[i]<='9') {
            mapPointer[i] = ' ';
        }
    }

    pthread_exit(NULL);
}

void replaceIntegersInFile(const char* fileName) {
    // Open the file
    int fd = open(fileName, O_RDWR);
    if (fd == -1) {
        perror("Error opening file");
        return;
    }

    // Getting the file size
    key_t key = ftok(fileName, 0);
    if (key == -1) {
         perror("ftok");
         exit(EXIT_FAILURE);
     }
    off_t fileSize=key;

    // Map the file into memory
    char* fileData = mmap(NULL, fileSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (fileData == MAP_FAILED) {
        perror("Error mapping file into memory");
        close(fd);
        return;
    }

    // Create two threads for replacing integers in the file
    pthread_t t1, t2;
    pthread_create(&t1, NULL, replaceIntegersInMap, fileData);
    pthread_create(&t2, NULL, replaceIntegersInMap, fileData + 50);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    // Unmap the memory and close the file
    munmap(fileData, fileSize);
    close(fd);
}

int main(int argc, char* argv[]) {
    //reading filename from the terminal 
    const char* fileName = argv[1];

    replaceIntegersInFile(fileName);

    printf("Integers replaced successfully in %s\n",argv[1]);

    return 0;
}
