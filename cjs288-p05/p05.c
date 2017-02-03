#include <stdio.h>  // fread(), fopen()
#include <stdlib.h> // exit()
#include <fcntl.h>  // open(), read()

#include <sys/types.h>
#include <sys/uio.h>  // one of these libs are bound to hold read() and open()
#include <unistd.h>   // for mac os
#include <fcntl.h>


//convert uppercase to lowercase
int toLowerCase(int letter){
  //if uppercase convert to lower
  if(letter >= 'A' && letter <= 'Z'){
    letter +=  32;
  }
  return letter;
}

// search for substring.  open file by using fopen and fread
int* level1(int arcg, char **argv, int* count){
  char* buffer;

  //open file
  FILE* fp = fopen(argv[1],"r");
  if(fp == NULL){
    perror(argv[0]);
    exit(EXIT_FAILURE);
  }

  //find size of file
  fseek(fp, 0, SEEK_END);
  int size = ftell(fp);
  fseek(fp,0,SEEK_SET); // could also rewind
  if(size == 0){
    perror(argv[0]);
    exit(EXIT_FAILURE);
  }

  //read in file and store
  buffer = (char*) calloc(size, sizeof(char));
  int n = fread(buffer,1,size-1,fp);
  if(buffer == NULL){
    perror("Error MEMORY not allocated");
  }

  //check file for each substring if it exists
  //inital variables
  int i,z,j;
  for(z = 0; buffer[z] != 0; z++){
    //increment through file
    for(i = 2; i < arcg; i++){
      //increment though subString
      for(j = 0; argv[i][j] != 0; j++){
        //convert to lower case
        int bufferLetter = toLowerCase(buffer[z+j]);
        int subStringLetter = toLowerCase(argv[i][j]);

        //if subString not matched
        if(bufferLetter != subStringLetter){
          break;
        }
        //when reached end of substring increment answer
        else if(argv[i][j+1] == 0){
          count[i-2] += 1;
          break;
        }
      }
    }
  }
  fclose(fp);
  free(buffer);
  return count;
}

int* level2(int arcg, char **argv, int* count){
  int fd = open("bar",O_RDONLY);
  if(fd < 0){
    perror("File not opened");
    exit(EXIT_FAILURE);
  }
  char* buffer;

  printf("Test\n");

  int i, j, offset, end;
  for(i = 3; i < arcg; i++){
    end = 0;
    for(offset = 0; !end; offset++){
      // int ret = lseek(fd,offset, SEEK_SET);
      // if(ret < 0){
      //   exit(EXIT_FAILURE);
      // }

      printf("Test2\n");

      for(j = 0; argv[i][j] != 0; j++){
        int gotten = read(fd, buffer, sizeof(char));
        perror("reading");
        printf("%s\n",buffer);
        if(buffer == NULL){
          end = 1;
          break;
        }
        if(gotten < 0){
          printf("Uh Oh\n");
          break;
        }
        printf("Test3\n");

        printf("%s\n",buffer);

        int bufferLetter = toLowerCase(*buffer);
        int subStringLetter = toLowerCase(argv[i][j]);
        if(bufferLetter != subStringLetter){
          break;
          }
        else if(argv[i][j+1] == 0){
          count[i-3] += 1;
        }
      }
    }
  }
  return count;
}


int main(int arcg, char **argv){

  int* count;
  int i;
  //if flag is enabled
  if(argv[1][0] == '-'){

    printf("Entered Flag\n");

    // alloctate memory for array to store values of appearences for substring
    count = (int*)calloc(arcg-3, sizeof(int));
    count = level2(arcg, argv, count);
    for(i = 0; i < arcg-3; i++){
      printf("%d\n",count[i]);
    }
  }

  else{

    // alloctate memory for array to store values of appearences for substring
    count = (int*)calloc(arcg-2, sizeof(int));
    // run search for substring
    count = level1(arcg, argv, count);
    for(i = 0; i < arcg-2; i++){
      printf("%d\n",count[i]);
    }
  }

  free(count);
  exit(EXIT_SUCCESS);
}
