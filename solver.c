// Main program that runs the maze solver

// !!! DO NOT MODIFY THIS FILE !!!

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <io.h>
#include <windows.h>

#include "Maze.h"
#include "solve.h"


int main(int argc, char *argv[]) {
    
    struct _finddata_t file_info;
    intptr_t handle;
    handle = _findfirst("mazes\\*.*", &file_info);
    int i = 1;
    do {
        if (strcmp(file_info.name, ".") != 0 && strcmp(file_info.name, "..") != 0) {
            printf("%d. %s\n", i,file_info.name);
            i++;
        }
    } while (_findnext(handle, &file_info) == 0);
    i = i-1;
    int choice;
    printf("Please enter a digit ranging from 1 to %d to select the maze: ", i);
    scanf("%d", &choice);
    while (choice <= 0 || choice > i) {
        printf("Please enter a digit ranging from 1 to %d to select the maze: ", i);
        scanf("%d", &choice);
    }
    
    char mazeName[100];
    handle = _findfirst("mazes\\*.*", &file_info);
    int j = 1;
    do {
        if (strcmp(file_info.name, ".") != 0 && strcmp(file_info.name, "..") != 0) {
            if (j == choice) {
                printf("You have selected %s\n",file_info.name);
                mazeName[0] = '\0';
                strcat(mazeName,"mazes\\");
                strcat(mazeName, file_info.name);   
            }
            j++;
        }
    } while (_findnext(handle, &file_info) == 0);

    int speed;
    printf("Please enter a digit ranging from 1 to 11 to select the speed: ", i);
    scanf("%d", &speed);
    while (speed <= 0 || speed > 11) {
        printf("Please enter a digit ranging from 1 to 11 to select the speed: ", i);
        scanf("%d", &speed);
    }
    
    FILE *fp = fopen(mazeName, "r");
    if (fp == NULL) {
        fprintf(stderr, "error: could not open '%s' for reading\n", mazeName);
        exit(EXIT_FAILURE);
    }

    Maze m = MazeRead(fp);
    fclose(fp);
    if (m == NULL) {
        fprintf(stderr, "error: failed to read maze %s\n", mazeName);
        exit(EXIT_FAILURE);
    }

    int pauseMs;

    switch (speed) {
        case  1:  pauseMs = 1000; break;
        case  2:  pauseMs =  500; break;
        case  3:  pauseMs =  200; break;
        case  4:  pauseMs =  100; break;
        case  5:  pauseMs =   50; break;
        case  6:  pauseMs =   20; break;
        case  7:  pauseMs =   10; break;
        case  8:  pauseMs =    5; break;
        case  9:  pauseMs =    2; break;
        case 10:  pauseMs =    1; break;
        case 11:  pauseMs =    0; break;
        default:
            exit(EXIT_FAILURE);
    }

    MazeSetDisplayPause(pauseMs);

    bool result = solve(m);

    printf("\nThe exit was %s\n", result ? "found!" : "not found.");
    
    MazeFree(m);

}


