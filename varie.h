#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>


/**
 * Questa procedura stampa il menu per la categoria "varie".
 * E' possibile effettuare diverse scelte al suo interno.
 *
 * @pre E' necessario che nel menu principale dello Smart Fridge sia selezionata la categoria "varie"
 *
 */
void varie();

/**
 * Procedura che stampa le diverse opzioni disponibili riguardo il menu settimanale
 * @pre per selezionare la prima scelta del menu, c'e' bisogno che il menu sia gia' stato inserito in precedenza
 */
void menu_sett();

/**
 * Questa procedura permette di accedere al sottomenu' riguardante la lista della spesa nella categoria "varie"
 *
 */
void lista();

/**Questa procedura permette di accedere ad un sottomenu', interno alla categoria "varie", che permette di visualizzare le statistiche relative ai cibi più consumati e alle ricette più preparate.
 *
 *@pre bisogna accedere prima al sottomenu' della categoria "varie" per visualizzare le statistiche.
 *@post verranno visualizzare le statistiche relative a:
 *		1) Alimenti piu' consumati;
 *		2) Ricette piu' preparate;
 *
 *
 */
void statistiche();

/**
 * Questa procedura permette di ordinare, tramite un algoritmo "selection sort", l'array passato alla procedura,
 * in maniera decrescente.E' una procedura generica e riusabile in quanto, a seconda dei parametri attuali che le vengono forniti, ordina
 * oggetti diversi. Se gli oggetti appartengono ad una struct, vengono copiati i campi della struct in array locali ed avviene l'ordinamento di questi array locali.
 *
 * @param array_int, ovvero l'array di interi del quale si deve effettuare l'ordinamento principale
 * @param array_nomi,ovvero l'array dei nomi corrispondenti ai numeri che devono essere ordinati
 * @param num_linee, ovvero il numero di linee di lui e' composto il file che deve essere ordinato
 */

void selection_sort(int array_int[],char array_nomi[CONSUM_MAX][LUNGH_MAX_NOME], int num_linee);
