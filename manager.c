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

    // Open seuqnce.txt file
    FILE* file;
    char ch;

    file = fopen("sequence.txt", "r");

    if (NULL == file)
    {
        printf("sequence.txt couldn't be opened.");
    }

    do 
    {
        ch = fgetc(file);
        printf("%c", ch);
    }
    while (ch != EOF);

    fclose(file);
    return 0;
}
