/*
 * Ecole Polytechnique Montreal - GIGL
 * Hiver 2025
 * Processes - part1.c
 *
 * Ajoutez vos noms, prénoms et matricules
*/

#include "libprocesslab/libprocesslab.h"
#include "stdbool.h"

#define childNum2 2
#define childNum3 3

void question1()
{
    // TODO
    // Level 0
    int pid_0 = getpid();
    printf("Level 0: PID %d \n", pid_0);

    // Level 1.1
    if (fork() == 0) {
        int pid_1_1 = getpid();
        printf("Level 1.1: PID %d, Parent PID %d, Is Parent Level 0: %d\n", 
               pid_1_1, getppid(), getppid() == pid_0);

        // Level 2.1
        if (fork() == 0) {
            int pid_2_1 = getpid();
            printf("Level 2.1: PID %d, Parent PID %d, Is Parent Level 1.1: %d\n", 
                   pid_2_1, getppid(), getppid() == pid_1_1);
            exit(0); // End Level 2.1 process
        }

        // Parent of Level 2.1 (Level 1.1) waits for its child
        while (wait(NULL) > 0);
        exit(0); // End Level 1.1 process
    }

    // Level 1.2
    if (fork() == 0) {
        int pid_1_2 = getpid();
        printf("Level 1.2: PID %d, Parent PID %d, Is Parent Level 0: %d\n", 
               pid_1_2, getppid(), getppid() == pid_0);
        
        // Level 2.2 and 2.3
        for (int i=0; i<childNum2; i++) {
            if (fork() == 0) {
                int pid_2 = getpid();
                printf("Level 2.2 || 2.3: PID %d, Parent PID %d, Is Parent Level 1.2: %d\n", 
                    pid_2, getppid(), getppid() == pid_1_2);
                exit(0);
            }
        }

        // Parent of Level 2.2 and 2.3 (Level 1.2) waits for its children
        while (wait(NULL) > 0);
        exit(0); // End level 1.2 process

    }

    // Level 1.3
    if (fork() == 0) {
        int pid_1_3 = getpid();
        printf("Level 1.3: PID %d, Parent PID %d, Is Parent Level 0: %d\n", 
               pid_1_3, getppid(), getppid() == pid_0);

        // Level 2.4
        if (fork() == 0) {
            int pid_2_4 = getpid();
            printf("Level 2.4: PID %d, Parent PID %d, Is Parent Level 1.3: %d\n", 
                   pid_2_4, getppid(), getppid() == pid_1_3);
            exit(0); // End Level 2.4 process
        }

        // Parent of Level 2.4 (Level 1.3) waits for its child
        while (wait(NULL) > 0);
        exit(0); // End Level 1.1 process
    }

    // Level 1.4
    if (fork() == 0) {
        int pid_1_4 = getpid();
        printf("Level 1.4: PID %d, Parent PID %d, Is Parent Level 0: %d\n", 
               pid_1_4, getppid(), getppid() == pid_0);
        
        // Level 2.5, 2.6, 2.7
        for (int i=0; i<childNum3; i++) {
            if (fork() == 0) {
                int pid_2 = getpid();
                printf("Level 2.5 || 2.6 || 2.7: PID %d, Parent PID %d, Is Parent Level 1.4: %d\n", 
                    pid_2, getppid(), getppid() == pid_1_4);
                exit(0);
            }
        }

        // Parent of Level 2.5, 2.6, 2.7 (Level 1.4) waits for its children
        while (wait(NULL) > 0);
        exit(0); // End level 1.2 process

    }

    // Parent (Level 0) waits for all Level 1 processes to finish
    while (wait(NULL) > 0);
}

