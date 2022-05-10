// Name: Rohan Chaudhury
// CSCE 611 600: OPERATING SYSTEMS Project #2
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

// Number of pages
#define REF_SIZE 100

//variable declared to take the system time as input
struct timeval system_time;

//using printf to display output information in console
//using fprintf to store output information in the respective output files

//________________Function for Least Recently Used (LRU) page replacement implementation____________________

void run_and_print_LRU(FILE *input_file, FILE *output_file,int FRAME_SIZE){

printf("\n\n\n\n******************************Running LRU algorithm******************************\n");


fprintf(output_file,"\n\n\n\n******************************Running LRU algorithm******************************\n");


//variable to store the number of page faults
int page_faults=0;


//array to store the current pages in memory
int mem[FRAME_SIZE];

//array to store the recently removed pages from the memory which are now stored in disk
int rem[FRAME_SIZE];

//initializing both the array values to -1, where -1 signifies an empty slot in the respective arrays
for (int i=0;i<FRAME_SIZE;i++){
mem[i]=-1;
rem[i]=-1;

}
int ti;

//indicator variable denotes whether a page fault has occurred or not
int indicator=0;

int j;
printf("\n '-1' indicates an empty frame\n");
printf ("\nInitial conditions: \n");

printf("Pages in Memory: \t");



fprintf(output_file,"\n '-1' indicates an empty frame\n");
fprintf(output_file,"\nInitial conditions: \n");

fprintf(output_file,"Pages in Memory: \t");

//printing out the initial states of the arrays

for(int ii = 0; ii < FRAME_SIZE; ii++) {

        printf("%d ", mem[ii]);

        fprintf(output_file,"%d ", mem[ii]);

}
printf ("\n");
printf("Recently Removed Pages moved to disk: ");



fprintf(output_file,"\n");
fprintf(output_file,"Recently Removed Pages moved to disk: ");
for(int ii = 0; ii < FRAME_SIZE; ii++) {
        printf("%d ", rem[ii]);

        fprintf(output_file,"%d ", rem[ii]);
}
printf("\n");


fprintf(output_file,"\n");

//count_remove variable stores the pointer in the rem array indicating the next place to store the removed page in disk
int count_remove=0;

//'used' stores the relative count of when a page is used in the ref array 
int used=0;

//ref array stores the relative count of when the frames in memory were used
int ref[FRAME_SIZE];

//lru is used to store the position of the least recently used page in memory
int lru;

//page_to_remove is used to store the page which is removed from memory in the current cycle
int page_to_remove=-1;

//Iterating over all the 100 pages in the input file
for (j=0; j<REF_SIZE; j++){

    //reading each individual page in each iteration
    int current_page;
    fscanf(input_file, "%d", &current_page);

    //f1=0 indicates that the current page which is read is not in memory
    //f2=0 indicates that the current page which is read is not in memory and there are no empty slots in memory so a page 
    //replacement will occur
    int f1=0;
    int f2=0;
    
    //checking if the current page is in memory
    for (int k=0; k<FRAME_SIZE;k++){
        if (current_page==mem[k]){
            //if current page is in memory then no page fault or replacement occurs
            //incrementing and storing used everytime a page operation occurs
            used++;
            ref[k]=used;
            f1=1;
            f2=1;
            indicator=1;
            break;
        }
    }
  //when current page is not found in memory
    if (f1==0){
        
        for (int i=0; i<FRAME_SIZE; i++)
        {
            //checking to see if an empty slot is available in memory
            if(mem[i]==-1){
                //if empty slot is available then a page fault occurs but no page replacement is required
                //incrementing and storing used everytime a page operation occurs
                used++;
                ref[i]=used;
                mem[i]=current_page;
                f2=1;
                indicator=0;
                page_faults++;
                break;
            }
        }
    }

    //when current page is not found in memory and no empty slot is available in memory

    if (f2==0){
        //page replacement will occur in memory in this case
        //finding the least recently used page
        //initializing the minimum value in the ref array to ref[0] and lru to 0
        int mini=ref[0];
        lru=0;

        //iterating over the ref array to find the position of the least recently used page
        for (int k=1; k<FRAME_SIZE; k++){
            if (ref[k]<mini){
                mini=ref[k];
                lru=k;
            }
        }
        //incrementing and storing used everytime a page operation occurs
        used++;
        
        ref[lru]=used;
        

        //storing the page to remove
    
        page_to_remove=mem[lru];


        //checking to see if the current page in this cycle is present in disk
        //if current page is in disk then we swap the current page in disk with the page to remove in memory and vice versa
        int temp=-1;
        for (int i=0; i<FRAME_SIZE;i++){
            if (rem[i]==current_page){
                //current page is in disk, storing its position in temp
                temp=i;
            }
        }
        if (temp==-1){
            //current page is not in disk
            //using the count_remove pointer for storing the page_to_remove in disk
            if (count_remove<FRAME_SIZE){
                //storing the removed page from memory to disk
                rem[count_remove]=mem[lru];
                }
            else{
                rem[count_remove%FRAME_SIZE]=mem[lru];
                }
            //incrementing the count_remove pointer
            count_remove++;
        }
        else{
            //if current page is in disk then we swap the current page in disk with the page to remove in memory and vice versa
            rem[temp]=mem[lru];
            count_remove=(temp+1)%FRAME_SIZE;
        }

    //storing the current page in memory
    mem[lru]=current_page;

    indicator=0;
    //incrementing the page faults number
    page_faults++;
    
    }

    //getting the system time and storing it in microseconds
    gettimeofday(&system_time, NULL);
    long seconds = (system_time.tv_sec);
    long microseconds = ((seconds * 1000000) + system_time.tv_usec);

    printf("\n");
    printf ("\nNext cycle: Current page received/referenced: %d \n", current_page);
    printf("SYSTEM Time: %ld microseconds",microseconds);


    fprintf(output_file,"\n");
    fprintf(output_file,"\nNext cycle: Current page received/referenced: %d \n", current_page);
    fprintf(output_file,"SYSTEM Time: %ld microseconds",microseconds);


    //printing out the information based on the values of indicator and page_to_remove variable
    if (indicator==1){

        //indication=1 means no page fault has occured as page is in memory
        printf("\nNo Page Fault occured as Page is present in memory\n");


        fprintf(output_file,"\nNo Page Fault occured as Page is present in memory\n");
    }
    else{

        //indication=0 means page fault has occured as page is not in memory
        printf("\nPage Fault occurred as Page is not present in memory\n");


        fprintf(output_file,"\nPage Fault occurred as Page is not present in memory\n");
        if (page_to_remove==-1){

            //page_to_remove=-1 means that slots were available in memory hence no page replacement has occurred
            printf("Slots were available in memory so no page was replaced\n");


            fprintf(output_file,"Slots were available in memory so no page was replaced\n");
        }
        else{
            printf("Page which is replaced : %d \n", page_to_remove);


            fprintf(output_file,"Page which is replaced : %d \n", page_to_remove);
        }
    }

    //printing the pages in memory and recently removed pages from memory and stored in disk for this cycle

    printf("Pages in Memory:\t ");


    fprintf(output_file,"Pages in Memory:\t ");
    for(int ii = 0; ii < FRAME_SIZE; ii++) {

            printf("%d ", mem[ii]);

            fprintf(output_file,"%d ", mem[ii]);

    }
    printf ("\n");
    printf("Recently Removed Pages moved to disk: ");


    fprintf(output_file,"\n");
    fprintf(output_file,"Recently Removed Pages moved to disk: ");
    for(int ii = 0; ii < FRAME_SIZE; ii++) {
            printf("%d ", rem[ii]);

            fprintf(output_file,"%d ", rem[ii]);
    }
    printf("\nNumber of page faults till now: %d", page_faults);


    fprintf(output_file,"\nNumber of page faults till now: %d", page_faults);


}


//printing the total number of page faults
printf("\n\nTotal number of page faults: %d \n", page_faults);

fprintf(output_file,"\n\nTotal number of page faults: %d \n", page_faults);

fclose(output_file);
}


