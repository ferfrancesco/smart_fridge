#ifndef ALIMENTI_H_
#define ALIMENTI_H_
#endif /* ALIMENTI_H_ */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>


/**
 * La procedura mi richiama il menu di scelta per la categoria alimenti.
 *
 *
 */
void alimenti();


/**
 * La procedura stampa gli alimenti presenti nello Smart Fridge.
 *
 * @param num_linee, ovvero di quante linee e' composto il file "alimenti.txt"
 *
 * Come risultato produce la stampa della tabella degli alimenti nello Smart Fridge.
 */

void stampa_alimenti(int num_linee);


/**
 * La procedura permette di aggiungere alimenti all'interno dello Smart Fridge.
 *
 * @param num_linee, ovvero di quante linee e' composto il file "alimenti.txt"
 *
 * Come risultato produce l'aggiunta di un certo numero di alimenti allo Smart Fridge.
 */
void aggiunta_alimenti(int num_linee);

/**
 * La procedura permette di modificare alimenti gia' presenti nello Smart Fridge.
 *
 * @param num_linee,ovvero di quante linee e' composto il file "alimenti.txt"
 *
 * Come risultato produce la modifica delle quantita' di certi alimenti presenti nello Smart Fridge.
 */

void modifica_alimenti(int num_linee);



