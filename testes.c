#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    char chamada[100];
    int status;

    for (int i = 0; i < 12; i++)
    {
        system("./serial.x 25000 25000");
        wait(&status);
    }
    
    for (int i = 2; i <= 16; i+=2)
    {
        sprintf(chamada, "./parallel.x 25000 25000 %d", i);
        for (int j = 0; j < 12; j++)
        {
            system(chamada);
            wait(&status);
        }
    }

    return 0;
}