#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#define GIORNI_SETTIMANA 7

typedef int bool;
#define true 1
#define false 0

int conta_linee(char nome_file[40]){ //TODO togli funzione perchè inutileee

    int num_linee=0;

    FILE *fp;
    fp = fopen (nome_file,"r");

    if (fp==NULL){													//controllo presenza file
        printf("\n Errore nel caricamento del file");
        exit(1);
    }

    while(!feof(fp)){

        if(fgetc(fp) == '\n')
            num_linee++;  											 //TODO NON ELIMINARE

    }

    fclose(fp);

    return num_linee;
}

//---------------------------------------------------------------------------------------
//OPERAZIONI DI CARICAMENTO DEI FILE

/**
 *Questa funzione conta le linee del file alimenti, se il file esiste,
 *altrimenti riporta un messaggio d'errore nell'apertura del file.
 *Apre automaticamente il file "alimenti.txt" senza aver bisogno di un nome in input
 *
 *@pre Il file "alimenti.txt" deve gia' esistere
 *
 * @return num_linee Se il controllo va a buon fine, la funzione restituirà il numero di linee del file analizzato
 */

int file_load_alimenti(){

    int i=0;
    int num_linee=0;

    FILE *fp;
    fp = fopen ("alimenti.txt","r");

    if (fp==NULL){										//controllo presenza file, se non esiste esce dal programma
        system("cls");
        printf("Errore nel caricamento del file\n");
        system("pause");
        exit(1);
    }

    while(!feof(fp)){								//TODO nella funzione stampa, se il num linee ==1, visualizza : 'il frigo è vuoto'

    	fscanf(fp,"%50[^,],%4[^,],%4[^,],%6[^,],%15[^,],%5[^,],%10[^,],%10[^,],%15[^,],%10[^,],\n",archivio_alimenti[i].nome,archivio_alimenti[i].giorno,archivio_alimenti[i].mese,archivio_alimenti[i].anno,archivio_alimenti[i].numero,archivio_alimenti[i].tipo,archivio_alimenti[i].quantita,archivio_alimenti[i].quantita_tot,archivio_alimenti[i].kcal,archivio_alimenti[i].scaduto);	//utilizzo [^,] in quanto utilizzare %s leggeva l'intera stringa,virgole incluse,

        i++;
        num_linee++;

        if(archivio_alimenti[i-1].giorno[0] == '\0'){   /*controllo se la prima posizione di un array di caratteri (stringa[0]) qualsiasi della struct contiene il carattere speciale \0. Se il carattere è trovato,significa che in realtà
        												 *non è stato caricato nulla,quindi decremento il numero di linee,e quindi di alimenti caricati. Funzione necessaria per il fix di un bug*/
        	i--;
        	num_linee--;

        }

    }

    fclose(fp);

    return num_linee;

}

/**
 *Questa funzione conta le linee del file ricette, se il file esiste,
 *altrimenti riporta un messaggio d'errore nell'apertura del file.
 *Apre automaticamente il file "ricette.txt" senza aver bisogno di un nome in input
 *@pre Il file "ricette.txt" deve gia' esistere
 *
 * @return num_linee Se il controllo va a buon fine, la funzione restituirà il numero di linee del file analizzato
 */

