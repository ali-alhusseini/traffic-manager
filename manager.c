#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


int main(int argc, char *argv[])
{
    if (argc == 2)
    {
         double p = argv[1];
    }
    else {
        printf("Wrong number of command line arguments.\n");
    }

}
