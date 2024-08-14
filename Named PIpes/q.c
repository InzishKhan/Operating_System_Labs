#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/type.h>
#include<fcntl.h>
int isPalindrome(int number) {
    int OgNum = number;
    int RsNum = 0;

    while (number != 0) {
        int remainder = number % 10;
        RsNum = RsNum * 10 + remainder;
        number /= 10;
    }
    if((OgNum == RsNum){
       return OgNum;
    }
}

int main(int argc,char *argv[]){
   int res=0;
   res=mkfifo("NamedPipe",0666); //making named pipe 
   pid_t pid=fork();
   if(pid==0){ //CHILD process (read process)
      int fd=open("NamedPipe",O_WRONLY);
      if(fd==-1){
        printf("Error opening the file!");
        close(fd);
        exit(1);
      }
      char buffer[100];
      ssize_t bytes=0;
      while(bytes=read(fd,buffer,sizeof(buffer))>0){
         write(res,buffer,sizeof(buffer));
      }
      close(fd);
      
   }
   else if(pid>0){ //PARENT process (write process)
      int fd=open("NamedPipe",O_WRONLY);
      if(fd==-1){
         printf("Error opening the file");
         exit(1);
      }
      int df=open(argv[1],O_RDONLY);
      if(df==-1){
         printf("Error opening the file!");
         exit(1);
      }
      char buff[100];
      ssize_t bytesR;
      while(bytesR=read(df,buff,sizeof(buff))>0){
         write(fd,buff,sizeof(buff));
      
      }
      close(fd);
      close(df);
      wait(NULL); //wait for the child process to complete
      
      int pipe=open("NamedPipe",O_RDONLY);
      if(pipe==-1){
         printf("Error opening the file!");
         exit(1);
      }
      char buff[100];
      ssize_t Bytes;
      while(Bytes=read(pipe,buff,sizeof(buff))>0){
         buff[Bytes]='\0';
         char * tok=strtok(buff," ");
         while(tok!=NULL){
            int num=atoi(tok);
            if(isPalindrome(num)==true){
                printf("%d",num);
            }
            tok=strtok(NULL," ");
         }
         printf("\n");
     }
     close(pipe);
   }
   else{
      printf("Error no process created!");
      exit(1);
   }

   return 0;
}
