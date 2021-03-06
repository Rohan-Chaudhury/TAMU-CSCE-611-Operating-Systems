// Name: Rohan Chaudhury
// CSCE 611 600: OPERATING SYSTEMS Project #1
// Email Address: rohan.chaudhury@tamu.edu
// UIN: 432001358


// Importing the necessary libraries

#include <pthread.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdbool.h>


//Defining macros

#define TRUE 1
#define FALSE 0

#define FRAME_SIZE 4
#define REF_SIZE 24



void run_and_print_LRU(int *reference_string){

printf("Running LRU");
printf("\n The provided reference string: \n");
int i=0;
    for(i=0;i<24;i++){
        printf("%d ",reference_string[i]);
    }
    printf("\n");

int page_faults=-1;

int mem[FRAME_SIZE];
int rem[FRAME_SIZE];
for (int i=0;i<FRAME_SIZE;i++){
mem[i]=-1;
rem[i]=-1;

}
int ti;
int indicator=0;
int j;
    printf("\n");
    printf ("\nInitial condition \n");

    printf("Pages in Memory: \t");
    for(int ii = 0; ii < FRAME_SIZE; ii++) {

            printf("%d ", mem[ii]);

    }
    printf ("\n");
    printf("Recently Removed Pages: ");
    for(int ii = 0; ii < FRAME_SIZE; ii++) {
            printf("%d ", rem[ii]);
    }
    printf("\n");
    int count_remove=0;
for (j=0; j<REF_SIZE; j++){
    
    int f1=0;
    int f2=0;
    
    indicator=0;
    for (int k=0; k<FRAME_SIZE;k++){
        if (reference_string[j]==mem[k]){
            f1=1;
            f2=1;
            break;
        }
    }
  int ref[FRAME_SIZE];
    if (f1==0){
        for (int i=0; i<FRAME_SIZE; i++)
        {
            if(mem[i]==-1){
                mem[i]=reference_string[j];
                f2=1;
                page_faults++;
                break;
            }
        }
    }

    if (f2==0){
        for (int i=0;i<FRAME_SIZE;i++){
            ref[i]=0;
        }
    for (int i = j-1, k=1;k<=FRAME_SIZE-1;k++,i--){
        for (int c=0;c<FRAME_SIZE;c++){
            if (mem[c]==reference_string[i]){
                ref[c]=1;
            }
        }
    }

    for (int i=0; i<FRAME_SIZE; i++){

        if (ref[i]==0){
            ti=i;
        }
    }

            int temp=-1;
            for (int i=0; i<FRAME_SIZE;i++){
                if (rem[i]==reference_string[j]){
                    temp=i;
                }
            }
            if (temp==-1){
            if (count_remove<FRAME_SIZE){
            rem[count_remove]=mem[ti];
            }
            else{
                rem[count_remove%FRAME_SIZE]=mem[ti];
            }
            count_remove++;
            }
            else{
                rem[temp]=mem[ti];
                count_remove=(temp+1)%FRAME_SIZE;
            }


    mem[ti]=reference_string[j];
    page_faults++;
    
    }

    printf("\n");
    printf ("\nLatest page received: %d \n", reference_string[j]);
    if (indicator==1){
        printf("\nPage present in memory\n");
    }
    else{
        printf("\nPage not present in memory, hence pushed to memory\n");
    }

    printf("Pages in Memory:\t ");
    for(int ii = 0; ii < FRAME_SIZE; ii++) {

            printf("%d ", mem[ii]);

    }
    printf ("\n");
    printf("Recently Removed Pages: ");
    for(int ii = 0; ii < FRAME_SIZE; ii++) {
            printf("%d ", rem[ii]);
    }
    printf("\nNumber of page faults: %d", page_faults);


}






}

void run_and_print_second_chance(int *reference_string){
printf("Running Second Chance");
printf("\n The provided reference string: \n");
int i=0;
    for(i=0;i<24;i++){
        printf("%d ",reference_string[i]);
    }
    printf("\n");

int page_faults=0;

int mem[FRAME_SIZE];
int rem[FRAME_SIZE];
int ref[FRAME_SIZE];
for (int i=0;i<FRAME_SIZE;i++){
mem[i]=-1;
rem[i]=-1;
ref[i]=0;
}
int indicator=0;
int j;
    printf("\n");
    printf ("\nInitial condition \n");

    printf("Pages in Memory: \t");
    for(int ii = 0; ii < FRAME_SIZE; ii++) {

            printf("%d ", mem[ii]);

    }
    printf ("\n");
    printf("Recently Removed Pages: ");
    for(int ii = 0; ii < FRAME_SIZE; ii++) {
            printf("%d ", rem[ii]);
    }
    printf("\n");
    int count_remove=0;
int cur_pos=0;
for (j=0; j<REF_SIZE; j++){
    
    
    indicator=0;
    for (int k=0; k<FRAME_SIZE;k++){
        if (reference_string[j]==mem[k]){
            indicator++;
            page_faults--;
            ref[k]=1;
        }
    }
    page_faults++;

    if (indicator==0){
        if (page_faults<=FRAME_SIZE){
            mem[cur_pos]=reference_string[j];
            cur_pos++;
        }
        else{
            
            cur_pos=(cur_pos)%FRAME_SIZE;
            while (ref[cur_pos]!=0){
                ref[cur_pos]=0;
                cur_pos=(cur_pos+1)%FRAME_SIZE;
            }
            int temp=-1;
            for (int i=0; i<FRAME_SIZE;i++){
                if (rem[i]==reference_string[j]){
                    temp=i;
                }
            }
            if (temp==-1){
            if (count_remove<FRAME_SIZE){
            rem[count_remove]=mem[cur_pos];
            }
            else{
                rem[count_remove%FRAME_SIZE]=mem[cur_pos];
            }
            count_remove++;
            }
            else{
                rem[temp]=mem[cur_pos];
                count_remove=(temp+1)%FRAME_SIZE;
            }
            mem[cur_pos]=reference_string[j];
            cur_pos++;
        }

    }
    printf("\n");
    printf ("\nLatest page received: %d \n", reference_string[j]);
    if (indicator==1){
        printf("\nPage present in memory\n");
    }
    else{
        printf("\nPage not present in memory, hence pushed to memory\n");
    }

    printf("Reference bit:\t ");
    for(int ii = 0; ii < FRAME_SIZE; ii++) {

            printf("%d ", ref[ii]);

    }
    printf ("\n");

    printf("Pages in Memory:\t ");
    for(int ii = 0; ii < FRAME_SIZE; ii++) {

            printf("%d ", mem[ii]);

    }
    printf ("\n");
    printf("Recently Removed Pages: ");
    for(int ii = 0; ii < FRAME_SIZE; ii++) {
            printf("%d ", rem[ii]);
    }
    printf("Number of page faults: %d", page_faults);
    printf("\n");

}

}







