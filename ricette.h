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

/**
 * Questa procedura permette di stampare le caratteristiche relative ad una ricetta, prendendo in input il
 * numero corrispondente alla ricetta di cui si vogliono visualizzare le caratteristiche.
 * Il numero della ricetta da visualizzare si ricava dall'elenco globale delle ricette.
 *
 * @param num, ovvero il numero della ricetta di cui visionare le caratteristiche.
 */
void stampa_ricetta(int num);

/**
 * La funzione "ricerca" prende in input una stringa (che rappresenta un alimento) e restituisce
 * la ricetta (o le ricette) che contengono quell'ingrediente.Dà come valore di ritorno un array
 * di interi, ovvero "ricette_con_alimento"
 *
 * @param alimento,ovvero l'ingrediente con il quale ricercare le corrispondenze
 * @return ricette_con_alimento,ovvero un array di indici interi che indicano le posizioni delle corrispondenze
 */

int* ricerca(char alimento[]);  //int* perchè ha come ritorno un array di int

/**
 * E' la procedura che ci permette di accedere alla funzione "ricerca", per trovare le
 * corrispondenze tra un alimento e le ricette disponibili all'interno del sistema.
 */
void ricerca_ricette();
/**
 * Questa procedura richiama a sua volta le sottoprocedure "stampa_elenco_ricette" e "stampa_ricetta"
 */
void visualizza_ricette();

/**
 * Questa procedura permette di aggiungere ricette alla lista di ricette presenti all'interno del sistema.
 * E' possibile immettere il nome della ricetta, gli ingredienti, la difficolta' e gli steps.
 *
 */

void aggiungi_ricette();

void modifica_ricette();