int file_load_ricette(){

    int i=0;
    int j=0;
    int temp_int=0; 								//variabile per la conversione del numero di step da stringa a intero
    int num_linee=0;

    FILE *fp;
    fp = fopen ("ricette.txt","r");

    if (fp==NULL){									//controllo presenza file
        system("cls");
        printf("Errore nel caricamento del file\n");
        system("pause");
        exit(1);
    }

    while(!feof(fp)){

        fscanf(fp,"%50[^,],%5[^,],%5[^,],%5[^,],",archivio_ricette[i].nome,archivio_ricette[i].difficolta,archivio_ricette[i].num_ingredienti,archivio_ricette[i].num_preparazioni); //utilizzo [^,] in quanto utilizzare %s leggeva l'intera stringa,virgole incluse

        temp_int = atoi(archivio_ricette[i].num_ingredienti);

        for(j=0;j<temp_int;j++){					//acquisizione degli ingredienti per ogni ricetta, un incremento della j indica un ingrediente

            fscanf(fp,"%100[^,],",archivio_ricette[i].ingredienti[j]);

        }

        fscanf(fp,"%5[^,],",archivio_ricette[i].num_step);

        temp_int = atoi(archivio_ricette[i].num_step);

        for(j=0;j<temp_int;j++){

            fscanf(fp,"%4000[^,],\n",archivio_ricette[i].procedura[j]);

        }

       i++;											//incremento della i per il ciclo while
       num_linee++;

       if(archivio_ricette[i-1].num_ingredienti[0] == '\0'){   /*controllo se la prima posizione di un array di caratteri (stringa[0]) qualsiasi della struct contiene il carattere speciale \0. Se il carattere è trovato,significa che in realtà
       												 *non è stato caricato nulla,quindi decremento il numero di linee,e quindi di alimenti caricati. Funzione necessaria per il fix di un bug*/
       	i--;
       	num_linee--;

       }

    }

    fclose(fp);

    return num_linee;

}

/**
 *Questa funzione conta le linee del file menu settimanale, se il file esiste,
 *altrimenti riporta un messaggio d'errore nell'apertura del file.
 *Apre automaticamente il file "menu_sett.txt" senza aver bisogno di un nome in input
 *
 *@pre Il file "menu_sett.txt" deve gia' esistere
 *
 * @return num_linee Se il controllo va a buon fine, la funzione restituirà il numero di linee del file analizzato
 */

int file_load_menu_sett(){

    int i;
    int num_linee=conta_linee("menu_sett.txt");

    FILE *fp;
    fp = fopen ("menu_sett.txt","r");

    if (fp==NULL){									//controllo presenza file
        printf("\n Errore nel caricamento del file");
        exit(1);
    }

    while(!feof(fp)){

        for	(i=0;i<GIORNI_SETTIMANA;i++){

            fscanf(fp,"%s\n",giorno[i].pietanza);

        }

    }

    fclose(fp);

    return num_linee;

}

/**
 *Questa funzione conta le linee del file lista della spesa, se il file esiste,
 *altrimenti riporta un messaggio d'errore nell'apertura del file.
 *Apre automaticamente il file "lista_spesa.txt" senza aver bisogno di un nome in input
 *
 *@pre Il file "lista_spesa.txt" deve gia' esistere
 *
 * @return num_linee Se il controllo va a buon fine, la funzione restituirà il numero di linee del file analizzato
 */

int file_load_lista(int num_linee){ //TODO CONTROLLA

    int i;

    FILE *fp;
    fp = fopen ("lista_spesa.txt","r");

    if (fp==NULL){								//controllo presenza file
        printf("\n Errore nel caricamento del file");
        exit(1);
    }

    //while(!feof(fp)){							//TODO controlla

    for	(i=0;i<num_linee;i++){

        fscanf(fp,"%[^,]\n",lista_spesa[i]);	//utilizzo [^,] in quanto utilizzare %s leggeva l'intera stringa,virgole incluse

    }

    fclose(fp);

    return num_linee;

}
/**
 * Questa funzione permette di caricare nel programma il file "consumazioni.txt", all'attivarsi del sottomenù della categoria "alimenti"
 * @return num_linee, ovvero il numero di linee di cui il file "consumazioni.txt" è composto
 */
int file_load_consumazioni(){

	int i=0;
	int num_linee=0;

    FILE *fp;
    fp = fopen ("consumazioni.txt","r");

    if (fp==NULL){								//controllo presenza file
        printf("\n Errore nel caricamento del file");
        exit(1);
    }

    while(!feof(fp)){

        fscanf(fp,"%50[^,],%10[^,],\n",archivio_consumazioni[i].nome,archivio_consumazioni[i].consumazioni);	//utilizzo [^,] in quanto utilizzare %s leggeva l'intera stringa,virgole incluse
        i++;
        num_linee++;

        if(archivio_consumazioni[i-1].nome[0] == '\0'){   /*controllo se la prima posizione di un array di caratteri (stringa[0]) qualsiasi della struct contiene il carattere speciale \0. Se il carattere è trovato,significa che in realtà
        												 *non è stato caricato nulla,quindi decremento il numero di linee,e quindi di alimenti caricati. Funzione necessaria per il fix di un bug*/
        	i--;
        	num_linee--;

        }

    }

    fclose(fp);

    return num_linee;


}