//_____________________Function for Second Chance Page Replacement implementation_____________________________


void run_and_print_second_chance(FILE *input_file,FILE *output_file, int FRAME_SIZE){
printf("\n\n\n\n******************************Running Second Chance******************************\n");


fprintf(output_file,"\n\n\n\n******************************Running Second Chance******************************\n");

//variable to store the number of page faults
int page_faults=0;


//array to store the current pages in memory
int mem[FRAME_SIZE];
//array to store the recently removed pages from the memory which are now stored in disk
int rem[FRAME_SIZE];
//array to store a refernce bit for each frame in memory indicating
int ref[FRAME_SIZE];

//initializing both the array values to -1, where -1 signifies an empty slot in the respective arrays
//initializing ref array values to 0 indicating that all the reference bits are initially 0

for (int i=0;i<FRAME_SIZE;i++){
mem[i]=-1;
rem[i]=-1;
ref[i]=0;
}
//indicator variable denotes whether a page fault has occurred or not
int indicator=0;
int j;
    printf("\n '-1' indicates an empty frame\n");
    printf ("\nInitial conditions: \n");

    printf("Pages in Memory: \t");



    fprintf(output_file,"\n '-1' indicates an empty frame\n");
    fprintf(output_file,"\nInitial conditions: \n");

    fprintf(output_file,"Pages in Memory: \t");

    //printing out the initial states of the arrays
    for(int ii = 0; ii < FRAME_SIZE; ii++) {

            printf("%d ", mem[ii]);

            fprintf(output_file,"%d ", mem[ii]);

    }
    printf ("\n");
    printf("Recently Removed Pages moved to disk: ");


    fprintf(output_file,"\n");
    fprintf(output_file,"Recently Removed Pages moved to disk: ");
    for(int ii = 0; ii < FRAME_SIZE; ii++) {
            printf("%d ", rem[ii]);

             fprintf(output_file,"%d ", rem[ii]);
    }
    printf("\n");

    fprintf(output_file,"\n");
    //count_remove variable stores the pointer in the rem array indicating the next place to store the removed page in disk
    int count_remove=0;
//cur_pos stores the current position of the pointer in memory
//it points to the next potential page for replacement
int cur_pos=0;

//page_to_remove is used to store the page which is removed from memory in the current cycle
int page_to_remove=-1;

//Iterating over all the 100 pages in the input file
for (j=0; j<REF_SIZE; j++){

    //reading each individual page in each iteration
    int current_page;
    fscanf(input_file, "%d", &current_page);
    
    indicator=0;

    //checking if the current page is in memory
    for (int k=0; k<FRAME_SIZE;k++){
        if (current_page==mem[k]){
            //if current page is in memory then no page fault or replacement occurs
            indicator++;
            //decrementing page faults here as we will again increment it outside this loop
            //thus balancing it out as no page_fault is supposed to occur in this case
            page_faults--;
            //changing the reference bit for the position where current page was accessed to 1
            ref[k]=1;
        }
    }
    //incrementing the number of page_faults
    page_faults++;
    //when current page is not found in memory
    if (indicator==0){
        if (page_faults<=FRAME_SIZE){
            //if page_faults is less than number of frames in memory then
            //an empty slot is available in memory

            //storing the current page in the empty slot and incrementing cur_pos
            mem[cur_pos]=current_page;
            cur_pos++;
        }
        else{
            //when current page is not found in memory and no empty slot is available in memory
            //page replacement will occur in memory in this case
            
            cur_pos=(cur_pos)%FRAME_SIZE;
            //checking the cur_pos and its reference bits
            while (ref[cur_pos]!=0){

                //iterating over the reference bits array until
                //a reference bit value of 0 is reached in a position
                //and setting all the reference bits of the encountered positions 
                //from 1 to 0
                ref[cur_pos]=0;
                
                cur_pos=(cur_pos+1)%FRAME_SIZE;
            }
            //now cur_pos stores the position of the page to remove from memory
            //storing the page to remove
            
            page_to_remove=mem[cur_pos];

        //checking to see if the current page in this cycle is present in disk
        //if current page is in disk then we swap the current page in disk with the page to remove in memory and vice versa
        
            int temp=-1;
            for (int i=0; i<FRAME_SIZE;i++){
                if (rem[i]==current_page){
                    //current page is in disk, storing its position in temp
                
                    temp=i;
                }
            }


            if (temp==-1){
            //current page is not in disk
            //using the count_remove pointer for storing the page_to_remove in disk
            if (count_remove<FRAME_SIZE){
                //storing the removed page from memory to disk
            rem[count_remove]=mem[cur_pos];
            }
            else{
                rem[count_remove%FRAME_SIZE]=mem[cur_pos];
            }
             //incrementing the count_remove pointer
            count_remove++;
            }
            else{
                //if current page is in disk then we swap the current page in disk with the page to remove in memory and vice versa
                rem[temp]=mem[cur_pos];
                count_remove=(temp+1)%FRAME_SIZE;
            }
            //storing the current page in memory
            mem[cur_pos]=current_page;
            //incrementing cur_pos
            cur_pos++;
        }

    }
//getting the system time and storing it in microseconds
    gettimeofday(&system_time, NULL);
    long seconds = (system_time.tv_sec);
    long microseconds = ((seconds * 1000000) + system_time.tv_usec);
    printf("\n");
    printf ("\nNext cycle: Current page received/referenced: %d \n", current_page);
    printf("SYSTEM Time: %ld microseconds",microseconds);


    fprintf(output_file,"\n");
    fprintf(output_file,"\nNext cycle: Current page received/referenced: %d \n", current_page);
    fprintf(output_file,"SYSTEM Time: %ld microseconds",microseconds);
    //printing out the information based on the values of indicator and page_to_remove variable
    
    if (indicator==1){

        //indication=1 means no page fault has occured as page is in memory
        printf("\nNo Page Fault occured as Page is present in memory\n");

        fprintf(output_file,"\nNo Page Fault occured as Page is present in memory\n");
    }
    else{

        //indication=0 means page fault has occured as page is not in memory
        printf("\nPage Fault occurred as Page is not present in memory\n");

        fprintf(output_file,"\nPage Fault occurred as Page is not present in memory\n");
        if (page_to_remove==-1){
            //page_to_remove=-1 means that slots were available in memory hence no page replacement has occurred
            printf("Slots were available in memory so no page was replaced\n");

            fprintf(output_file,"Slots were available in memory so no page was replaced\n");
        }
        else{
            printf("Page which is replaced : %d \n", page_to_remove);

            fprintf(output_file,"Page which is replaced : %d \n", page_to_remove);
        }
    }

//printing the pages in memory and recently removed pages from memory and stored in disk for this cycle

    printf("Pages in Memory:\t ");

    fprintf(output_file,"Pages in Memory:\t ");
    for(int ii = 0; ii < FRAME_SIZE; ii++) {

            printf("%d ", mem[ii]);

            fprintf(output_file,"%d ", mem[ii]);

    }
    printf ("\n");
    printf("Recently Removed Pages moved to disk: ");


    fprintf(output_file,"\n");
    fprintf(output_file,"Recently Removed Pages moved to disk: ");
    for(int ii = 0; ii < FRAME_SIZE; ii++) {
            printf("%d ", rem[ii]);

            fprintf(output_file,"%d ", rem[ii]);
    }
    printf("\nNumber of page faults: %d", page_faults);
    printf("\n");


    fprintf(output_file,"\nNumber of page faults: %d", page_faults);
    fprintf(output_file,"\n");


}

//printing the total number of page faults
printf("\n\nTotal number of page faults: %d \n", page_faults);


fprintf(output_file,"\n\nTotal number of page faults: %d \n", page_faults);
fclose(output_file);
}



