#include "execution.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#define BUFEER_SIZE 1024;

int go_to_folder(char **args);
int remove_folder(char **args);
int current_location(char **args);
int create_folder(char **args);
int help_shell(char **args);
int exit_shell(char **args);
int rename_folder(char **args);
int get_time(char **args);
///
char *builtin_str[] =
{
    "cdd",
    "rm",
    "location",
    "mk_dir",
    "rename",
    "time_l",
    "help",
    "exit"
};
int (*builtin_f[])(char **) =
{
    &go_to_folder,
    &remove_folder,
    &current_location,
    &create_folder,
    &rename_folder,
    &get_time,
    &help_shell,
    &exit_shell
};
///
int calculate_amount_of_commands()
{
    return sizeof(builtin_str) / sizeof(char *);
}
char *read_line()
{
    int buf_size = BUFEER_SIZE;
    int c;
    char *line = malloc(sizeof(char) * buf_size);
    int pos = 0;
    while(1)
    {
        c = getchar();
        if(c == EOF)
        {
            exit(EXIT_SUCCESS);
        }
        if(c == '\n')
        {
            line[pos] = '\0';
            return line;
        }
        else
        {
            line[pos] = c;
            pos++;
        }
        if(pos>=buf_size)
        {
            buf_size +=BUFEER_SIZE;
            line = realloc(line,buf_size);
        }
    }
}
char **split_line(char *line)
{
    int buf_size = BUFEER_SIZE;
    char **args = malloc(sizeof(char *) * buf_size);
    int pos = 0;
    char *accum = strtok(line, " \n");
    while(accum!=NULL)
    {
        args[pos] = accum;
        pos++;
        if(pos>=buf_size)
        {
            buf_size += BUFEER_SIZE;
            args = realloc(args, buf_size);
        }
        accum = strtok(NULL, " \n");
    }
    args[pos] = NULL;
    return args;
}
int execute(char **args)
{
    if(args[0] == NULL)
    {
        perror("Wrong command: ");
        return 1;
    }
    int a = 0;
    for(int i=0; i< calculate_amount_of_commands(); i++)
    {
        if(strcmp(args[0], builtin_str[i]) == 0)
        {
            a = 1;
            return (*builtin_f[i])(args);
        }
    }
    if(a==0)
    {
        perror("Wrong command: ");
        return 1;
    }
    return 1;
}
///
int go_to_folder(char **args)
{
    int check;
    if(args[1] == NULL)
    {
        perror("Wrong command: ");
        return 1;
    }
    else
    {
        check = chdir(args[1]);
        if(check != 0)
        {
            perror("Wrong command: ");
            return 1;
        }
        else
        {
            return 1;
        }
    }
    return 0;
}
int remove_folder(char **args)
{
    if(args[1] == NULL)
    {
        perror("Wrong command: ");
    }
    else
    {
        rmdir(args[1]);
        return 1;
    }
    return 0;
}
int current_location(char **args)
{
    char dir[100];
    getcwd(dir, 100);
    printf("Location: %s\n", dir);
    return 1;
}
int create_folder(char **args)
{
    if(args[1] == NULL)
    {
        perror("Wrong command: ");
        return 1;
    }
    else
    {
        int check;
        check = mkdir(args[1],1);
        if(!check)
        {
            return 1;
        }
        else
        {
            perror("Wrong command ");
            return 1;
        }
    }
    return 1;
}
int rename_folder(char **args)
{
    if(args[1] == NULL || args[2] == NULL )
    {
        perror("Worng command: ");
        return 1;
    }
    int check;
    check = rename(args[1], args[2]);
    if(!check)
    {
        return 1;
    }
    else
    {
        perror("Wrong command: ");
        return 1;
    }
    return 1;
}
int help_shell(char **args)
{
    printf("Shell functions: \n");
    printf("1)Open folder -> cdd \n");
    printf("2)REMOVE FOLDER -> rm \n");
    printf("3)Current Location -> location \n");
    printf("4)Create folder -> mk_dir \n");
    printf("5)Rename folder -> rename \n");
    printf("6)Time -> time_l \n");
    printf("7)HELP -> help \n");
    printf("8)EXIT -> exit \n");
    return 1;
}
int exit_shell(char **args)
{
    return 0;
}
int get_time(char **args)
{
    time_t rawtime;
    struct tm *timeinfo;
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    printf("Time: %s", asctime(timeinfo));
    return 1;
}

