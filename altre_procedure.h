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
 *
 * @pre stringa deve essere composta da soli numeri
 * @param stringa, ovvero la stringa che bisogna controllare sia davvero composta da soli numeri.
 *
 *@return un valore booleano tra true o false(codificati in 1: true, 2:false)
 * true: se la funzione non è composta da soli numeri;
 * false: se la stringa è composta da soli numeri;
 *
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

/**
 * Procedura che permette di visualizzare sull'interfaccia del programma eventuali
 * note e promemoria.
 */
void memos();

/**
 * Questa funzione trasforma una stringa composta di lettere (anche maiuscole) in lettere tutte minuscole
 * @param stringa, ovvero la stringa da convertire tutta in minuscolo
 * @return stringa, ovvero la stringa convertita
 */

const char* low_conversion(char* stringa[]); //converte la stringa di ingresso in caratteri minuscoli

