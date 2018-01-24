/*
This program reads the directories list, detects the latest exercise
on the root directory and updates readme.md file with an estimate
progress considering the total amount of exercises on the course

I know I could have written this using another language, but it
wouldnt feel right :/
*/

#define TOTAL_EXERCISES 52
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

char *str_replace(char *org, char *rep, char *with);
int latest_exs();
int create_file();

int main(int argc, char *argv[])
{
    char str_progress[3];
    int latest = latest_exs();
    printf("latest is %d\n", latest);
    float float_progress = (latest / (float) TOTAL_EXERCISES) * 100;
    printf("float_progress is %.0f\n", float_progress);
    sprintf(str_progress, "%.0f", float_progress);
    return(create_file(str_progress));
}

// You must free the result if result is non-NULL.
char *str_replace(char *orig, char *rep, char *with) 
{
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    // sanity checks and initialization
    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);

    // count the number of replacements needed
    ins = orig;
    for (count = 0; tmp = strstr(ins, rep); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}

int latest_exs()
{
    DIR *dir;
    struct dirent *ent;
    dir = opendir("./exercises");
    int number = 0;
    int result = 0;

    if(dir != NULL)
    {
        ent = readdir(dir);
        while( ent != NULL )
        {
            char *name = ent -> d_name;
            sscanf(name, "ex%d", &number);
            if(number > result)
            {
                result = number;
            }
            ent = readdir(dir);
        }
        free(dir);
        free(ent);
        return result;
    }
    else
    {
        printf("Opendir failed! Code %d\n", EXIT_FAILURE);
        return EXIT_FAILURE;
    }
}

int create_file(char* progress)
{
    char * buffer_template;
    char * buffer_replaced;
    long length;

    FILE * f = fopen ("./README_template.md", "rb");
    if (f==NULL)
    {
        return 1;
    }
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    buffer_template = malloc(length + sizeof(char));
    if(buffer_template)
    {
        fread(buffer_template, 1, length, f);
    }
    fclose(f);
    buffer_replaced = str_replace(buffer_template, "#progress#", progress);
    FILE * g = fopen("./README.md", "wb");
    if( g == NULL)
    {
        free(buffer_template);
        free(buffer_replaced);
        return 1;
    }
    fputs(buffer_replaced, g);
    fclose(g);
    free(buffer_replaced);
    free(buffer_template);
    return 0;
}