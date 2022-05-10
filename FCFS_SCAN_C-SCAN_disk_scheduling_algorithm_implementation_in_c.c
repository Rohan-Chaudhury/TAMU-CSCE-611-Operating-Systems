// Name: Rohan Chaudhury
// CSCE 611 600: OPERATING SYSTEMS Exam 2 Q20
// Email Address: rohan.chaudhury@tamu.edu
// UIN: 432001358
// Collaborated with: None

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

//request size of 1000
#define REQ_SIZE 1000

//Disk size of 5000
#define DISK_SIZE 5000


//Function to swap values of 2 variables

void swap_values(int *aa, int *bb) 
{ 
int temp = *aa; 
*aa = *bb; 
*bb = temp; 
}  

//The FCFS disk-scheduling algorithm
void run_and_print_FCFS(int head, int *requests){

    printf ("\n############## Running FCFS disk-scheduling algorithm: ##############\n");


    int head_mov_num=0;
  float average_seek;
    int dist=0;
    
  for(int j = 0; j<REQ_SIZE; j++){
      //calculating the absolute distance

    dist=abs(head-requests[j]);

    //adding the distance to the final count
    head_mov_num += dist;

    //the serviced request is the new head now
    head=requests[j];
  }

printf("\n");
    // seek sequence is the same as the request sequence for FCFS algorithm
    printf("The seek sequence for this algorithm is: \n");
 
    for (int i = 0; i < REQ_SIZE; i++) {
        printf("%d, ",requests[i]);
    }

    printf ("\n");

//printing the total number of head movements and average seek duration for the algorithm
      printf("\nThe total number of head movements for the FCFS algorithm is= %d\n", head_mov_num);
  average_seek = (float)head_mov_num/(float)REQ_SIZE;
  printf("\n");
  printf("The average seek duration for the algorithm is= %f\n", average_seek);

}

//The Scan disk-scheduling algorithm


