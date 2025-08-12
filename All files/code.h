#ifndef CODE_H
#define CODE_H

#include <stdio.h>   
#include <stdlib.h> 
#include <unistd.h>  
#include <string.h>  
#include <errno.h> 
#include <limits.h>
#include<pwd.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>

#include "colors.h"
#include "code.h"
#include "hop.h"
#include "reveal.h"
#include "log.h"
#include "main.h"
#include "proclore.h"

extern char *home_dir;
extern char *cwd;
extern char *temp;
extern int flag;

void print_prompt(void);

#endif
