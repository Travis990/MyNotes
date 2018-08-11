#include <stdio.h>

int showi(void)
{
    int i = 0;

    for (i = 0; i < 100; i++)
    {
        printf("i = %d\n", i); 
    }

    return 0;
}

int main(int argc, char **argv)
{
    
    int i = 0;

    for (i = 0; i < argc; i++)
    {
        printf("argv[%d]: %s\n", i, argv[i]); 
    }


    printf("=========================\n");

    showi();

    return 0;
}
