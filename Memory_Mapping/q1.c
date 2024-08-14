#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

void replaceWordInFile(const char *fileName, const char *wordToReplace, const char *replacementWord) {

    size_t ReplaceLen = strlen(wordToReplace);
    size_t ToWordLen = strlen(replacementWord); 
    
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
    // Mapping file into memory
    char *fileData = mmap(NULL, fileSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (fileData == MAP_FAILED) {
        perror("Error mapping file into memory");
        close(fd);
        return;
    }
    char* found = fileData;
    // replacing word
    while ((found = strstr(found, wordToReplace)) != NULL) {
        memmove(found + ToWordLen, found +ReplaceLen, strlen(found + ReplaceLen) + 1);
        memcpy(found, replacementWord, ToWordLen);
        found =found+ ToWordLen;
    }

    // Unmap the memory and close the file
    munmap(fileData, fileSize);
    close(fd);
}

int main(int argc, char *argv[]) {
    const char *fileName = argv[1];

    replaceWordInFile(fileName,"hello", "goodbye");

    printf("Word replaced successfully in %s\n",argv[1]);

    return 0;
}

