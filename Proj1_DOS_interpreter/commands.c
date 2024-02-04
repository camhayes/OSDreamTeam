#include "commands.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void cd_command(char* arg1, const char* arg2){
    if (arg2 != NULL){
        printf("ERROR: too many arguments entered for command 'cd'");
    }else{
        if(chdir(arg1) != 0){
            printf("ERROR: unable to find file/directory %s", arg1);
        };
    }
}

void pwd_command(){
    system("pwd");
}

void dir_command(char* arg1, char* arg2){
    //lists all files (ls)
    char commandString[100];
    commandString[0] = '\0';
    strcat(commandString, "ls");
    strcat(commandString, " ");
    if(arg1 != NULL){
        strcat(commandString, arg1);
        if(arg2 != NULL){
            strcat(commandString, " ");
            strcat(commandString, arg2);
        }
    }
    system(commandString);
}

void type_command(char* arg1, char* arg2){
    char commandString[100];
    commandString[0] = '\0';
    strcat(commandString, "cat ");
    if(arg1 == NULL){
        printf("invalid command: no file given\n");
        return;
    }
    strcat(commandString, arg1);
    if(arg2 != NULL){
        strcat(commandString, " ");
        strcat(commandString, arg2);
    }
    system(commandString);
    printf("\n");
}

void del_command(char* arg1, char* arg2){
    char commandString[100];
    commandString[0] = '\0';
    strcat(commandString, "rm ");
    if(arg1 == NULL){
        printf("invalid command: no args given\n");
        return;
    }
    strcat(commandString, arg1);
    if(arg2 != NULL){
        strcat(commandString, " ");
        strcat(commandString, arg2);
    }
    system(commandString);
}

void ren_command(char* arg1, char* arg2){
    char commandString[100];
    commandString[0] = '\0';
    strcat(commandString, "mv ");
    if(arg1 == NULL){
        printf("invalid command: not enough args given\n");
        return;
    }
    strcat(commandString, arg1);
    if(arg2 == NULL){
        printf("invalid command: not enough args given\n");
        return;
    }
    strcat(commandString, " ");
    strcat(commandString, arg2);
    system(commandString);
}

void copy_command(char* arg1, char* arg2){
    char commandString[100];
    commandString[0] = '\0';
    strcat(commandString, "cp ");
    if(arg1 == NULL){
        printf("invalid command: not enough args given\n");
        return;
    }
    strcat(commandString, arg1);
    if(arg2 == NULL){
        printf("invalid command: not enough args given\n");
        return;
    }
    strcat(commandString, " ");
    strcat(commandString, arg2);
    system(commandString);
}