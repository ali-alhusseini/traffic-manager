#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>


int main(int argc, char *argv[])
{
    // Check for command line input
    if (argc == 2)
    {
         double p = argv[1];
    }
    else {
        printf("Wrong number of command line arguments.\n");
    }

    // Open sequence.txt file
    FILE* filePointer;
    char ch;

    filePointer = fopen("sequence.txt", "r");

    if (filePointer == NULL)
    {
        printf("%s does not exist.\n", "sequence.txt");
    }

    while((ch = fgetc(filePointer)) != EOF){
        printf("%c", ch);
    }

    if(!fclose(fp)){
        printf("\n%s: closed.\n", "sequence.txt");
    }
    return 0;
}
