
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {

        int fh;
        char buffer[65];
        int gotten;

        fh = open("abc.txt",O_RDONLY);
        printf ("File handle %d\n",fh);
        while ((gotten = read(fh,buffer,64))) {
                buffer[gotten] = '\0';
                printf("******%s",buffer);
                }
        }
