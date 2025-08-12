#include "colors.h"
#include "code.h"
#include "hop.h"
#include "reveal.h"
#include "log.h"
#include "main.h"
#include "proclore.h"
#include "seek.h"

#define PATH_SIZE 1024
#define MAX_LOG_SIZE 15

char *home_dir;
char *cwd;
char *prev_dir;
char *dir_path;

double time_taken;

struct timespec start_time,end_time;

void print_prompt(){
    char hostname[PATH_SIZE];
    if(gethostname(hostname,sizeof(hostname))!=0){
        perror("gethostname failed");
        exit(1);
    }
    if(flag==1){
        time_taken = get_time_diff(start_time, end_time);
    }
    else{
        time_taken=0;
    }
    //printf("%f\n",time_taken);
    if(strcmp(cwd,home_dir)==0){
        if(time_taken>2){
            printf(PROMPT_COLOR "<%s@" HOSTNAME_COLOR "%s" PROMPT_COLOR ":~ %s : %ds>" RESET" ", getenv("USER"), hostname,temp,(int)time_taken);
        }
        else{
            printf(PROMPT_COLOR "<%s@" HOSTNAME_COLOR "%s" PROMPT_COLOR ":~>" RESET " ", getenv("USER"), hostname);
        }
    }
    else{
        if(time_taken>2){
            printf(PROMPT_COLOR "<%s@" HOSTNAME_COLOR "%s" PROMPT_COLOR ":~ %s %s : %ds>" RESET " ",getenv("USER"), hostname, cwd+strlen(home_dir),temp,(int)time_taken);
            flag=1;
        }
        else{
            printf(PROMPT_COLOR "<%s@" HOSTNAME_COLOR "%s" PROMPT_COLOR ":~" PATH_COLOR "%s" RESET "> ", getenv("USER"), hostname, cwd + strlen(home_dir));
            //This expression adjusts the pointer cwd to point to the character immediately following the home_directory portion of cwd.
            //For example, if cwd is /home/user/projects and home_directory is /home/user, then cwd + strlen(home_directory) points to /projects.
        }
    }
}

int main(){
    char input[PATH_SIZE];
    home_dir=malloc(PATH_SIZE);
    cwd=malloc(PATH_SIZE);
    prev_dir=malloc(PATH_SIZE);
    dir_path=malloc(PATH_SIZE);
    if(cwd==NULL||home_dir==NULL||prev_dir==NULL||dir_path==NULL){
        perror("malloc failed");
        exit(1);
    }
    if(getcwd(home_dir,PATH_SIZE)==NULL){
        perror("getcwd failed");
        free(home_dir);
        exit(1);
    }
    strcpy(cwd,home_dir);
    strcpy(dir_path,home_dir);
    strcpy(prev_dir,home_dir);

    signal(SIGALRM,handle_alarm);   // Set up signal handler for periodic checks
    alarm(5);                       // Start the first alarm
    load();
    while(1){
        print_prompt();
        if(fgets(input,sizeof(input),stdin)==NULL){
            perror("fgets failed");
            exit(1);
        }
        input[strcspn(input,"\n")]='\0';
        if(strcmp(input,"exit")==0){
            break;
        }
        check(input);
    }
    add_to_file();
    return 0;
}