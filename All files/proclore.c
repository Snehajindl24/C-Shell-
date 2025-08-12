#include "proclore.h"

#define PATH_SIZE 1024

void proclore(char *command) {
    char *token=strtok(command," \t");
    token=strtok(NULL," \t");
    char pid_str[10];
    if(token==NULL){
        snprintf(pid_str, sizeof(pid_str), "%d", getpid());
        token=pid_str; // Used shell PID as token
    }
    char *pid=token;
    char stat_path[PATH_SIZE],statm_path[PATH_SIZE],exe_path[PATH_SIZE],exe_resolved[PATH_SIZE];

    int vm_size;
    FILE *file;
    snprintf(stat_path, sizeof(stat_path), "/proc/%s/stat", pid);
    snprintf(statm_path, sizeof(statm_path), "/proc/%s/statm", pid);
    snprintf(exe_path, sizeof(exe_path), "/proc/%s/exe", pid);

    // Read and print process status from /proc/[pid]/stat
    file=fopen(stat_path,"r");
    if(file==NULL){
        perror("Error opening stat file");
        return;
    }

    int process_pid, pgrp;
    char comm[256],state;
    fscanf(file,"%d %s %c %*d %d",&process_pid,comm,&state,&pgrp);  // Read necessary fields
    fclose(file);
    printf("pid : %d\n",process_pid);
    printf("process Status : %c\n",state);
    printf("Process Group : %d\n",pgrp);

    // Read and print virtual memory size from /proc/[pid]/statm
    file=fopen(statm_path,"r");
    if(file==NULL){
        perror("Error opening statm file");
        return;
    }
    fscanf(file,"%d",&vm_size);
    printf("Virtual Memory : %d\n",vm_size);
    fclose(file);

    // Resolve and print executable path from /proc/[pid]/exe
    ssize_t len=readlink(exe_path,exe_resolved,sizeof(exe_resolved)-1);
    if(len!=-1){
        exe_resolved[len]='\0'; 
        printf("executable path : %s\n",exe_resolved);
    } else {
        perror("Error resolving executable path");
    }
}