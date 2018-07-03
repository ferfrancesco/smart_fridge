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

int file_load_lista(int num_linee); //TODO commenta dopo che la funzione viene controllata

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
 * @param num_linee,ovvero il numero di linee di cui il file e' composto
 */
void file_save_ricette (int num_linee);


//provaa
void file_append_lista(char stringa[]);
