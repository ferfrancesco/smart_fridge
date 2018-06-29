#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "structs.h"
#include "alimenti.h"
#include "ricette.h"
#include "varie.h"

//inclusione valori bool
typedef int bool;
#define true 1
#define false 0

/**
 * Questa funzione verifica che una data stringa contenga solo numeri.
 *
 * @pre deve essere inserita una stringa che indica la data di scadenza di un dato prodotto
 * @post viene restituito un valore booleano, o vero o falso (che corrispondono rispettivamente ad un 1 o ad uno 0)
 */
int isOnlyNumbers(char* stringa){

    int i;
    int numero;

    for(i=0;i<strlen(stringa);i++){

        if(isdigit(stringa[i])==false){

            return true;

        }

        else if(isdigit(stringa[i])==true){

            return false;

        }

    }

}

/**
 * Questa procedura stampa un messaggio di errore, utile in diverse funzioni
 *
 */

void messaggio_errore(){

    system("cls");
    printf("Selezione Errata.Inserire una cifra numerica (1,2,3,4,...)\n");
    system("pause");
    fflush(stdin);

}

/**
 * Questa procedura copia i nomi dei giorni della settimana nella struct "giorno"
 */

void dayname_fill(){

    strcpy(giorno[0].dayname,"Lunedi'");
    strcpy(giorno[1].dayname,"Martedi'");
    strcpy(giorno[2].dayname,"Mercoledi'");
    strcpy(giorno[3].dayname,"Giovedi'");
    strcpy(giorno[4].dayname,"Venerdi'");
    strcpy(giorno[5].dayname,"Sabato");
    strcpy(giorno[6].dayname,"Domenica");

}

/**
 * Questa procedura stampa il menu principale dello Smart Fridge.
 *
 */

void stampa_menu(){

    int menu_select=0;

    time_t orario;
    char* stringa_ora;

    orario = time(NULL);

    /* Convert to local time format. */
    stringa_ora = ctime(&orario);

    fflush(stdin);		//termina lo stream di scanf
    system("cls");

    printf("Benvenuto nel tuo Smart Fridge\n");

    printf("%s",stringa_ora);

    printf("\n\nSeleziona una categoria\n\n1)Alimenti\n2)Ricette\n3)Varie\n4)Spegni il sistema\n\n");

    //memos();

    scanf("%d",&menu_select);

    switch(menu_select){

        case 1:
            alimenti();
            break;

        case 2:
            ricette();
            break;

        case 3:
            varie();
            break;

        case 4:
            exit(1);
            break;

        default:
            messaggio_errore();
            stampa_menu();
            break;
    }

}

/**
 * Procedura che stampa eventuali promemoria inseriti nello Smart Fridge
 *
 */
void memos(){

    printf("\n\n---------------------------------------------\n\nSEZIONE MEMOS");
}

void scadenze(int num_linee){

	int anno_int;          //conversione in int dell'anno di scadenza dell'alimento
	int mese_int;		   //conversione in int del mese di scadenza dell'alimento
	int giorno_int;		   //conversione in int del giorno di scadenza dell'alimento

	int anno_attuale;   //variabile in cui salvare l'anno attuale (a cui poi dover aggiungere 1900)
	int i;

	//Acquisisco l'orario e lo memorizzo nella struct tm
    time_t rawtime;
    struct tm *info;

    time(&rawtime);
    info = gmtime(&rawtime );

    anno_attuale=info->tm_year;

    anno_attuale=anno_attuale + 1900; //aggiungo 1900 perchè la libreria esterna inizia a contare da 0,ignorando ben 1900 anni.Senza l'addizione,risulterebbe come anno attuale il 118,e non 2018 (2018=1900+118)


    for(i=0;i<num_linee;i++){

    	anno_int=atoi(archivio_alimenti[num_linee].anno);
    	mese_int=atoi(archivio_alimenti[num_linee].mese);
    	giorno_int=atoi(archivio_alimenti[num_linee].giorno);


        if(anno_int<anno_attuale){


        }

        if(anno_int==anno_attuale && mese_int-1<info->tm_mon){  //shift di -1 per il mese,in quanto tm_mon è un array da 0 a 11

        	printf("\n----------------------------------------------------------------------");
        	printf("\nATTENZIONE!");
        	printf("\n----------------------------------------------------------------------");

        	printf("\nHai inserito un alimento gia' scaduto.L'inserimento e' stato annullato.\nE' consigliato cestinare questo alimento\n\n");
        	system("pause");
        	alimenti();

        }

        if(anno_int==anno_attuale && mese_int-1==info->tm_mon && giorno_int<info->tm_mday){  //shift di -1 per il mese,in quanto tm_mon è un array da 0 a 11

        	printf("\n----------------------------------------------------------------------");
        	printf("\nATTENZIONE!");
        	printf("\n----------------------------------------------------------------------");

        	printf("\nHai inserito un alimento gia' scaduto.L'inserimento e' stato annullato.\nE' consigliato cestinare questo alimento\n\n");
        	system("pause");
        	alimenti();

        }


    }

}

