// ONLY ONE THING LEFT FROM SPECIFICATION 6

#include "main.h"
#include "code.h"
#include "hop.h"
#include "reveal.h"
#include "log.h"
#include "proclore.h"
#include "seek.h"

#define PATH_SIZE 1024

char *temp;
int flag=0;

void handle_alarm(int sig) {
    check_background_processes();
    alarm(5); // Re-schedule the alarm for the next 5 seconds
}

void check_background_processes()
{
    int status;
    pid_t pid;
    // Check if any background process has terminated
    while((pid=waitpid(-1,&status,WNOHANG))>0)
    {
        if(WIFEXITED(status)){
            printf("Process with pid %d exited normally\n",pid);
        }
        else if(WIFSIGNALED(status)){
            printf("Process with pid %d terminated by signal %d\n", pid, WTERMSIG(status));
        }
    }
}

// Function to calculate the time difference in seconds
double get_time_diff(struct timespec start, struct timespec end) {
    double seconds = end.tv_sec - start.tv_sec;   // Difference in seconds
    double nanoseconds = end.tv_nsec - start.tv_nsec;  // Difference in nanoseconds
    return seconds + nanoseconds * 1e-9;  // Combine to get the total difference in seconds
}

void check(char *input){
    time_taken=0;
    char *token;
    char *command;
    command=malloc(PATH_SIZE);
    char *trimmed_command;
    trimmed_command=malloc(PATH_SIZE);
    token=malloc(PATH_SIZE);
    char *token2;
    token2=malloc(PATH_SIZE);
    if(token==NULL || command==NULL || trimmed_command==NULL || token2==NULL){
        perror("malloc failed");
        exit(1);
    }
    char input_copy[PATH_SIZE];
    strcpy(input_copy,input);
    int check_log=0;
    token2=strtok(input_copy," \t");
    while(token2!=NULL){
        if(strcmp(token2,"log")==0){
            check_log=1;
            break;
        }
        token2=strtok(NULL," \t");    
    }
    if(check_log==0){
        add_to_array(input);
    }
    char* save;
    command=strtok_r(input,";",&save);        // input won't be changed
    while(command!=NULL){
        strcpy(trimmed_command,command);
        while(*trimmed_command==' '|| *trimmed_command=='\t'){
            trimmed_command++;
        }
        while(strchr(trimmed_command,'&')!=NULL){
            // Separate the background command from the rest
            char *background=strchr(trimmed_command,'&');
            *background='\0'; 
            // Fork a new process to run the command in the background
            pid_t pid=fork();
            if(pid==0){
                char *args[]={"/bin/sh","-c",trimmed_command,NULL};
                execvp(args[0],args);
                perror("execvp");
                exit(1);
            }
            else if(pid>0){
                printf("[%d] %d\n",pid,pid);
            }
            else{
                perror("fork");
            }
            trimmed_command=background+1;
        }
        if(*trimmed_command!='\0'){
            flag=0;
            char command_copy[PATH_SIZE];
            strncpy(command_copy,trimmed_command,PATH_SIZE);
            token=strtok(command_copy," \t");
            if(token!=NULL) {
                if(strcmp(token,"hop")==0) {
                    hop(trimmed_command);  
                } 
                else if(strcmp(token,"reveal")==0) {
                    reveal(trimmed_command); 
                }
                else if(strcmp(token,"proclore")==0){
                    proclore(trimmed_command);
                }
                else if(strcmp(token,"seek")==0){
                    seek(trimmed_command);
                }
                else if(strcmp(token,"log")==0){
                    token=strtok(NULL," \t");
                    if(token==NULL){
                        print();
                    }
                    else{
                        if(strcmp(token,"purge")==0){
                            log_purge();
                        }
                        if(strcmp(token,"execute")==0){
                            token=strtok(NULL," \t");
                            int index=atoi(token);
                            if(index!=0){
                                log_execute(index);
                            }
                            else{
                                printf("give some index\n");
                            }
                        }
                    }
                }
                else{
                    temp=trimmed_command;
                    flag=1;
                    // Handle system commands using execvp
                    clock_gettime(CLOCK_MONOTONIC,&start_time);
                    pid_t pid=fork();
                    if(pid==0){ 
                        // Parse the command and its arguments
                        char *args[PATH_SIZE];
                        int i=0;
                        char *arg=strtok(trimmed_command," \t");
                        while(arg!=NULL){
                            args[i++]=arg;
                            arg=strtok(NULL," \t");
                        }
                        args[i]=NULL;            
                        execvp(args[0],args);   
                        perror("execvp");   
                        exit(1);
                    } 
                    else if(pid>0){  
                        wait(NULL);
                    } 
                    else{
                        perror("fork");
                    }
                    clock_gettime(CLOCK_MONOTONIC, &end_time);
                }
            }
        }
        command=strtok_r(NULL,";",&save);
    }
}