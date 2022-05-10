// Name: Rohan Chaudhury
// CSCE 611 600: OPERATING SYSTEMS Exam 2 Q18
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
#include <sys/stat.h>

//Defining macros

#define TRUE 1
#define FALSE 0



//Function to print out the file/directory properties

void print_stats(struct stat st){

  struct tm t1;
  struct tm t2;

  if (S_ISDIR(st.st_mode)) {
      printf("\nProvided path is a directory, the directory properties are as follows:\n");
    }
    else {
        printf("\nProvided path is a file, the file properties are as follows:\n");
    } 
  printf("\n");
  printf("1. The file/directory size is: %ld", st.st_size);
  printf("\n");
  printf("2. The number of blocks allocated is: %ld", st.st_blocks);
  printf("\n");
  printf("3. The reference (link) count is: %u", (unsigned int)st.st_nlink);

  printf("\n");
  printf("4. The file/directory user ID is: %d \n",st.st_uid);
  printf("\n");
  printf("5. The preferred block size for I/O file system of the file/directory is: %ld \n",st.st_blksize);
  printf("\n");
  printf("6. The file/directory group ID is: %d \n",st.st_gid);
  printf("\n");
  printf("7. The total number of blocks in multiples of 512 bytes is: %ld \n",st.st_blocks);

  printf("\n");
  printf("Note: 'r' denotes read permission, 'w' denotes write permission, 'x' denotes execute permission, '-' denotes that the particular permission is not present");
  printf("\n");
  printf("8. The File/directory Permissions for User: ");
  if (st.st_mode & S_IRUSR){
    printf("r");
  }
  else{
    printf("-");
  }
    if (st.st_mode & S_IWUSR){
    printf("w");
  }
  else{
    printf("-");
  }
    if (st.st_mode & S_IXUSR){
    printf("x");
  }
  else{
    printf("-");
  }
  printf("\n");
  printf("9. The File/directory Permissions for Group: ");
  if (st.st_mode & S_IRGRP){
    printf("r");
  }
  else{
    printf("-");
  }
    if (st.st_mode & S_IWGRP){
    printf("w");
  }
  else{
    printf("-");
  }
    if (st.st_mode & S_IXGRP){
    printf("x");
  }
  else{
    printf("-");
  }

  printf("\n");
  printf("10. The File/directory Permissions for Others: ");
    if (st.st_mode & S_IROTH){
    printf("r");
  }
  else{
    printf("-");
  }
    if (st.st_mode & S_IWOTH){
    printf("w");
  }
  else{
    printf("-");
  }
    if (st.st_mode & S_IXOTH){
    printf("x");
  }
  else{
    printf("-");
  }
    // Getting the file creation time in seconds and converting it to date and time format
    t1 = *(gmtime(&st.st_ctime));
    printf("\n11. The file/directory was created on: %d/%d/%d (DD/MM/YYYY) at %d hours %d minutes %d seconds", t1.tm_mday, t1.tm_mon, t1.tm_year + 1900, t1.tm_hour, t1.tm_min, t1.tm_sec);

    //  Getting the file modification time in seconds and converting it to date and time format
    t2 = *(gmtime(&st.st_mtime));
    printf("\n12. The file/directory was modified on: %d/%d/%d (DD/MM/YYYY) at %d hours %d minutes %d seconds", t2.tm_mday, t2.tm_mon, t2.tm_year + 1900, t2.tm_hour, t2.tm_min, t2.tm_sec);
  printf("\n");
  printf("\n");
  printf("Answer to the second part of this question: \n'A Link count shows how many directory entries link to the file/directory. A file's link count is displayed in the second column of output from the ls -l command. This number represents the total number of links that have been created to point to the data. The link count of a directory increases whenever a sub-directory is created. When the hard link file is moved or deleted, the link count of the original file gets reduced.'");
  printf("\nReference: [1] https://frameboxxindore.com/windows/what-is-link-count-in-linux.html\n[2] https://www.theunixschool.com/2012/10/link-count-file-vs-directory.html'\n");
  printf("\n");
}

//***************THE MAIN FUNCTION*********************//



int main()
{   


  //getting the relative path of the file/directory as input from the user

  char file_path[1000];
  printf("Please enter the file/directory path relative to the present working directory:");
  scanf("%s", file_path);

  int stat_out;

  //structure to store the stats of the file/directory 
  struct stat st;

  // stat() will return 0 on successful execution, otherwise it will return -1 if it is not able to get file/directory properties
  stat_out=stat(file_path, &st);
    if ( stat_out == 0)
    {
      //Calling a function which prints the file/directory properties
        print_stats(st);
    }
    else
    {
        printf("\nNot able to access file/directory properties, please make sure whether '%s' exists\n", file_path);
    }



 
 return 0;
}