//___________________________Function for First In First Out (FIFO) page replacement implementation_________________________



void run_and_print_FIFO(FILE *input_file,FILE *output_file, int FRAME_SIZE)
{

printf("\n\n\n\n******************************Running FIFO******************************\n");

fprintf(output_file,"\n\n\n\n*****************************Running FIFO******************************\n");

//variable to store the number of page faults
int page_faults=0;

//array to store the current pages in memory
int mem[FRAME_SIZE];

//array to store the recently removed pages from the memory which are now stored in disk
int rem[FRAME_SIZE];
//initializing both the array values to -1, where -1 signifies an empty slot in the respective arrays
for (int i=0;i<FRAME_SIZE;i++){
mem[i]=-1;
rem[i]=-1;
}
//indicator variable denotes whether a page fault has occurred or not
int indicator=0;
int j;
    printf("\n '-1' indicates an empty frame\n");
    printf ("\nInitial conditions: \n");

    printf("Pages in Memory: \t");


    fprintf(output_file,"\n '-1' indicates an empty frame\n");
    fprintf(output_file,"\nInitial conditions: \n");

    fprintf(output_file,"Pages in Memory: \t");
    //printing out the initial states of the arrays
    for(int ii = 0; ii < FRAME_SIZE; ii++) {

            printf("%d ", mem[ii]);

            fprintf(output_file,"%d ", mem[ii]);

    }
    printf ("\n");
    printf("Recently Removed Pages moved to disk: ");


    fprintf(output_file,"\n");
    fprintf(output_file,"Recently Removed Pages moved to disk: ");
    for(int ii = 0; ii < FRAME_SIZE; ii++) {
            printf("%d ", rem[ii]);

            fprintf(output_file,"%d ", rem[ii]);
    }
    printf("\n");

    fprintf(output_file,"\n");
    //count_remove variable stores the pointer in the rem array indicating the next place to store the removed page in disk
    int count_remove=0;
    //page_to_remove is used to store the page which is removed from memory in the current cycle
    int page_to_remove=-1;

    //cur_pos stores the current position of the pointer in memory
//it points to the next potential page for replacement
    int cur_pos=0;

    //Iterating over all the 100 pages in the input file
for (j=0; j<REF_SIZE; j++){
    //reading each individual page in each iteration
    int current_page;
    fscanf(input_file, "%d", &current_page);
    indicator=0;

    //checking if the current page is in memory
    for (int k=0; k<FRAME_SIZE;k++){
        if (current_page==mem[k]){
            //if current page is in memory then no page fault or replacement occurs
            indicator++;
            //decrementing page faults here as we will again increment it outside this loop
            //thus balancing it out as no page_fault is supposed to occur in this case
            page_faults--;
        }
    }
    //incrementing the number of page_faults
    page_faults++;
//when current page is not found in memory
    if (indicator==0){
        if (page_faults<=FRAME_SIZE){
            //if page_faults is less than number of frames in memory then
            //an empty slot is available in memory
            //storing the current page in the empty slot and incrementing cur_pos
            mem[cur_pos]=current_page;
            cur_pos++;
        }
        else{
             //when current page is not found in memory and no empty slot is available in memory
            //page replacement will occur in memory in this case
            
            //cur_pos gives the position of the page to replace
            cur_pos=cur_pos%FRAME_SIZE;

            //checking to see if the current page in this cycle is present in disk
        //if current page is in disk then we swap the current page in disk with the page to remove in memory and vice versa
        
            int temp=-1;
            for (int i=0; i<FRAME_SIZE;i++){
                    if (rem[i]==current_page){
                        //current page is in disk, storing its position in temp
                
                        temp=i;
                    }
                }
            //now cur_pos stores the position of the page to remove from memory
            //storing the page to remove
                page_to_remove=mem[cur_pos];
            if (temp==-1){
                //current page is not in disk
            //using the count_remove pointer for storing the page_to_remove in disk
            
                if (count_remove<FRAME_SIZE){

                    //storing the removed page from memory to disk
                rem[count_remove]=mem[cur_pos];
                }
                else{
                    rem[count_remove%FRAME_SIZE]=mem[cur_pos];
                }
                //incrementing the count_remove pointer
                count_remove++;
            }
            else{
                //if current page is in disk then we swap the current page in disk with the page to remove in memory and vice versa
                rem[temp]=mem[cur_pos];
                count_remove=(temp+1)%FRAME_SIZE;
            }
            //storing the current page in memory
            mem[cur_pos]=current_page;
            //incrementing cur_pos
            cur_pos=(cur_pos+1)%FRAME_SIZE;
        }

    }
//getting the system time and storing it in microseconds

    gettimeofday(&system_time, NULL);
    long seconds = (system_time.tv_sec);
    long microseconds = ((seconds * 1000000) + system_time.tv_usec);
    printf("\n");
    printf ("\nNext cycle: Current page received/referenced: %d \n", current_page);
    printf("SYSTEM Time: %ld microseconds ",microseconds);


    fprintf(output_file,"\n");
    fprintf(output_file,"\nNext cycle: Current page received/referenced: %d \n", current_page);
    fprintf(output_file,"SYSTEM Time: %ld microseconds ",microseconds);
//printing out the information based on the values of indicator and page_to_remove variable
    if (indicator==1){
        //indication=1 means no page fault has occured as page is in memory
        
        printf("\nNo Page Fault occured as Page is present in memory\n");

         fprintf(output_file,"\nNo Page Fault occured as Page is present in memory\n");
    }
    else{
        //indication=0 means page fault has occured as page is not in memory
       
        printf("\nPage Fault occurred as Page is not present in memory\n");


        fprintf(output_file,"\nPage Fault occurred as Page is not present in memory\n");
        if (page_to_remove==-1){
            //page_to_remove=-1 means that slots were available in memory hence no page replacement has occurred
            
            printf("Slots were available in memory so no page was replaced\n");

            fprintf(output_file,"Slots were available in memory so no page was replaced\n");
        }
        else{
            printf("Page which is replaced : %d \n", page_to_remove);

            fprintf(output_file,"Page which is replaced : %d \n", page_to_remove);
        }
    }


//printing the pages in memory and recently removed pages from memory and stored in disk for this cycle

    printf("Pages in Memory:\t ");

    fprintf(output_file,"Pages in Memory:\t ");
    for(int ii = 0; ii < FRAME_SIZE; ii++) {

            printf("%d ", mem[ii]);

            fprintf(output_file,"%d ", mem[ii]);

    }
    printf ("\n");
    printf("Recently Removed Pages moved to disk: ");


    fprintf(output_file,"\n");
    fprintf(output_file,"Recently Removed Pages moved to disk: ");
    for(int ii = 0; ii < FRAME_SIZE; ii++) {
            printf("%d ", rem[ii]);

            fprintf(output_file,"%d ", rem[ii]);
    }
    printf("\nNumber of page faults: %d", page_faults);

    fprintf(output_file,"\nNumber of page faults: %d", page_faults);


}

//printing the total number of page faults
printf("\n\nTotal number of page faults: %d \n", page_faults);


fprintf(output_file,"\n\nTotal number of page faults: %d \n", page_faults);

fclose(output_file);
}





