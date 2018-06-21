#ifndef OPERAZIONI_FILE_H_
#define OPERAZIONI_FILE_H_
#endif /* OPERAZIONI_FILE_H_ */

/* Libreria contenente funzioni per operazioni su file,quali apertura,salvataggio,modifica,
e conversione di spazi in tratti bassi per il salvataggio come CSV file e viceversa*/

#include <stdio.h>
#include <stdlib.h>

int conta_linee(char nome_file[40]);  //conta quante linee sono presenti in un determinato file
void to_und_conversion(char stringa[]); //funzione di conversione da spazio a _ ,utile per il salvataggio su file
void to_space_conversion(char stringa[]); //Viceversa di quanto scritto sopra ^

//PROCEDURE DI CARICAMENTO DA FILE
int file_load_alimenti();
int file_load_ricette();
int file_load_menu_sett();
int file_load_lista(int num_linee);

//PROCEDURE DI SALVATAGGIO SU FILE
void file_save_menu_sett();
void file_save_alimenti(int num_linee);
void file_save_ricette (int num_linee);
