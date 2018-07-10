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
#include "CUnit/Basic.h"

int main() {
/*
	int num_linee;
	char nomi_temp[CONSUM_MAX][LUNGH_MAX_NOME];
	int valori_ordinare[CONSUM_MAX];
	int i;

	num_linee=file_load_ricette();

	for(i=0;i<num_linee;i++){

		valori_ordinare[i]=atoi(archivio_ricette[i].kcal);  //converto i valori da ordinare da char a int
		strcpy(nomi_temp[i],archivio_ricette[i].nome);

	}

	selection_sort(valori_ordinare,nomi_temp,num_linee);*/


    stampa_menu();									//stampa del menù di scelta principale del programma

    return 0;
}
