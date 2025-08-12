#ifndef SEEK_H
#define SEEK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

extern char *home_dir;
extern char *cwd;

int is_dir(const char*);
void print_file(const  char*);
void search_dir(char*,char*,int,int,int*,int*,char*);
void seek(char *);

#endif
