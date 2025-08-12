#include "log.h"
#include "main.h"

#define PATH_SIZE 1024
#define MAX_LOG_SIZE 15

int count=0;
char store[MAX_LOG_SIZE][PATH_SIZE];

void add_to_array(char *input){
    if(strlen(input)==0 || strcmp(input," ")==0){
        return;
    }
    if(count>0 && strcmp(input,store[count-1])==0){
        return;
    }
    if(count==MAX_LOG_SIZE){
        for(int i=0;i<MAX_LOG_SIZE-1;i++){
            strcpy(store[i],store[i+1]);
        }
        strcpy(store[MAX_LOG_SIZE-1],input);
    }
    else{
        strcpy(store[count],input);
        count++;
    }
    
}

void add_to_file(){
    FILE *file=fopen("log.txt","w");
    if(file==NULL){
        perror("can't open file");
        exit(1);
    }
    for(int i=0;i<count;i++){
        fprintf(file, "%s\n",store[i]);
    }
    fflush(file);
    fclose(file);
}

void load(){
    char buffer[PATH_SIZE];
    int line_count=0;
    FILE *file=fopen("log.txt","r"); 
    if(file==NULL){
        perror("error opening file\n");
        return;
    }
    while(fgets(buffer,sizeof(buffer),file)!=NULL){     // reads a line from file into buffer
        buffer[strcspn(buffer,"\n")]=0;
        //If '\n' is found in buffer, this line replaces it with the null terminator,if not found returns length of string 
        if(line_count<MAX_LOG_SIZE){
            strcpy(store[line_count],buffer);
            line_count++;
        }
        else{
            break;
        }
    }
    count=line_count;
    fclose(file);
}

void log_purge() {
    for(int i=0;i<count;i++){
        store[i][0]='\0';
    }
    count=0;
    FILE*file=fopen("log.txt","w");
    if(file==NULL){
        perror("error opening file\n");
        return;
    }
    fclose(file);
}

void print(){
    for(int i=0;i<count;i++){
        printf("%s\n",store[i]);
    }
}

void log_execute(int index) {
    char command[PATH_SIZE];
    strcpy(command,store[count-index]);
    check(command);
}
