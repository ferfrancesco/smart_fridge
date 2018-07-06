/**
 * @file alimenti.h
 *
 * Questa libreria contiene procedure relative al sottomenu' della categoria "alimenti".
 *
 * @authors Francesco Ferrara & Alessia Laforgia
 *
 */

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
 * Questa procedura permette di modificare alimenti gia' presenti nello Smart Fridge. Funziona tramite lo stabilimento di una correlazione
 * di tre campi della struct "alimento", ovvero archivio_alimenti.quantita, archivio_alimenti.quantita_tot, archivio_alimenti.numero.
 * Infatti, se si modifica il numero di confezioni di alimento presenti in frigo (archivio_alimenti.numero), verrà conseguentemente modificata anche la quantità totale di un alimento(archivio_alimenti.quantita_tot),
 * poichè il sistema rimuoverà da essa il quantitativo (in ml o g ) corrispondente ad una confezione di quell'alimento (archivio_alimenti. quantita).
 *
 *
 * @param num_linee,ovvero di quante linee e' composto il file "alimenti.txt"
 *
 * Come risultato produce la modifica delle quantita' di certi alimenti presenti nello Smart Fridge.
 */

void modifica_alimenti(int num_linee);

/**
 * Questa procedura permette di capire quali sono,eventualmente, gli alimenti scaduti o in scadenza tra quelli presenti all'interno del sistema Smart Fridge.
 * Segue un algoritmo molto preciso, che conta il giorno attuale, contando la sua posizione da 0 a 365.
 * Dopodiche' legge la data di scadenza di un alimento (sempre con la stessa numerazione) e confronta il giorno attuale con il giorno di scadenza di ogni singolo alimento.
 * Se il giorno in cui l'alimento scade e' inferiore al giorno attuale,l'alimento e' scaduto.
 * Se e' maggiore rispetto al giorno attuale, ma di al massimo la costante SOGLIA_SCADENZA, l'alimento e' in scadenza.
 * Se invece è maggiore di piu' di SOGLIA_SCADENZA, l'alimento non e' ne' in scadenza, ne' scaduto.
 * (SOGLIA_SCADENZA è una costante che vale 3).
 *
 * @pre viene attivata in automatico quando si seleziona il sottomenù "alimenti"
 * @pre devono esserci alimenti presenti all'interno dello Smart Fridge
 * @param num_linee, ovvero il numero di linee di cui si compone il file "alimenti.txt"
 */

void scadenze(int num_linee);



