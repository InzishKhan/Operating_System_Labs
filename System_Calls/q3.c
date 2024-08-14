#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>

int main(){
   int ProcessNo=0;
   int trackC=0;
   printf("Enter the no. of processes : \n");
   scanf("%d",&ProcessNo);
   printf("You entered the Number : %d\n",ProcessNo);
   if ( ProcessNo<1 || ProcessNo>10){
      exit(1);
   }
   for (int i=1;i<=ProcessNo;i++){
      int a=fork();
      if(a==0){  //child process has been created
         printf("Child process %d ID:%d\n",trackC+i,getpid());
         printf("Child Process %d Parent ID : %d\n",trackC+i,getppid()); 
         break;
      } 
      if(a==-1) {
        //child process is not created
        printf("Child process is not created");
        exit(1);
      }   
   }
   wait(NULL); 
   return 0;

}
