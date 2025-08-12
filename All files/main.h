#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <pwd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <grp.h>
#include <time.h>

extern char *home_dir;
extern char *cwd;
extern struct timespec start_time,end_time;
extern double time_taken;

void check(char*);
void check_background_processes(void);
void handle_alarm(int);
double get_time_diff(struct timespec,struct timespec);

#endif
