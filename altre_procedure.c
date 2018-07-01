#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "alimenti.h"
#include "ricette.h"
#include "varie.h"

//inclusione valori bool
typedef int bool;
#define true 1
#define false 0

#define SOGLIA_SCADENZA 3

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

    //fflush(stdout);
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
	int flag_scadenza=0;	//valore flag per indicare se ci sono alimenti in scadenza
	int i;

	int tot_giorni_anno=0; //variabile per salvare il numero del giorno in cui scade l'alimento,da 0 a 365
	int giorni1;		   //variabile di appoggio per il controllo della scadenza nel caso di alimenti che scadono l'anno dopo (solo nel caso di (Dicembre 20XX) -> (Gennaio 20XX+1)
	int giorni2;		   //variabile di appoggio per il controllo della scadenza nel caso di alimenti che scadono l'anno dopo (solo nel caso di (Dicembre 20XX) -> (Gennaio 20XX+1)


	//Acquisisco l'orario e lo memorizzo nella struct tm
    time_t rawtime;
    struct tm *info;

    time(&rawtime);
    info = gmtime(&rawtime );

    anno_attuale=info->tm_year;

    anno_attuale=anno_attuale + 1900; //aggiungo 1900 perchè la libreria esterna inizia a contare da 0,ignorando ben 1900 anni.Senza l'addizione,risulterebbe come anno attuale il 118,e non 2018 (2018=1900+118)

    printf("\n-----------------------------------------------------------");
    printf("\nALIMENTI IN SCADENZA");
    printf("\n-----------------------------------------------------------");

    for(i=0;i<num_linee;i++){

    	anno_int=atoi(archivio_alimenti[i].anno);
    	mese_int=atoi(archivio_alimenti[i].mese);
    	giorno_int=atoi(archivio_alimenti[i].giorno);

    	tot_giorni_anno=0;

    	//in base al mese di scadenza dell'alimento,sommo il numero di giorni dei mesi precedenti
    	//Es. Marzo(case 3) equivale alla somma  dei giorni di Gennaio (31) e Febbraio (28) = 59 , + i giorni del mese stesso
    	//Quindi,se avremo un alimento che scade il 10 Marzo,avremo che il contatore totale dei giorni dell'anno ammonterà a 69.
    	//Questo numero sarà poi utilizzato per il controllo di scadenza,dove confronterò i giorni di scadenza del cibo,con i giorni attualmente passati dall'inizio dell'anno


    	switch(mese_int){

    		case 1:

    			tot_giorni_anno=giorno_int;

    		break;

    		case 2:

    			tot_giorni_anno=31+giorno_int;

    		break;

    		case 3:

    			tot_giorni_anno=59+giorno_int;

    		break;

    		case 4:

    			tot_giorni_anno=90+giorno_int;

    		break;

    		case 5:

    			tot_giorni_anno=120+giorno_int;

    		break;

    		case 6:

    			tot_giorni_anno=151+giorno_int;

    		break;

    		case 7:

    			tot_giorni_anno=181+giorno_int;

    		break;

    		case 8:

    			tot_giorni_anno=212+giorno_int;

    		break;

    		case 9:

    			tot_giorni_anno=243+giorno_int;

    		break;

    		case 10:

    			tot_giorni_anno=273+giorno_int;

    		break;

    		case 11:

    			tot_giorni_anno=304+giorno_int;

    		break;

    		case 12:

    			tot_giorni_anno=334+giorno_int;

    		break;

    	}

    	if((anno_attuale==anno_int) && (tot_giorni_anno-SOGLIA_SCADENZA<=info->tm_yday)){

    		flag_scadenza=1; //indica che c'è effettivamente cibo in scadenza

            printf("\n%s",archivio_alimenti[i].nome);

            //printf("Potresti cucinare:%s",);

    	}

    	//controllo della scadenza nel caso di alimenti che scadono l'anno dopo (solo nel caso di (Dicembre 20XX) -> (Gennaio 20XX+1)

    	//ALGORITMO
    	//[(N.Giorni_Anno - Giorno_attuale) + Giorno_di_scadenza] < Soglia_di_scadenza

    	//Se il risultato dell'operazione fra le parentesi è minore della soglia di scadenza,l'alimento è in scadenza

    	if ((anno_attuale<anno_int)  && (mese_int==1) && (((364-info->tm_yday)+tot_giorni_anno)<=SOGLIA_SCADENZA)){

        		flag_scadenza=1; //indica che c'è effettivamente cibo in scadenza

                printf("\n%s",archivio_alimenti[i].nome);

                //printf("Potresti cucinare:%s",);

    		}

    	}


    if(flag_scadenza==0){

    	printf("\nNessun alimento in scadenza\n\n");
    }

}

