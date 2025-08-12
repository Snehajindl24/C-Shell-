#ifndef REVEAL_H
#define REVEAL_H

#include <stdio.h>   
#include <stdlib.h> 
#include <unistd.h>  
#include <string.h>  
#include <errno.h> 
#include <limits.h>
#include<pwd.h>
#include<dirent.h>
#include <sys/stat.h>
#include <grp.h>
#include <time.h>
#include<dirent.h>
#include<ctype.h>

extern char *home_dir;
extern char *cwd;
extern char *prev_dir;
extern char *dir_path;

void reveal(char*);
void extra(struct stat,char *);
int compare(const void*,const void*);

#endif
