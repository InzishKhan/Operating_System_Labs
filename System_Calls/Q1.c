#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>

void sort(int arr[10]){
  for(int i =0;i<10;i++){
     for(int j=i+1;j<10;j++){
        if(arr[i]>arr[j]){
           int temp=0;
           temp=arr[i];
           arr[i]=arr[j];
           arr[j]=temp;
        }
     }
  }
}

int main(int argc, char ** argv){
   int arr[10];
   int i,j=0;
   for(int i=0;i<10;i++){
     arr[j]=atoi(argv[i+1]);
     j++;
   }
   int a=fork();
   if(a==0){ //child process has been created
      sort(arr);
      for (int i=0;i<10;i++){
         printf("%d",arr[i]);
         printf("\t");
      }
      int ans=getpid();
      printf("Child process ID : %d\n",ans);
      exit(0);
   }
   else if(a>0){
      wait(NULL);
      printf("Parent has been successfully created");
   }
   else{ //child has not been created
      printf(" Child is not been created!!");
   }



}