void run_and_print_SCAN( int head, int *requests){
  printf ("\n");
printf ("\n############## Will now run SCAN disk-scheduling algorithm from both left and right directions: ##############\n");


  int seek_sequence[1000];
  int s=0;
int temp_head=head;
    printf ("\n############## 1. Running SCAN disk-scheduling algorithm from right direction: ##############\n");
   int head_mov_num=0;
  float average_seek;
    int dist=0;
    //creating two arrays to store request values to the left/right of the head respectively
    int left_req[1000], right_req[1000];


//appending the final position to right_req as when SCAN algorithm starts from the right direction it goes to the rightmost end
    right_req[0]=DISK_SIZE-1;
    int lt=0,rt=1;
    //dividing the requests on the basis of whether their values are towards the left or right of the head
    for (int i=0; i<REQ_SIZE; i++){
        if (requests[i]<head){
            left_req[lt]=requests[i];
            lt++;
        }
        else{
            right_req[rt]=requests[i];
            rt++;
        }

    }


//sorting the left and right arrays
   for(int a = 0; a<rt-1; a++){
    for(int b = a+1; b<rt; b++){
        if(right_req[a] > right_req[b]){
            swap_values(&right_req[a], &right_req[b]);
      }
    }
  }

  for(int a = 0; a<lt-1; a++){
    for(int b = a+1; b<lt; b++){
      if(left_req[a] > left_req[b]){
            swap_values(&left_req[a], &left_req[b]);
      }
    }
  }

  //Going towards the right direction and adding the absolute distance
   
  for(int a = 0; a < rt; a++) {
    if (a!=rt-1){
      seek_sequence[s]=right_req[a];
      s++;
    }
    dist=abs(head-right_req[a]);
    head_mov_num += dist;
    head=right_req[a];
  }
 

 //Once the end is reached on the right side, the direction of traversal changes and the head now travels from the end 
 //of the left array to its start towards the left side
  for (int a = lt - 1; a>=0; a--) {
    seek_sequence[s]=left_req[a];
    s++;
    dist=abs(head-left_req[a]);
    head_mov_num += dist;
    head=left_req[a];

  }
printf("\n");
//Priniting the seek sequence
    printf("The seek sequence for this algorithm is: \n");
 
    for (int i = 0; i < REQ_SIZE; i++) {
        printf("%d, ",seek_sequence[i]);
    }
    printf("\n");

//printing the total number of head movements and average seek duration for the algorithm
    printf("\n");

      printf("The total number of head movements for the SCAN algorithm \nwhen you initially traverse from the right direction is= %d\n", head_mov_num);
      
      // printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa%d\n", left_req[0]);
      // printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa%d\n", left_req[lt-1]);
    printf("\n");
  average_seek = (float)head_mov_num/(float)REQ_SIZE;
  printf("The average seek duration for the algorithm is= %f\n", average_seek);

  int seek_sequence2[1000];
  int s2=0;

  printf ("\n############## 2. Running SCAN disk-scheduling algorithm from left direction: ##############\n");
  head=temp_head;
   int head_mov_num2=0;
  float average_seek2;
    int dist2=0;
    //creating two arrays to store request values to the left/right of the head respectively
    int left_req2[1000], right_req2[1000];
//appending the start position (0) to left_req as when SCAN algorithm starts from the left direction it goes to the leftmost end
    left_req2[0]=0;
    int lt2=1,rt2=0;
        //dividing the requests on the basis of whether their values are towards the left or right of the head
    for (int i2=0; i2<REQ_SIZE; i2++){
        if (requests[i2]<head){
            left_req2[lt2]=requests[i2];
            lt2++;
        }
        else{
            right_req2[rt2]=requests[i2];
            rt2++;
        }

    }

    //sorting the left and right arrays

   for(int a2 = 0; a2<rt2-1; a2++){
    for(int b2 = a2+1; b2<rt2; b2++){
        if(right_req2[a2] > right_req2[b2]){
            swap_values(&right_req2[a2], &right_req2[b2]);
      }
    }
  }

  for(int a2 = 0; a2<lt2-1; a2++){
    for(int b2 = a2+1; b2<lt2; b2++){
      if(left_req2[a2] > left_req2[b2]){
            swap_values(&left_req2[a2], &left_req2[b2]);
      }
    }
  }
   
   //Going towards the left, traversing the left array in the descending order and adding the absolute distance
 
  for (int a2 = lt2 - 1; a2>=0; a2--) {
    if (a2!=0){
      seek_sequence2[s2]=left_req2[a2];
      s2++;
    }
    dist2=abs(head-left_req2[a2]);
    head_mov_num2 += dist2;
    head=left_req2[a2];

  }

 //Once the end is reached on the left side, the direction of traversal changes and the head now travels from the start 
 //of the right array to its end towards the right side
  for(int a2 = 0; a2 < rt2; a2++) {
      seek_sequence2[s2]=right_req2[a2];
      s2++;
    dist2=abs(head-right_req2[a2]);
    head_mov_num2 += dist2;
    head=right_req2[a2];
  }


// printf("sssssssssssssssssssss%d\n", right_req2[rt2-1]);

     printf("\n");
    //Priniting the seek sequence
    printf("The seek sequence for this algorithm is: \n");
 
    for (int i = 0; i < REQ_SIZE; i++) {
        printf("%d, ",seek_sequence2[i]);
    }
    
//printing the total number of head movements and average seek duration for the algorithm
    printf("\n");
    printf("\n");
      printf("The total number of head movements for the SCAN algorithm \nwhen you initially traverse from the left direction is= %d\n", head_mov_num2);
  average_seek2 = (float)head_mov_num2/(float)REQ_SIZE;
  printf("\n");
  printf("The average seek duration for the algorithm is= %f\n", average_seek2);

}


//The C-Scan disk-scheduling algorithm