//OPERAZIONI DI SALVATAGGIO DEI FILE

/**
 * Questa procedura riceve in input il numero di linee del file "alimenti.txt" e lo stesso viene aperto in scrittura.
 * Salva sul file eventuali modifiche apportate.
 *
 * @param num_linee La procedura riceve in input il numero di linee del file, derivanti dalla precedente lettura dello stesso.
 */

void file_save_alimenti(int num_linee){

    FILE *fp;
    int i;

    fp = fopen ("alimenti.txt","w"); 					//apro il file per aggiungere elementi

    for(i=0;i<num_linee;i++){

    	fprintf(fp,"%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,\n",archivio_alimenti[i].nome,archivio_alimenti[i].giorno,archivio_alimenti[i].mese,archivio_alimenti[i].anno,archivio_alimenti[i].numero,archivio_alimenti[i].tipo,archivio_alimenti[i].quantita,archivio_alimenti[i].quantita_tot,archivio_alimenti[i].kcal,archivio_alimenti[i].scaduto);

    }

    fclose(fp);
}

/**
 * Questa procedura riceve in input il numero di linee del file "ricette.txt" e lo stesso viene aperto in scrittura.
 * Salva sul file eventuali modifiche apportate.
 *
 * @param num_linee La procedura riceve in input il numero di linee del file, derivanti dalla precedente lettura dello stesso.
 */

void file_save_ricette (int num_linee){

    FILE *fp;
    int i=0;
    int j=0;
    int temp_int=0;										//variabile che contiene il numero di step di una ricetta

    fp = fopen ("ricette.txt","w");  					//apro il file per aggiungere elementi

    for(i=0;i<num_linee;i++){

        fprintf(fp,"%s,%s,%s,%s,",archivio_ricette[i].nome,archivio_ricette[i].difficolta,archivio_ricette[i].num_ingredienti,archivio_ricette[i].num_preparazioni);

        temp_int = atoi(archivio_ricette[i].num_ingredienti);  //converto il numero di step in intero per l'uso nel ciclo

        for(j=0;j<temp_int;j++){

            fprintf(fp,"%s,",archivio_ricette[i].ingredienti[j]);  //acquisizione degli ingredienti

        }

        fprintf(fp,"%s,",archivio_ricette[i].num_step);

        temp_int = atoi(archivio_ricette[i].num_step);

        for(j=0;j<temp_int;j++){

            fprintf(fp,"%s,",archivio_ricette[i].procedura[j]);

        }

        fprintf(fp,"\n");
    }

    fclose(fp);

}

/**
 * Questa procedura salva il menu settimanale.
 *
 * Non effettua alcun controllo sulla previa esistenza del file, semplicemente sovrascrive l'intero menu settimanale qualora venisse chiesto di salvarlo
 *
 *
 */

void file_save_menu_sett(){

    FILE *fp;
    int i;

    fp = fopen ("menu_sett.txt","w");

    for(i=0;i<GIORNI_SETTIMANA;i++){

        fprintf(fp,"%s\n",giorno[i].pietanza);

    }

    fclose(fp);

}
//todo aspetta
void file_append_lista(char stringa[]){

    FILE *fp;
    fp = fopen ("lista_spesa.txt","a");

    fprintf(fp,"%s,\n",stringa);

    fclose(fp);
}

/**
 * Questa procedura permette di salvare le modifiche apportate al file "consumazioni.txt".
 *
 * @param num_linee,ovvero il numero di linee di cui è composto il file "consumazioni.txt"
 */
void file_save_consumazioni(int num_linee){

	int i;

    FILE *fp;
    fp = fopen ("consumazioni.txt","w");

    if (fp==NULL){								//controllo presenza file
        printf("\n Errore nel caricamento del file");
        exit(1);
    }

    for(i=0;i<num_linee;i++){

        fprintf(fp,"%s,%s,\n",archivio_consumazioni[i].nome,archivio_consumazioni[i].consumazioni);

    }

    fclose(fp);

}


