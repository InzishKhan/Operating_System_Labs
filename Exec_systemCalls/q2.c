#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;
    pid = fork();
    if (pid == 0) { //child process created
        execlp("mkdir", "mkdir", "demo_folder", NULL); // demo folder creation through execlp
        exit(1);
    } 
    else if (pid>0){ //parent process 
        wait(NULL);
    }
    else{
       exit(1);
    }

    pid = fork();
    if (pid == 0) { //child process created
        execlp("touch", "touch", "demo_folder/file1.txt", "demo_folder/file2.txt", NULL);//files created
        exit(1);
    } 
    else if (pid>0){ //parent process 
        wait(NULL);
    }
    else{
       exit(1);
    }
    
    pid = fork();
    if (pid == 0) { //child process created
        execlp("ls", "ls", "demo_folder", NULL); //ls command execution
        exit(1);
    } 
    else if (pid>0){ //parent process 
        wait(NULL);
    }
    else{
       exit(1);
    }

    pid = fork();
    if (pid == 0) {//child process created
        execlp("rm", "rm", "-rf", "demo_folder", NULL);//removing demo_folder
        exit(1);
    } 
    else if (pid>0){ //parent process 
        wait(NULL);
    }
    else{
       exit(1);
    }
    return 0;
}


