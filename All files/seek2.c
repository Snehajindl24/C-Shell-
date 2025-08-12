#include "main.h"
#include "seek.h"
#include "colors.h"
#include "hop.h"

#define PATH_SIZE 1024

int is_dir(const char *path){
    struct stat path_stat;
    if(lstat(path,&path_stat)!=0){
        perror("lstat");
        exit(1);
    }
    return S_ISDIR(path_stat.st_mode);
}

void print_file(const char *file_path){
    FILE *file=fopen(file_path,"r");
    if(file==NULL){
        perror("error in opening file");
        exit(1);
    }
    char ch;
    while((ch=fgetc(file))!=EOF){
        putchar(ch);
    }
    fclose(file);
}

void search_dir(char*target_dir,char*search,int flag_d,int flag_f,int *found_dir,int *found_file,char *found_path){
    char current_dir[PATH_SIZE];
    if(strcmp(target_dir,".")==0){
        getcwd(current_dir,PATH_SIZE);
    }
    else if(strcmp(target_dir,"~")==0){
        strncpy(current_dir,home_dir,PATH_SIZE-1);
        current_dir[PATH_SIZE-1]='\0';
    }
    else if(strcmp(target_dir,"..")==0){
        if(chdir("..")==0){
            getcwd(current_dir,PATH_SIZE);
        }
    }
    else{
        strncpy(current_dir,target_dir,PATH_SIZE-1);
        current_dir[PATH_SIZE-1]='\0';
    }
    DIR *dir=opendir(current_dir);
    if(dir==NULL){
        perror("error in opening directory");
        exit(1);
    }
    struct dirent *entry;
    char path[PATH_SIZE];
    while((entry=readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0){    //hidden files
            continue;
        }
        snprintf(path,sizeof(path),"%s/%s",target_dir,entry->d_name);
        struct stat path_stat;
        if(lstat(path,&path_stat)!=0){
            perror("lstat");
            exit(1);
        }
        if(strncmp(entry->d_name,search,strlen(search))==0){
            if(S_ISDIR(path_stat.st_mode)){
                if(flag_f==0){
                    (*found_dir)++;
                    strncpy(found_path,path,PATH_SIZE-1); 
                    found_path[PATH_SIZE-1]='\0';
                    printf("%s%s%s\n",BLUE,path,RESET);

                }
            }
            else{
                if(flag_d==0){
                    (*found_file)++;
                    strncpy(found_path,path,PATH_SIZE-1);
                    found_path[PATH_SIZE-1]='\0';
                    printf("%s%s%s\n",GREEN,path,RESET);
                }
            }
        }
        // Recurse into subdirectories
        if(S_ISDIR(path_stat.st_mode)){
            search_dir(path,search,flag_d,flag_f,found_dir,found_file,found_path);
        }
    }
    closedir(dir);
}

void seek(char *input){
    int flag_d=0,flag_f=0,flag_e=0;
    char search[PATH_SIZE]="";
    char target_dir[PATH_SIZE]=".";  

    char *token=strtok(input," \t");
    if(token==NULL){
        perror("input is empty");
        exit(1);
    }
    token=strtok(NULL," \t");
    while(token!=NULL){
        //printf("%s\n",token);
        if(strcmp(token,"-d")==0){
            flag_d=1;
        }
        else if(strcmp(token,"-f")==0){
            flag_f=1;
        }
        else if(strcmp(token,"-e")==0){
            flag_e=1;
        }
        else if(strlen(search)==0){
            strcpy(search,token);
        }
        else{
            strcpy(target_dir,token);
        }
        token=strtok(NULL," \t");
    }
    //printf("%d %d %d\n",flag_d,flag_f,flag_e);
    if(flag_d==1 && flag_f==1){
        printf("Invalid flags!\n");
        return;
    }
    if(strlen(search)==0){
        perror("no file specified for search");
        exit(1);
    }
    int found_dir=0,found_file=0;
    char found_path[PATH_SIZE]="";
    search_dir(target_dir,search,flag_d,flag_f,&found_dir,&found_file,found_path);
    printf("%d %d\n",found_dir,found_file);
    if(flag_d==1 && flag_f==1){
        printf("No match found!\n");
    }
    else if(flag_e==1){
        if(flag_d==1 && flag_f==0){
            if(access(found_path,R_OK)==0 && found_dir==1) {
                char temp[PATH_SIZE];
                strcpy(temp,"hop");
                strcat(temp," ");
                strcat(temp,found_path);
                hop(temp);
            } 
            else {
                printf("Missing permissions for task!\n");
            }
        }
        else if(flag_f==1 && flag_d==0){
            if(access(found_path,R_OK)==0 && found_file==1){
                printf("%d\n",found_file);
                print_file(found_path);
            } 
            else {
                printf("Missing permissions for task!\n");
            }
        }
        else if(flag_f==0 && flag_d==0){
            if(is_dir(found_path)){
                if(access(found_path,R_OK)==0 && found_dir==1){
                    char temp[PATH_SIZE];
                    strcpy(temp,"hop");
                    strcat(temp," ");
                    strcat(temp,found_path);
                    hop(temp);
                } 
                else {
                    printf("Missing permissions for task!\n");
                }
            }
            else{
                if(access(found_path,R_OK)==0 && found_path==1){
                    print_file(found_path);
                } 
                else {
                    printf("Missing permissions for task!\n");
                }
            }
        }
    }
    return ;
}