void run_and_print_C_SCAN(int head, int *requests){
int seek_sequence[1500];
int s=0;
     printf ("\n############## Running C-Scan disk-scheduling algorithm: ##############\n");
    int head_mov_num=0;
  float average_seek;
    int dist=0;

    //creating two arrays to store the request values to the left and right of the head respectively
    int left_req[1000], right_req[1000];
    //If the algorithm is going towards the right, it will first travel to the rightmost point (DISK_SIZE - 1 ) and then jump 
    //to the start position 0 and continue scanning towards the right
    left_req[0]=0;
    right_req[0]=DISK_SIZE-1;
    int lt=1,rt=1;

    //Diving the requests based on whether they are to the left/right of the head
    for (int i=0; i<REQ_SIZE; i++){
        if (requests[i]<head){
            left_req[lt]=requests[i];
            lt++;
        }
        else{
            right_req[rt]=requests[i];
            rt++;
        }

    }

//sorting the left and right arrays

   for(int a = 0; a<rt-1; a++){
    for(int b = a+1; b<rt; b++){
        if(right_req[a] > right_req[b]){
            swap_values(&right_req[a], &right_req[b]);
      }
    }
  }

  for(int a = 0; a<lt-1; a++){
    for(int b = a+1; b<lt; b++){
      if(left_req[a] > left_req[b]){
            swap_values(&left_req[a], &left_req[b]);
      }
    }
  }
   

   //First we service the requests on the right side of the head
  for(int a = 0; a < rt; a++) {
    seek_sequence[s]=right_req[a];
    s++;
      //calculating the absolute distance between current head and current request and then adding that value to the final output
    dist=abs(head-right_req[a]);
    head_mov_num += dist;
    //updating the head
    head=right_req[a];
  }
//  printf("%d\n", head_mov_num);

//Once we reach the right most end we jump to the start
  head = 0;
//adding the distance from the end to the start of the disk 
    head_mov_num += DISK_SIZE-1;

//Now processing the remaining requests which are on the left of the head 
//Processing happens in the right direction
//  printf("%d\n", head_mov_num);
  for (int a = 0; a < lt; a++) {
    seek_sequence[s]=left_req[a];
    s++;
      //calculating the absolute distance between current head and current request and then adding that value to the final output
    dist=abs(head-left_req[a]);
    head_mov_num += dist;
    //updating the head
    head=left_req[a];

  }

printf("\n");
//Priniting the seek sequence
    printf("The seek sequence for this algorithm is: \n");
 
    for (int i = 0; i < REQ_SIZE+2; i++) {
        printf("%d, ",seek_sequence[i]);
    }


//printing the total number of head movements and average seek duration for the algorithm
// printf("%d\n", head_mov_num);
    printf("\n");
    printf("\n");
      printf("The total number of head movements for the C-Scan algorithm is= %d\n", head_mov_num);
  average_seek = (float)head_mov_num/(float)REQ_SIZE;
  printf("\n");
  printf("The average seek duration for the algorithm is= %f\n", average_seek);


}

//***************THE MAIN FUNCTION*********************//


int main()
{   
  time_t tm;

    
  srand((unsigned) time(&tm));


    //Generating a random series of 1,000-cylinder requests (1000 random integers)
    int requests[REQ_SIZE];    
    printf ("\n");
    printf ("Generating a random series of 1,000-cylinder requests (1000 random integers) between 0 and 5000\n");
    for(int i = 0;i < REQ_SIZE;i++){
        requests[i] = rand() % 5000;
        }
    printf ("Printing the 1,000-cylinder requests\n");
    for(int i = 0; i < REQ_SIZE ; i++){
      printf("%d, ", requests[i]);
        }
    int head;
    printf("\n\nPlease enter the initial position of the disk head:\n");
    scanf("%d", &head);


   //Asking the user for input regarding the choice of disk-scheduling algorithms
    int choice;
   printf("\n Please choose from the following options: \n| 1 -> Run all 3 algorithms one-by-one: FCFS, SCAN (for both left and right directions), C-SCAN |\n| 2 -> Run FCFS |\n| 3 -> Run SCAN (will show ouput for both left and right directions) |\n| 4 -> Run C-SCAN |");
   printf("\n Enter an integer from 1, 2, 3, or 4 which corresponds to running all disk-scheduling algorithms, running FCFS only, running SCAN only (will show ouput for both left and right directions) , or running C-SCAN only \n");
   scanf("%d",&choice);

    switch(choice) {
    case 1:
        //Running all 3 algorithms one-by-one: FCFS, SCAN, C-SCAN
        run_and_print_FCFS(head, requests);
        run_and_print_SCAN(head, requests);
        run_and_print_C_SCAN(head, requests);
        break;
    case 2:
        //Running FCFS
        run_and_print_FCFS(head, requests);
        break;
    case 3:
        //Running SCAN
        run_and_print_SCAN(head, requests);
        break;
    case 4:
        //Run C-SCAN
        run_and_print_C_SCAN(head, requests);
        break;
    default:
        printf("\nInvalid choice");
        printf("\nExpected either 1, 2, 3, or 4 please re-run the program \n");
        exit(EXIT_FAILURE);
    printf("\n Program ended \n");
}
 return 0;
}