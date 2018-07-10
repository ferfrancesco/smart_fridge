#ifndef STRUCTS_H_
#define STRUCTS_H_
#endif /* STRUCTS_H_ */

// Libreria contentente le strutture del programma

#define ALIM_MAX 50  //quantità alimenti massimi inseribile in frigo
#define CONSUM_MAX 100
#define STEP_MAX 50  //quantità massima di step per ricetta
#define INGR_MAX 50  //quantità max di ingredienti in una ricetta
#define LUNGH_MAX_NOME 50 //Luneghezza massima per il nome di un alimento
#define MAX_RICETTE 50 //Num massimo di ricette salvabili
#define MAX_LISTA 50

/**
 * Struct che definisce ogni singola pietanza del menu settimanale,
 * contrassegnata da nome del piatto stesso e dal giorno della settimana in cui
 * si e' consumato o si intende consumarlo
 */

struct menu_settimana{
	/// nome del giorno della settimana
    char dayname[12];
    /// nome del piatto
    char pietanza[2][LUNGH_MAX_NOME];

}giorno[6];

/**
 * Struct che definisce ogni singolo alimento presente nello Smart Fridge
 */

struct alimento{
	///nome dell'alimento
    char nome[LUNGH_MAX_NOME];

    ///giorno di scadenza dell'alimento
    char giorno[4];

    ///mese di scadenza dell'alimento
    char mese[4];

    ///anno di scadenza dell'alimento
    char anno[6];

    ///numero di confezioni di un alimento presente nello Smart Fridge
    char numero[10];

    ///calorie di un dato alimento
    char kcal[7];

    ///tipo di un alimento (ovvero liquido o solido)
    char tipo [5];

    ///quantita' di un dato alimento
    char quantita[10];

    ///quantità totale di un alimento presente nello Smart Fridge
    char quantita_tot[10];

    ///flag che indica se un alimento presente nello Smart Fridge è scaduto oppure no
    char scaduto[10];

}archivio_alimenti[ALIM_MAX];

struct consumazioni{

	///nome dell'alimento
    char nome[LUNGH_MAX_NOME];

    ///numero di volte in cui un certo alimento è stato consumato
    char consumazioni[10];

    int consumazioni_int;

}archivio_consumazioni[CONSUM_MAX],archivio_cons_ordinato[CONSUM_MAX];

/**
 * Struct che definisce ogni singola ricetta presente nella lista inserita nello Smart Fridge
 */

struct ricetta{
	///nome ricetta
    char nome[LUNGH_MAX_NOME];

    ///difficolta' (da 1 a 5)
    char difficolta[5];

    ///numero di ingredienti
    char num_ingredienti[5];

    ///[numero max ingredienti] [nome ciascun ingrediente]
    char ingredienti[INGR_MAX][100];

    ///numero di step che la ricetta richiede
    char num_step[5];

    ///[numero step] [descrizione ciascuno step]
    char procedura[STEP_MAX][4000];

    ///numero di volte in cui una ricetta è stata preparata
    char num_preparazioni[5];

    ///kcal di una ricetta
    char kcal[10];


}archivio_ricette[MAX_RICETTE];

/**
 * Rappresenta la lista della spesa, con [ numero di ingrediente ]
 * e [nome dell'alimento]
 *
 */

char lista_spesa[MAX_LISTA][LUNGH_MAX_NOME];