void run_and_print_FIFO(int *reference_string)
{

printf("Running FIFO");
printf("\n The provided reference string: \n");
int i=0;
    for(i=0;i<24;i++){
        printf("%d ",reference_string[i]);
    }
    printf("\n");

int page_faults=0;

int mem[FRAME_SIZE];
int rem[FRAME_SIZE];
for (int i=0;i<FRAME_SIZE;i++){
mem[i]=-1;
rem[i]=-1;
}
int indicator=0;
int j;
    printf("\n");
    printf ("\nInitial condition \n");

    printf("Pages in Memory: \t");
    for(int ii = 0; ii < FRAME_SIZE; ii++) {

            printf("%d ", mem[ii]);

    }
    printf ("\n");
    printf("Recently Removed Pages: ");
    for(int ii = 0; ii < FRAME_SIZE; ii++) {
            printf("%d ", rem[ii]);
    }
    printf("\n");
    int count_remove=0;
    int cur_pos=0;
    int page_to_remove=-1;
for (j=0; j<REF_SIZE; j++){
    
    
    indicator=0;
    for (int k=0; k<FRAME_SIZE;k++){
        if (reference_string[j]==mem[k]){
            indicator++;
            page_faults--;
        }
    }
    page_faults++;

   if (indicator==0){
        if (page_faults<=FRAME_SIZE){
            mem[cur_pos]=reference_string[j];
            cur_pos++;
        }
        else{
            cur_pos=cur_pos%FRAME_SIZE;
            int temp=-1;
            for (int i=0; i<FRAME_SIZE;i++){
                    if (rem[i]==reference_string[j]){
                        temp=i;
                    }
                }
                page_to_remove=mem[cur_pos];
            if (temp==-1){
                if (count_remove<FRAME_SIZE){
                rem[count_remove]=mem[cur_pos];
                }
                else{
                    rem[count_remove%FRAME_SIZE]=mem[cur_pos];
                }
                count_remove++;
            }
            else{
                rem[temp]=mem[cur_pos];
                count_remove=(temp+1)%FRAME_SIZE;
            }
            mem[cur_pos]=reference_string[j];
            cur_pos=(cur_pos+1)%FRAME_SIZE;
        }

    }
    printf("\n");
    printf ("\nLatest page received: %d \n", reference_string[j]);
    if (indicator==1){
        printf("\nPage present in memory\n");
    }
    else{
        printf("\nPage not present in memory, hence pushed to memory\n");
    }

    printf("Pages in Memory:\t ");
    for(int ii = 0; ii < FRAME_SIZE; ii++) {

            printf("%d ", mem[ii]);

    }
    printf ("\n");
    printf("Recently Removed Pages: ");
    for(int ii = 0; ii < FRAME_SIZE; ii++) {
            printf("%d ", rem[ii]);
    }
    printf("\nNumber of page faults: %d", page_faults);


}

}


//***************THE MAIN FUNCTION*********************//


int main()
{   
   //The given reference string

   int  reference_string[24]= {0, 2, 1, 3, 5, 4, 6, 3, 7, 4, 7, 3, 3, 5, 5, 3, 1, 1, 1, 7, 2, 3, 4, 1};
    printf("\n-1 indicates an empty frame\n");

    int i;


   //Asking the user for input regarding the choice of page replacement algorithm
    int choice;
   printf("\n Please choose from the following options: | 1 -> FIFO | 2 -> LRU | 3 -> Second chance |\n");
   printf("\n Enter an integer from 1, 2, or 3 which corresponds to FIFO, LRU, or Second Chance \n");
   scanf("%d",&choice);

    switch(choice) {
    case 1:
        //Running FIFO
        run_and_print_FIFO(reference_string);
        break;
    case 2:
        //Running LRU
        run_and_print_LRU(reference_string);
        break;
    case 3:
        //Running second chance
        run_and_print_second_chance(reference_string);
        break;
    default:
        printf("\nInvalid choice");
        printf("\nExpected either 1, 2, or 3, please re-run the program \n");
        exit(EXIT_FAILURE);
    printf("\n Program ended \n");
}
}