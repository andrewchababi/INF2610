/*
 * Ecole Polytechnique Montreal - GIGL
 * Hiver 2025
 * Processes - part2.c
 *
 * Ajoutez vos noms, prénoms et matricules
*/

#include "./libprocesslab/libprocesslab.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define m 1000000
#define nb 4

long somme[nb];


// fonction exécutée par chaque thread créé
void* contribution(void*p)
{
    // TODO
    int no = *(int*)p;
    int start = (no * m)/nb + 1;
    int end = (no + 1)*m/nb;

    somme[no] = 0;

    for(int i = start; i <= end; i++){
      somme[no] += i;
    }

  return NULL;
}


void question2( )
{
    // TODO

    pthread_t threads[nb]; // creer un tableau pour les threads
    int thread_args[nb];
    // pthread_create();

    // int total = m * (m + 1)/2;
    // printf( );
    
}

