char *read_line();
char **split_line(char *line);
int execute(char **args);
int go_to_folder(char **args);
int remove_folder(char **args);
int current_location(char **args);
int create_folder(char **args);
int help_shell(char **args);
int exit_shell(char **args);
int rename_folder(char **args);
int get_time(char **args);