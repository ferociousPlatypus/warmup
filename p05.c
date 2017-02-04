#include <stdio.h>  // fread(), fopen()
#include <stdlib.h> // exit()
#include <fcntl.h>  // open(), read()

#include <sys/types.h>
#include <sys/uio.h>  // one of these headers are bound to hold read() and open()
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

  int fd = open(argv[2],O_RDONLY);
  if(fd < 0){
    perror("File not opened");
    exit(EXIT_FAILURE);
  }
  char buffer;

  int i, j, offset, end;
  // check for each substring submitted
  for(i = 3; i < arcg; i++){
    end = 0;
    for(offset = 0; !end; offset++){
      // rewind file to beginging with offset
      int ret = lseek(fd,offset, SEEK_SET);
      if(ret < 0){
        perror("Exit Failure");
        exit(EXIT_FAILURE);
      }

      // search for substring
      for(j = 0; argv[i][j] != 0; j++){

        int gotten = read(fd, &buffer, 1);
        // check if file is at end
        if(gotten == 0){
          end = 1;
          break;
        }

        if(gotten < 0){ // error checking
          perror(argv[0]);
          exit(EXIT_FAILURE);
        }

        // logic to see if substring is found
        int bufferLetter = toLowerCase(buffer);
        int subStringLetter = toLowerCase(argv[i][j]);
        if(bufferLetter != subStringLetter){  // substring not found
          break;
        }
        // if at end of substring, increment counter
        else if(argv[i][j+1] == 0){
          count[i-3] += 1;
        }
      }
    }
  }

  // close and return
  close(fd);
  return count;
}


int main(int arcg, char **argv){

  int* count;
  int i;
  //if flag is enabled
  if(argv[1][0] == '-'){

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
