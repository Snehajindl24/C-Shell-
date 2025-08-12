#ifndef PROCLORE_H
#define PROCLORE_H

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
#include <fcntl.h>

extern char *home_dir;
extern char *cwd;

void proclore(char *);

#endif
