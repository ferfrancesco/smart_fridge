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


/**Questa procedura permette di accedere ad un sottomenu', interno alla categoria "varie", che permette di visualizzare le statistiche relative ai cibi piu' consumati e alle ricette piu' preparate.
 *
 *@pre bisogna accedere prima al sottomenu' della categoria "varie" per visualizzare le statistiche.
 *@post verranno visualizzare le statistiche relative a:
 *		1) Alimenti piu' consumati;
 *		2) Ricette piu' preparate;
 *
 *
 */

void statistiche();
