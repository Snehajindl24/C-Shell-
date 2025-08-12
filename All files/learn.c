#include "learn.h"

#define INITIAL_PATH_SIZE 1024

char *home_directory;

void print_prompt() {   
    char *cwd = NULL;
    size_t size = INITIAL_PATH_SIZE;
    char hostname[size];
    if(gethostname(hostname,sizeof(hostname))!=0){
        perror("gethostname failed");
        exit(1);
    }
    cwd=malloc(size);
    if(cwd==NULL) {
        perror("error in malloc");
        exit(1);
    }
    while(getcwd(cwd,size)==NULL) {
        if(errno==ERANGE){                 // Buffer is small; need to increase size
            size*=2;
            cwd=realloc(cwd,size);
            if(cwd==NULL){
                perror("error in realloc");
                exit(1);
            }
        }
        else{
            perror("error in getcwd");
            free(cwd);
            exit(1);
        }
    }
    if(strncmp(cwd,home_directory,strlen(home_directory))==0) {
        printf("<%s@%s:~%s> ",getenv("USER"),hostname,cwd+strlen(home_directory));
        //This expression adjusts the pointer cwd to point to the character immediately following the home_directory portion of cwd.
        //For example, if cwd is /home/user/projects and home_directory is /home/user, then cwd + strlen(home_directory) points to /projects.
    } else {
        // I will do later
    }
    free(cwd);
}


int main() {
    char *input=NULL;
    size_t input_size=INITIAL_PATH_SIZE;
    input=malloc(input_size);
    if(input==NULL) {
        perror("error in malloc");
        exit(1);
    }
    home_directory=malloc(INITIAL_PATH_SIZE);
    if(home_directory==NULL){
        perror("error in malloc");
        exit(1);
    }
    if(getcwd(home_directory,INITIAL_PATH_SIZE)==NULL){
        // cwd is stored in home directory as refering to function,i want cwd to point to nothing bcz i just want tilda(~)
        perror("error in getcwd");
        exit(1);
    }

    while (1) {
        print_prompt();
        if(getline(&input,&input_size,stdin)==-1){
            //If input is NULL, getline will allocate a buffer dynamically using malloc. If it already points to an allocated buffer, getline will resize it as needed using realloc.
            perror("error in getline");
            free(home_directory);
            free(input);
            exit(1);
        }
        input[strcspn(input,"\n")]='\0';
        //This replaces the newline character with a null terminator ('\0'), effectively truncating the string at that point
    }
    free(home_directory);
    free(input);
    return 0;
}
