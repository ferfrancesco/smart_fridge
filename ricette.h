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

//----------------------------------------------------------------------------
//PROCEDURE RICETTE VARIE
/**
 * 	Questa procedura permette di stampare il sottomenu per la categoria "ricette".
 * 		E' possibile :
 * 	1) 	Visualizzare le ricette salvate nel sistema
 * 	2)	Ricercare corrispondenza ricette per ingrediente o per numero di Kcal
 * 	3)	Aggiungere una ricetta
 * 	4)  Modificare una ricetta
 * 	5)	Rimuovere una ricetta
 * 	6)	Tornare al menu
 */

void ricette();

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


//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//VISUALIZZAZIONE RICETTE

/**
 * Questa procedura richiama a sua volta le sottoprocedure "stampa_elenco_ricette" e "stampa_ricetta"
 */

void visualizza_ricette();

//TODO COMMENTA

void stampa_elenco_ricette(int num_linee);

/**
 * Questa procedura permette di stampare le caratteristiche relative ad una ricetta, prendendo in input il
 * numero corrispondente alla ricetta di cui si vogliono visualizzare le caratteristiche.
 * Il numero della ricetta da visualizzare si ricava dall'elenco globale delle ricette.
 *
 * @param num, ovvero il numero della ricetta di cui visionare le caratteristiche.
 */

void stampa_ricetta(int num);


//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//RICERCA RICETTE

/**
 * La funzione "ricerca" prende in input una stringa (che rappresenta un alimento) e restituisce
 * la ricetta (o le ricette) che contengono quell'ingrediente.Dà come valore di ritorno un array
 * di interi, ovvero "ricette_con_alimento"
 *
 * @param alimento,ovvero l'ingrediente con il quale ricercare le corrispondenze
 * @return ricette_con_alimento,ovvero un array di indici interi che indicano le posizioni delle corrispondenze
 */

int* ricerca(char alimento[]);  //int* perchè ha come ritorno un array di intt

/**
 * E' la procedura che ci permette di accedere alla funzione "ricerca", per trovare le
 * corrispondenze tra un alimento e le ricette disponibili all'interno del sistema.
 */

void ricerca_ricette();


//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
//GESTIONE RICETTE

/**
 * Questa procedura permette di aggiungere ricette alla lista di ricette presenti all'interno del sistema.
 * E' possibile immettere il nome della ricetta, gli ingredienti, la difficolta' e gli steps.
 *
 */

void aggiungi_ricette();
/**
 * Questa procedura permette di modificare le caratteristiche di una ricetta, ovvero nome, difficolta', kcal, ingredienti o procedura.
 * Si accede ad un sottomenu' di modifica, dal quale si immette la scelta relativa al dato da modificare.
 * 1)nome
 * 2)difficolta'
 * 3)kcal
 * 4)ingredienti
 * 5)procedura
 *
 * @pre Per accedere al sottomenu' di modifica e' necessario accedere alla categoria "ricette" del programma
 * @pre E' necessario che ci siano ricette all'interno del programma
 *
 * @post si ha l'effettiva modifica dei dati di una ricetta
 *
 */

void modifica_ricette();

/**
 * Questa procedura permette di aggiungere, modificare o rimuovere un ingrediente da una ricetta gia' esistente all'interno del sistema Smart Fridge.
 * @pre e' necessario prima accedere alla categoria "ricette", poi al sottomenu' di modifica di una ricetta.
 * @pre e' necessario che ci siano ricette all'interno dello Smart Fridge
 *
 * @param ingrediente, ovvero il numero dell'ingrediente che, eventualmente, si vuole modificare
 */

void modifica_ingredienti(int ingrediente);

/**
 * Questa procedura permette di modificare i passi di una ricetta.
 * @pre e' necessario accedere al sottomenu' di modifica di una ricetta e poi selezionare la modifica della procedura della ricetta
 * @pre devono esserci ricette all'interno dello Smart Fridge
 * @param step,ovvero il numero dello step che si intende modificare o eliminare
 */

void modifica_procedura(int ingrediente);

/**
 * Questa procedura permette di rimuovere una ricetta dal sistema Smart Fridge.
 * @pre e' necessario accedere al sottomenu' della categoria "ricette" e selezionare "rimuovi una ricetta"
 * @post rimuove una ricetta
 *
 */

void rimuovi_ricette();


//----------------------------------------------------------------------------

