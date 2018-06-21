#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "operazioni_file.h"
#include "operazioni_varie.h"
#include "alimenti.h"
#include "ricette.h"
#include "varie.h"

#define ALIM_MAX 50  //quantità alimenti massimi inseribile in frigo
#define STEP_MAX 50  //quantità massima di step per ricetta
#define INGR_MAX 50  //quantità max di ingredienti in una ricetta
#define LUNGH_MAX_NOME 50 //Luneghezza massima per il nome di un alimento

int main(int argc, char *argv[]) {

    dayname_fill(); //inizializzo la struct con i nomi dei giorni della settimana,da utilizzare poi nel menu' della settimana

    stampa_menu();

    return 0;
}
