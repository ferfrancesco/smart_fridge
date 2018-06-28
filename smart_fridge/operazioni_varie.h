#ifndef OPERAZIONI_VARIE_H_
#define OPERAZIONI_VARIE_H_
#endif /* OPERAZIONI_VARIE_H_ */

/*Libreria contenente operazioni varie quali controlli di input,atti al corretto funzionamento del programma*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int controllo_numerico(char* stringa);  //prende in input una stringa,usare quindi gets(),non scanf("%c",..). Controlla che sia ocmposta unicamente da numeri,poi la riconverte in un valore intero che restituisce
void messaggio_errore();
void dayname_fill();
void stampa_menu();
