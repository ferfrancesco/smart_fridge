/**
 * @file altre_procedure.h
 *
 * Questa libreria contiene controlli e procedure utilizzati in altre librerie e/o altre procedure
 * appartenenti a differenti sottomenu'.
 *
 * @authors Francesco Ferrara & Alessia Laforgia
 *
 */

#ifndef OPERAZIONI_VARIE_H_
#define OPERAZIONI_VARIE_H_
#endif /* OPERAZIONI_VARIE_H_ */

/*Libreria contenente operazioni varie quali controlli di input,atti al corretto funzionamento del programma*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Questa funzione verifica che la stringa data in input sia composta da soli numeri.
 * @param stringa, ovvero quella che dovrebbe essere la data di scadenza
 * @return un valore booleano tra true o false(codificati in 1: true, 2:false)
 */
int isOnlyNumbers(char* stringa);

/**
 * Procedura che stampa un messaggio d'errore
 */
void messaggio_errore();

/**
 * Questa procedura copia i nomi dei giorni della settimana nella struct "giorno"
 */
void dayname_fill();

/**
 * Questa procedura stampa il menu principale dello Smart Fridge.
 */
void stampa_menu();

void memos();

const char* low_conversion(char* stringa[]); //converte la stringa di ingresso in caratteri minuscoli


