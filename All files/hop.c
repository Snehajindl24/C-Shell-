#include "hop.h"

#define PATH_SIZE 1024

void hop(char *input){
    char *token;
    token=malloc(PATH_SIZE);
    if(token==NULL){
        perror("malloc failed");
        exit(1);
    }
    token=strtok(input," \t");
    if(strcmp("hop",token)!=0){
        printf("wrong command");
        return;
    }
    token=strtok(NULL," \t");
    if(token==NULL){
        strcpy(prev_dir,cwd);
        getcwd(cwd,PATH_SIZE);
        printf("%s\n",cwd);
        return;
    }

    char *token2;
    token2=malloc(PATH_SIZE);
    if(token2==NULL){
        perror("malloc failed");
        exit(1);
    }
    char *token3;
    token3=malloc(PATH_SIZE);
    if(token3==NULL){
        perror("malloc failed");
        exit(1);
    }
    int k=0;
    int flag=0;
    if((token[0]=='.' || token[0]=='~' || token[0]=='-') && token[1]=='/'){
        for(int i=2;i<strlen(token);i++){
            token3[k++]=token[i];
        }
        token3[k]='\0';
        token2[0]=token[0];
        token2[1]='\0';
        strcpy(token,token2);
        flag=1;
    }
    if(token[0]=='.' && token[1]=='.' && token[3]=='/'){
        for(int i=2;i<strlen(token);i++){
            token3[k++]=token[i];
        }
        token3[k]='\0';
        token2[0]=token[0];
        token2[1]=token[1];
        token2[2]='\0';
        strcpy(token,token2);
        flag=1;
    }
    while(token!=NULL){
        if(strcmp(token,".")==0){
            strcpy(prev_dir,cwd);
            getcwd(cwd,PATH_SIZE);
            printf("%s\n",cwd);
        }
        else if(strcmp(token,"~")==0){
            strcpy(prev_dir,cwd);
            if(chdir(home_dir)!=0) {
                perror("chdir to home directory failed");
                return;
            }
            else{
                getcwd(cwd,PATH_SIZE);
                printf("%s\n",cwd);
            }
        }
        else if(strcmp(token,"..")==0){
            strcpy(prev_dir,cwd);
            char *temp_dir;
            temp_dir=malloc(PATH_SIZE);
            if(temp_dir==NULL){
                perror("malloc failed");
                exit(1);
            }
            (getcwd(temp_dir,PATH_SIZE));
            if(strcmp(temp_dir,home_dir)==0){
                printf("already at home directory");
                return;
            }
            if(chdir(token)==0){
                getcwd(cwd,PATH_SIZE);
                printf("%s\n",cwd);
            }
            else{
                printf("no such directory exits\n");
            }
        }
        else if(strcmp(token,"-")==0){
            if(chdir(prev_dir)==0) {
                char temp[PATH_SIZE];
                strcpy(temp,cwd);
                strcpy(cwd,prev_dir);
                strcpy(prev_dir,temp);
                printf("%s\n",cwd);
            }
            else{
                printf("no such directory exists\n");
            }
        }
        else{
            strcpy(prev_dir,cwd);
            if(chdir(token)==0){
                getcwd(cwd,PATH_SIZE);
                printf("%s\n",cwd);
            }
            else{
                printf("no such directory exits\n");
            }
        }
        token=strtok(NULL," \t");
    }
    if(flag==1){
        if(chdir(token3)==0){
            getcwd(cwd,PATH_SIZE);
            printf("%s\n",cwd);
        }
        else{
            printf("no such directory exits\n");
        }
    }
}
