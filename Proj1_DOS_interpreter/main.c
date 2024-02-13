#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>
#include "commands.h"
#include "commands.c"

#define MAX_LINE_LENGTH  80

enum Commands {CD_CMD, DIR_CMD, TYPE_CMD, DEL_CMD, REN_CMD, COPY_CMD, PWD_CMD, INVALID_CMD};


int getCommandType(char* commandString){
    if(strcmp(commandString, "cd") == 0){
        return CD_CMD;
    }
    if (strcmp(commandString, "dir") == 0){
        return DIR_CMD;
    }
    if(strcmp(commandString, "type") == 0){
        return TYPE_CMD;
    }
    if(strcmp(commandString, "del") == 0){
        return DEL_CMD;
    }
    if(strcmp(commandString, "ren") == 0){
        return REN_CMD;
    }
    if(strcmp(commandString, "copy") == 0){
        return COPY_CMD;
    }
    if(strcmp(commandString, "pwd") == 0){
        return PWD_CMD;
    }
    return INVALID_CMD;
}

static bool interrupt_cmd = false;

void handle_interrupt(int signum){
    interrupt_cmd = true;
}

int main() {

    char input[MAX_LINE_LENGTH];
    char* cmd;
    char* args[4];
    char currentDir[100];

    struct sigaction act;
    act.sa_handler = handle_interrupt;
    

    //main loop, infinite until ctrl^c
    while(!interrupt_cmd){
        printf("Type Ctrl-C to exit\n");
        printf("DOS-INTERPRETER>");
        fgets(input, MAX_LINE_LENGTH, stdin);
        sigaction(SIGINT, &act, NULL);
        //max two args

        cmd = strtok(input, " \n");
        args[1] = strtok(NULL, " \n");
        args[2] = strtok(NULL, " \n");
        args[3] = strtok(NULL, " \n");

        if(args[1] == NULL){
            cmd = input;
        }

        if(args[3] != NULL){
            printf("Invalid Input: Too Many Args");
            continue;
        }

        switch (getCommandType(cmd)) {
            case CD_CMD:
                cd_command(args[1], args[2]);
                break;
            case PWD_CMD:
                pwd_command();
                break;
            case DIR_CMD:
                //list files command
                dir_command(args[1], args[2]);
                break;
            case TYPE_CMD:
                type_command(args[1], args[2]);
                break;
            case DEL_CMD:
                del_command(args[1], args[2]);
                break;
            case REN_CMD:
                ren_command(args[1], args[2]);
                break;
            case COPY_CMD:
                copy_command(args[1], args[2]);
                break;
            case INVALID_CMD:
                printf("ERROR: Invalid command\n");
                break;
        }
        

    }
}


