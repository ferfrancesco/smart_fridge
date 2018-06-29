#ifndef STRUCTS_H_
#define STRUCTS_H_
#endif /* STRUCTS_H_ */

// Libreria contentente le strutture del programma

#define ALIM_MAX 50  //quantità alimenti massimi inseribile in frigo
#define STEP_MAX 50  //quantità massima di step per ricetta
#define INGR_MAX 50  //quantità max di ingredienti in una ricetta
#define LUNGH_MAX_NOME 50 //Luneghezza massima per il nome di un alimento
#define MAX_RICETTE 50 //Num massimo di ricette salvabili

/*struct menu_settimana();
struct archivio_alimenti[ALIM_MAX];
struct archivio_ricette[MAX_RICETTE];*/

struct menu_settimana{

    char dayname[12];
    char pietanza[50];

}giorno[6];

//struct dati cibo

struct alimento{

    char nome[LUNGH_MAX_NOME];
    char giorno[5];
    char mese[20];
    char anno[6];
    char numero[10];
    char kcal[7];
    char tipo [5];
    char quantita[10];


}archivio_alimenti[ALIM_MAX];

//struct dati ricette

struct ricetta{

    char nome[LUNGH_MAX_NOME];
    char difficolta[5];

    char num_ingredienti[5];   //variabile per determinare il numero di ingredienti
    char ingredienti[INGR_MAX][100]; //[RIGHE] [COLONNE]

    char num_step[5];   //variabile per determinare il numero di step che la ricetta richiede
    char procedura[STEP_MAX][4000];

}archivio_ricette[MAX_RICETTE];

char lista_spesa[50][50];
