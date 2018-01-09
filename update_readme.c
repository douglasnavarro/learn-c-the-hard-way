/*
This program reads the directories list, detects the latest exercise
on the root directory and updates readme.md file with an estimate
progress considering the total amount of exercises on the course
*/

#define TOTAL_EXERCISES 30
#include <stdio.h>

int main(int argc, char *argv[])
{
    char * buffer = 0;
    long length;
    FILE * f = fopen ("./README.md", "rb");
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    buffer = malloc(length);
    if(buffer)
    {
        fread(buffer, 1, length, f);
    }
    fclose(f);
    printf("%s", buffer);
}