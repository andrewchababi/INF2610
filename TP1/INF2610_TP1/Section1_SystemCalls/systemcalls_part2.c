/*
 * Ecole Polytechnique Montreal - GIGLL
 * Hiver 2025
 * SystemCalls - part2.c
 *
 * Ajoutez vos noms, prénoms et matricules
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void part21 ()
{
    // TODO
    const char* messageWrite = "77dbcb01f575f1c32s196c3a7d27f62e (printed using write) \n";
    const char* messagePrint = "77dbcb01f575f1c32s196c3a7d27f62e (printed using printf) \n";    

    for (size_t i = 0; i < strlen(messagePrint); i++) {
        printf("%c", messagePrint[i]);
    }

    write(STDOUT_FILENO, messageWrite, strlen(messageWrite));
}

void part22 ()
{
    // DONE
    setvbuf(stdout, NULL, _IONBF, 0);
    part21();    
}

int main (int argc, char* argv[])
{
    
    if (argc!=2)
    {   printf("Le programme a un seul paramètre : 1 ou 2\n");
        return 1;
    }
    switch (atoi(argv[1])) {
         case 1:        part21();
                        break;
         case 2:        part22();
                        break;
        default:        printf(" Le paramètre du programme est invalide\n");
                        return 1;
    }
    return 0;
}
