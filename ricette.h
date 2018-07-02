/**
 * @file ricette.h
 *
 * Questa libreria contiene procedure e funzioni utili all'interno del sottomenu' "ricette".
 *
 *
 * @authors Francesco Ferrara & Alessia Laforgia
 *
 */




#ifndef RICETTE_H_
#define RICETTE_H_
#endif /* RICETTE_H_ */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

void ricette();
void stampa_elenco_ricette(int num_linee);

/**
 * Questa funzione, dato in input un numero intero, calcola il numero di stelle che verranno visualizzate
 * relativamente al grado di difficolta' di una ricetta.
 *
 * Ricevendo il numero intero che indica la difficolta', compreso tra 1 e 5, la funzione carica l'array di 5 posizioni max
 * con un numero di stelle corrispondenti all'intero inserito
 *
 * @param num,ovvero l'intero che indica il grado di difficolta'
 *
 * @return il vettore caricato di stelle in base all'input inserito
 */
char* stampa_stelle(int num); //stampa le stellette di difficolta',int num indica il numero della ricetta

void stampa_ricetta(int num);

int* ricerca_ricetta(char alimento[]);
