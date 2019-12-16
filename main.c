#include <stdio.h>
#include <stdlib.h>
#include "execution.h"
void main_loop();
int main()
{
    main_loop();
}
void main_loop()
{
    char *line;
    char **args;
    int status = 1;
    while(status)
    {
        printf(">");
        line = read_line();
        args = split_line(line);
        status = execute(args);
        free(line);
        free(args);
    }
}
