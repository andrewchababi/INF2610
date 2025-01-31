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
    
	for (int i=0; i<nb; i++) {
		int* thread_num = malloc(sizeof(int));
		if (thread_num == NULL) {
			perror("Pas capable d'alouer pour le thread numero");
			exit(EXIT_FAILURE);
		}

		*thread_num = i;
		if (pthread_create(&threads[i], NULL, contribution, thread_num) != 0) {
			perror("Echoue de creation de thread");
			exit(EXIT_FAILURE);
		}
	}	

	// Wait for all threads to finish
    for (int i = 0; i < nb; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            exit(EXIT_FAILURE);
        }
    }

	long total_sum = 0;
    for (int i = 0; i < nb; i++) {
        total_sum += somme[i];
    }

	// Calculate the theoretical sum using the formula
    long expected_sum = (long)m * (m + 1) / 2;

    // Print results
    printf("Calculated sum using threads: %ld\n", total_sum);
    printf("Expected sum using formula: %ld\n", expected_sum);
    printf("Difference: %ld\n", total_sum - expected_sum);

	
}