//***************THE MAIN FUNCTION*********************//


int main()
{   
    srand(time(NULL));
    //declaring the input and output files
    FILE *input_file;
    
    FILE *output_file;

    //checking if input file is present
    if (input_file = fopen("chaudhuryr_proj2_input.txt", "r")) 
    {
        //input file exists
        printf("Input file exists in directory");

    }
    else
    {   
        //input file doesn't exist, then we create one and store 100 random values between 0 and 15
        printf("Input file doesn't exist, creating file");
        input_file  = fopen ("chaudhuryr_proj2_input.txt", "w");

        int temp;

        for (int i = 0; i < 100; i++)  
            {  
                temp=rand()%16;

                fprintf(input_file, "%d\n",temp);
            }
        //closing the input file after storing the values
        fclose(input_file);
        //opening the input_file in read mode
        input_file  = fopen ("chaudhuryr_proj2_input.txt", "r");
    }
    
    

        
    printf("\n '-1' indicates an empty frame\n");

    int i;


   //Asking the user for input regarding the choice of page replacement implementation
    int choice;
   printf("\n Please choose from the following options: \n| 1 -> FIFO |\n| 2 -> LRU |\n| 3 -> Second chance |\n");
   printf("\n Enter an integer from 1, 2, or 3 which corresponds to FIFO, LRU, or Second Chance \n -->");
   scanf("%d",&choice);


//Asking the user for input regarding the frame size
    int choice2;
    int FRAME_SIZE;
    printf("\n Please choose from the following options of Page Frames: \n| 1 -> Four-page frames |\n| 2 -> Eight-page frames | \n");
   printf("\n Enter an integer from 1 and 2 which corresponds to the choice of Four-page frames or Eight-page frames respectively \n -->");
   scanf("%d",&choice2);

   //creating separate output files based on frame sizes

    if (choice2/4==2 || choice2==2){
        FRAME_SIZE=8;
        output_file  = fopen ("chaudhuryr_proj2_output_8 frames.txt", "a");
        printf("\n***********************User chose frame size of 8 pages***********************\n");
        fprintf(output_file,"\n***********************User chose frame size of 8 pages***********************\n");
    }
    else if (choice2/4==1 || choice2==1){
        FRAME_SIZE=4;
        output_file  = fopen ("chaudhuryr_proj2_output_4 frames.txt", "a");
        printf("\n***********************User chose frame size of 4 pages***********************\n");
        fprintf(output_file,"\n***********************User chose frame size of 4 pages***********************\n");
    }
    else{
        //if the user gives wrong input then choosing the default frame size as 4
        printf ("\n***********************Invalid choice of page frame size provided, running with default FRAME_SIZE=4***********************\n\n");
        FRAME_SIZE=4;
        output_file  = fopen ("chaudhuryr_proj2_output_4 frames.txt", "a");
        fprintf (output_file,"\n***********************Invalid choice of page frame size provided, running with default FRAME_SIZE=4***********************\n\n");
    }
    switch(choice) {//running the page replacement implementation functions based on user choices
    case 1:
        //Running FIFO
        run_and_print_FIFO(input_file,output_file,FRAME_SIZE);
        break;
    case 2:
        //Running LRU
        run_and_print_LRU(input_file,output_file,FRAME_SIZE);
        break;
    case 3:
        //Running second chance
        run_and_print_second_chance(input_file,output_file,FRAME_SIZE);
        break;
    default:
        //If the user gives a wrong choice of page replacement implementation
        printf("\nInvalid choice");
        printf("\nExpected either 1, 2, or 3, please re-run the program \n");


        fprintf(output_file,"\nInvalid choice");
        fprintf(output_file,"\nExpected either 1, 2, or 3, please re-run the program \n");
        exit(EXIT_FAILURE);
    printf("\n Program ended \n");


    fprintf(output_file,"\n Program ended \n");

    //closing the input file
    fclose(input_file);
}
}