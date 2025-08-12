#ifndef LOG_H
#define LOG_H

#include <stdio.h>   
#include <stdlib.h> 
#include <unistd.h>  
#include <string.h>  
#include <errno.h> 
#include <limits.h>
#include <pwd.h>
#include <fcntl.h>

extern char *home_dir;
extern char *cwd;
extern char store[][1024];
extern int count;

void add_to_array(char*);
void log_purge();
void print();
void log_execute(int);
void add_to_file();
void load();

#endif
