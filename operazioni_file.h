 /**
 * @file operazioni_file.h
 *
 * Questa libreria contiene procedure relative al caricamento, al salvataggio e alla modifica
 * dei vari file CSV utili all'interno del programma.
 *
 * @authors Francesco Ferrara & Alessia Laforgia
 *
 */

#ifndef OPERAZIONI_FILE_H_
#define OPERAZIONI_FILE_H_
#endif /* OPERAZIONI_FILE_H_ */

#include <stdio.h>
#include <stdlib.h>

/**
 * Questa funzione permette di contare le linee di cui un file e' composto.
 *
 * @param nome_file, ovvero il nome del file di cui bisogna contare il numero di linee.
 * @return num_linee, il numero di linee di cui il file e' composto
 */
int conta_linee(char nome_file[40]);  //conta quante linee sono presenti in un determinato file

//PROCEDURE DI CARICAMENTO DA FILE
/**
 * Questa funzione carica la lista degli alimenti nel programma.
 *
 * @return num_linee, ovvero il numero di linee di cui il file e' composto
 */
int file_load_alimenti();

/**
 * Questa funzione carica la lista delle ricette nel programma.
 *
 * @return num_linee, ovvero il numero di linee di cui il file e' composto
 */
int file_load_ricette();

/**
 * Questa funzione carica il menu settimanale nel programma.
 *
 * @return num_linee, ovvero il numero di linee di cui il file e' composto
 */
int file_load_menu_sett();

/**
 * Questa procedura carica nello Smart Fridge il file "lista_spesa.txt"
 *
 * @param num_linee,ovvero il numero di linee di cui e' composto il file "lista_spesa.txt" al momento del caricamento
 *
 * @return num_linee, ovvero il numero di linee del file "lista_spesa.txt" aggiornato
 */
int file_load_lista(int num_linee); //TODO commenta dopo che la funzione viene controllata

/**
 * Questa procedura permette di caricare il file "consumazioni.txt" all'interno dello Smart Fridge.
 *
 * @return num_linee, ovvero il numero di linee di cui e' composto il file "consumazioni.txt"
 */
int file_load_consumazioni();

//PROCEDURE DI SALVATAGGIO SU FILE

/**
 * Procedura che salva il menu settimanale.
 */
void file_save_menu_sett();

/**
 * Procedura che salva il file alimenti, dopo eventuali modifiche apportate.
 *
 * @param num_linee,ovvero il numero di linee di cui il file e' composto
 */
void file_save_alimenti(int num_linee);

/**
 * Procedura che salva il file ricette, dopo eventuali modifiche apportate.
 *
 * @param num_linee,ovvero il numero di linee di cui il file "ricette.txt" e' composto
 */
void file_save_ricette (int num_linee);


/**
 * Questa procedura serve ad aggiungere stringhe in append ad un determinato file, in questo caso "lista_spesa.txt"
 *
 * @param stringa, ovvero la stringa da aggiungere in coda al file
 */
void file_append_lista(char stringa[]);

/**
 * Procedura che salva il file "consumazioni.txt", dopo eventuali modifiche apportate.
 *
 * @param num_linee,ovvero il numero di linee di cui il file "consumazioni.txt" e' composto
 */
void file_save_consumazioni(int num_linee);
