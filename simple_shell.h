#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

void handle_sigint(int sig);
char *_getenv(char *string, char **envp);

int find_command_path(char *cmd, char **envp, char *cmd_path);
void execute_command(char **args, char **envp, char *argv0, int count, int *last_status);

char *read_line(void);
void token_command(char *line, char **args);

int built_in_checks(char **args, char **envp, char *line, int *last_status);

#endif
