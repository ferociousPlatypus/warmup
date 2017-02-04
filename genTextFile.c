#include <stdio.h>
#include <stdlib.h>

int main(){
  int i;
  for(i = 0; i < 10000000 / 26; i++){
    printf("abcdefghijklmnopqrstuvwxyz");
  }
  
  return 0;
}
