#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


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

}
