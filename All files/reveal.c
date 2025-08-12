#include "reveal.h"
#include "colors.h"

#define PATH_SIZE 1024

int compare(const void *a,const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

void reveal(char *input){
    char *token=strtok(input," \t");
    if(token==NULL||strcmp("reveal",token)!=0){
        printf("wrong command");
        return;
    }
    int cnt1=0,cnt2=0;
    int dir_provided=0;
    getcwd(dir_path,PATH_SIZE);    
    token=strtok(NULL," \t");
    while(token!=NULL){
        if(token[0]=='-'&&(token[1]>='a'&&token[1]<='z')){
            int i=1;
            while(token[i]!='\0'){
                if(token[i]=='a'){
                    cnt1=1;
                }
                if(token[i]=='l'){
                    cnt2=1;
                }
                i++;
            }
        }
        else{
            dir_provided=1;
            if(strcmp(token,".")==0){
                strcpy(prev_dir,dir_path);
                getcwd(dir_path,PATH_SIZE);
                printf("%s\n",dir_path);
            }
            else if(strcmp(token,"..")==0){
                strcpy(prev_dir,dir_path);
                if(chdir(token)==0){
                    getcwd(dir_path,PATH_SIZE);
                }
            }
            else if(strcmp(token,"~")==0){
                strcpy(prev_dir,dir_path);
                strcpy(dir_path,home_dir);
            }
            else if(strcmp(token,"-")==0){
                strcpy(dir_path,prev_dir);
            }
            else{
                strcpy(prev_dir,dir_path);
                if(chdir(token)==0){
                    getcwd(dir_path,PATH_SIZE);
                    printf("%s\n",dir_path);
                }
                else{
                    printf("no such directory exits\n");
                }
            }
        }
        token=strtok(NULL," \t");
    }
    if(dir_path==NULL){
        printf("directory not specified");
        return;
    }
    if(dir_provided==0){
        getcwd(dir_path,PATH_SIZE);
    }
    struct dirent *entry;
    DIR *dir=opendir(dir_path);
    if(dir==NULL){
        printf("couldn't open directory");
        return;
    }
    char *filenames[PATH_SIZE];
    int file_count = 0;

    while((entry=readdir(dir))!=NULL) {
        if(cnt1==0&&entry->d_name[0]=='.'){
            continue;
        }
        filenames[file_count]=strdup(entry->d_name);
        file_count++;
    }
    closedir(dir);
    qsort(filenames,file_count,sizeof(char*),compare);
    for(int i=0;i<file_count;i++){
        char full_path[PATH_SIZE];
        snprintf(full_path,sizeof(full_path),"%s/%s",dir_path,filenames[i]);
        struct stat path_stat;
        if(stat(full_path,&path_stat)==-1){
            perror("stat failed");
            continue;
        }
        if (S_ISDIR(path_stat.st_mode)) {
            printf("%s%s%s\n",BLUE,filenames[i],RESET);
        } else if (path_stat.st_mode & S_IXUSR) {
            printf("%s%s%s\n",GREEN,filenames[i],RESET);
        } else {
            printf("%s%s%s\n",WHITE,filenames[i],RESET);
        }
        if(cnt2==1) {
            extra(path_stat,filenames[i]);
        } 
        free(filenames[i]);
    }
}


void extra(struct stat path_stat,char *filename){
    char permissions[11];
    permissions[0]=S_ISDIR(path_stat.st_mode) ? 'd' : '-';
    permissions[1]=(path_stat.st_mode & S_IRUSR) ? 'r' : '-';
    permissions[2]=(path_stat.st_mode & S_IWUSR) ? 'w' : '-';
    permissions[3]=(path_stat.st_mode & S_IXUSR) ? 'x' : '-';
    permissions[4]=(path_stat.st_mode & S_IRGRP) ? 'r' : '-';
    permissions[5]=(path_stat.st_mode & S_IWGRP) ? 'w' : '-';
    permissions[6]=(path_stat.st_mode & S_IXGRP) ? 'x' : '-';
    permissions[7]=(path_stat.st_mode & S_IROTH) ? 'r' : '-';
    permissions[8]=(path_stat.st_mode & S_IWOTH) ? 'w' : '-';
    permissions[9]=(path_stat.st_mode & S_IXOTH) ? 'x' : '-';
    permissions[10]='\0';

    struct passwd *pw=getpwuid(path_stat.st_uid);
    struct group *gr=getgrgid(path_stat.st_gid);
    char timebuf[80];
    strftime(timebuf,sizeof(timebuf),"%b%d%H:%M",localtime(&path_stat.st_mtime));

    printf("%s %ld %s %s %ld %s %s\n", permissions, path_stat.st_nlink, pw->pw_name, gr->gr_name, path_stat.st_size, timebuf, filename);
}