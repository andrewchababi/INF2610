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
    const char* filename = "systemcalls_output1.txt";

    int file = open(filename, O_TRUNC);
    if (file < 0) {
        perror("Appel systeme open a echoue");
        return EXIT_FAILURE;
    }

    const char* message = "Saisissz votre texte suivi de CTRL-D : \n";
    printf(message);
    
    char buffer; 
    ssize_t size;

    while((size = read(STDIN_FILENO, buffer, 1)) > 0) {
        write(file, buffer, size);
    }

    close(file);

    return 0;
}
