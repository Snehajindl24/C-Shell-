#ifndef HOP_H
#define HOP_H

#include <stdio.h>   
#include <stdlib.h> 
#include <unistd.h>  
#include <string.h>  
#include <errno.h> 
#include <limits.h>
#include<pwd.h>

extern char *home_dir;
extern char *cwd;
extern char *prev_dir;

void hop(char*);

#endif
