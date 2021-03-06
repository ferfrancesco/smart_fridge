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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//--------------------------------------------------------------------------------


/**
 * Questa funzione verifica che la stringa data in input sia composta da soli numeri.
 *
 * @pre stringa deve essere composta da soli numeri
 * @param stringa, ovvero la stringa che bisogna controllare sia davvero composta da soli numeri.
 *
 *@return ritorno, un valore booleano tra true o false(codificati in 1: true, 0:false)
 * true: se la funzione non e' composta da soli numeri;
 * false: se la stringa e' composta da soli numeri;
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
 * Questa funzione trasforma una stringa composta di lettere (anche maiuscole) in lettere tutte minuscole
 * @param stringa, ovvero la stringa da convertire tutta in minuscolo
 * @return stringa, ovvero la stringa convertita
 */

char* low_conversion(char stringa[]); //converte la stringa di ingresso in caratteri minuscoli



/**
  * Questa procedura non fa altro che effettuare controlli sul calcolo delle consumazioni di ciascun alimento e sulla trascrizione dell'aggiornamento sul file "consumazioni.txt"
  * Vengono distinti diversi casi a seconda se l'alimento e' gia' in lista consumazioni, se il file � vuoto, oppure se e' gia' presente nel file.
  * Se il file e' vuoto, si scrive l'alimento e le relative consumazioni
  * Se il file non e' vuoto ma non esistono corrispondenze, si aggiunge il nome dell'alimento e le relative consumazioni
  * Se il file non e' vuoto e viene trovata una corrispondenza, si aggiorna solo il dato relativo alle consumazioni.
  *
  * @param num_consumazioni, ovvero il numero di confezioni che si stanno eliminando di un dato alimento.
  * @param num_linee, ovvero di quante linee e' composto il file "consumazioni.txt".
  * @param stringa, ovvero il nome dell'alimento di cui si intende cercare la corrispondenza nel file "consumazioni.txt"
  */

void consumazioni(int num_consumazioni,int num_linee,char stringa[]);



/**
 * Questa procedura permette di ordinare, tramite un algoritmo "selection sort", l'array passato alla procedura.
 * E' una procedura generica e riusabile in quanto, a seconda dei parametri attuali che le vengono forniti, ordina
 * oggetti diversi. Se gli oggetti appartengono ad una struct, vengono copiati i campi della struct in array locali ed avviene l'ordinamento di questi array locali.
 *
 * @param array_int, ovvero l'array di interi del quale si deve effettuare l'ordinamento principale
 * @param array_nomi, ovvero l'array dei nomi corrispondenti ai numeri che devono essere ordinati
 * @param num_linee, ovvero il numero di linee di lui e' composto il file che deve essere ordinato
 */

void selection_sort(int array_int[],char array_nomi[CONSUM_MAX][LUNGH_MAX_NOME], int num_linee);



//------------------------------------------------------------------------------------------------------
//PROCEDURE TESTING CUNIT

/**
 * Funzione che introduce il testing con CUnit.
 * E' possibile accedervi selezionando la scelta 5 nel menu' principale.
 * Testa le asserzioni (Test Method) inserite in una o piu' "Test Suite" e ne valuta la verita' o la falsita'.
 * Vi sono diversi tipi di asserzione, a seconda di quale funzione si vuole testare.
 * Le funzioni testate sono "low_conversion", "stampa_stelle" e "isOnlyNumbers".
 * Le asserzioni sono raggruppate in un'unica Test Suite, la quale a sua volta si trova nel Test Registry allocato e deallocato all'inizio del programma.
 *
 *
 * @return CU_get_error();
 */

int testing();

//------------------------------------------------------------------------------------------------------

