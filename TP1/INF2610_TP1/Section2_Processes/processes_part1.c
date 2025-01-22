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
    int totalChild = 0;
    registerProc(pid_0, getppid(), 0, 0);    // Call registerProc for level 0
    printf("Level 0: PID %d \n", pid_0);

    // Level 1.1
    if (fork() == 0) {
        int pid_1_1 = getpid();
        registerProc(pid_1_1, getppid(), 1, 1);     // Call registerProc for level 1.1
        printf("Level 1.1: PID %d, Parent PID %d, Is Parent Level 0: %d\n", 
               pid_1_1, getppid(), getppid() == pid_0);

        // Level 2.1
        if (fork() == 0) {
            int pid_2_1 = getpid();
            registerProc(pid_2_1, getppid(), 2, 1);  // Call registerProc for level 2.1
            printf("Level 2.1: PID %d, Parent PID %d, Is Parent Level 1.1: %d\n", 
                   pid_2_1, getppid(), getppid() == pid_1_1);
            exit(1); // End Level 2.1 process
        }

        // Parent of Level 2.1 (Level 1.1) waits for its child
        // And counts the number of descendent processes
        
        int count = 0;
        while (wait(NULL) > 0) count++; // wait for Level 2.1
        exit(count + 1); // End Level 1.1 process
    }

    // Level 1.2
    if (fork() == 0) {
        int pid_1_2 = getpid();
        registerProc(pid_1_2, getppid(), 1, 2);     // Call registerProc for level 1.2
        printf("Level 1.2: PID %d, Parent PID %d, Is Parent Level 0: %d\n", 
               pid_1_2, getppid(), getppid() == pid_0);
        
        // Level 2.2 and 2.3
        int count = 0;
        for (int i=0; i<childNum2; i++) {
            if (fork() == 0) {
                int pid_2 = getpid();
                registerProc(pid_2, getppid(), 2, i + 2);
                printf("Level 2.2 || 2.3: PID %d, Parent PID %d, Is Parent Level 1.2: %d\n", 
                    pid_2, getppid(), getppid() == pid_1_2);
                exit(1);
            }
        }

        // Parent of Level 2.2 and 2.3 (Level 1.2) waits for its children
        while (wait(NULL) > 0) count++;
        exit(count + 1); // End level 1.2 process

    }

    // Level 1.3
    if (fork() == 0) {
        int pid_1_3 = getpid();
        registerProc(pid_1_3, getppid(), 1, 3);
        printf("Level 1.3: PID %d, Parent PID %d, Is Parent Level 0: %d\n", 
               pid_1_3, getppid(), getppid() == pid_0);

        // Level 2.4
        if (fork() == 0) {
            int pid_2_4 = getpid();
            registerProc(pid_2_4, getppid(), 2, 4);
            printf("Level 2.4: PID %d, Parent PID %d, Is Parent Level 1.3: %d\n", 
                   pid_2_4, getppid(), getppid() == pid_1_3);
            exit(1); // End Level 2.4 process
        }

        // Parent of Level 2.4 (Level 1.3) waits for its child
        int count = 0;
        while (wait(NULL) > 0) count++;
        exit(count + 1); // End level 2.4 process
    }

    // Level 1.4
    if (fork() == 0) {
        int pid_1_4 = getpid();
        registerProc(pid_1_4, getppid(), 1, 4);
        printf("Level 1.4: PID %d, Parent PID %d, Is Parent Level 0: %d\n", 
               pid_1_4, getppid(), getppid() == pid_0);
        
        // Level 2.5, 2.6, 2.7
        int count = 0;
        for (int i=0; i<childNum3; i++) {
            if (fork() == 0) {
                int pid_2 = getpid();
                registerProc(pid_2, getppid(), 2, i+5);
                printf("Level 2.5 || 2.6 || 2.7: PID %d, Parent PID %d, Is Parent Level 1.4: %d\n", 
                    pid_2, getppid(), getppid() == pid_1_4);
                exit(1);
            }
        }

        // Parent of Level 2.5, 2.6, 2.7 (Level 1.4) waits for its children
        while (wait(NULL) > 0) count++;
        exit(count + 1); // End level 1.2 process

    }

    // Parent (Level 0) waits for all Level 1 processes to finish
    // Root process: Count all descendants
    int status;
    while (wait(&status) > 0) {
        if (WIFEXITED(status)) {
            totalChild += WEXITSTATUS(status);
        }
    }

    // Print total descendants
    printf("Total descendants of Level 0 (root): %d\n", totalChild);
    
    printProcRegistrations();

    // Replace level0 process with `ls -l .`
    char *args[] = {"ls", "-l", ".", NULL};
    if (execvp("ls", args) == -1) {
        perror("execvp failed");
        exit(1);
    }
}

