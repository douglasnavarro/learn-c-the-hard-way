#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;
    while(i < argc)
    {
        printf("arg %d: %s\n", i, argv[i]);
        i++;
    }

    char *states[] = 
    {
        "California", "Washington",
        "Oregon", "Texas"
    };

    int num_states = 4;
    i = 0;
    while( i < num_states)
    {
        printf("state %d: %s\n", i , states[i]);
        i++;
    }

    i = 1;
    while(i < argc)
    {
        states[i] = argv[i];
        i++;
    }

    i = 0;
    while( i < num_states)
    {
        printf("state copied from argv %d: %s\n", i , states[i]);
        i++;
    }
    return 0;
}