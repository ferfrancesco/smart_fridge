#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "operazioni_file.h"
#include "alimenti.h"
#include "altre_procedure.h"
#include "ricette.h"
#include "varie.h"


#define ALIM_MAX 50  								//quantità massima alimenti presenti in frigo
#define STEP_MAX 50  								//numero massimo di step per ricetta
#define INGR_MAX 50  								//numero massimo di ingredienti per ricetta
#define LUNGH_MAX_NOME 50 							//lunghezza massima stringa per il nome di un alimento

int main(int argc, char *argv[]) {


	int num_linee=file_load_alimenti();
	scadenze(num_linee);

    dayname_fill(); 								//inizializzazione giorni della settimana per il menù settimanale
    stampa_menu();									//stampa del menù di scelta principale del programma

    return 0;
}
