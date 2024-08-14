#include<stdio.h>
#include"header.h"

void sort(int array[],int order){
  if (order==1){ //order is true
      int a=0;
      for(int i =0;i<5;i++){
         for(int j=i+1;j<5;j++){
            if(array[i]>array[j]){
               a=array[i];
               array[i]=array[j];
               array[j]=a;
            }         
         }
      }
  }
  else{//order is false
     int b=0;
     for(int i=0;i<5;i++){
       for(int j=i+1;j<5;j++){
          if(array[i]<array[j]){
             b=array[i];
             array[i]=array[j];
             array[j]=b;
           }
        }
     }
  }
}

void findHighest(int array[],int nth){
    sort(array,1); //making the array in ascending order
    printf("The %d Highest Value is: %d",nth,array[5-nth]);

}

void print(int array[]){
   printf("Sorted Array is :\n");
   for(int i=0;i<5;i++){
     printf("%d ",array[i]);
     printf("\t");
   }
}
