/*
 * Ecole Polytechnique Montreal - GIGL
 * Hiver 2025
 * SystemCalls - part1.c
 *
 * Ajoutez vos noms, prénoms et matricules
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


int main () {
    // TODO
    const char* filename = "systemcalls_output2.txt";
    int file;
    
    file = open(filename, O_TRUNC | O_WRONLY);
    if (file < 0) {
        perror("Appel systeme open a echoue");
        exit(EXIT_FAILURE);
    }

    printf("Saisissez votre text suivi de CTRL-D :\n");

    char buffer[1];
    ssize_t bytesRead;

    while ((bytesRead = read(STDIN_FILENO, buffer, 1)) > 0) {
        write(file, buffer, bytesRead);
    }

    close(file);
    
    return 0;
}
