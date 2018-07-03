#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "operazioni_file.h"
#include "alimenti.h"
#include "ricette.h"
#include "altre_procedure.h"

typedef int bool;
#define true 1
#define false 0

#define SOGLIA_SCADENZA 3  //Un alimento risultera' in scadenza quando il suo giorno di scadenza di stanzier� di SOGLIA_SCADENZA dal giorno attuale
#define SOGLIA_LISTA 2     //Soglia sotto al quale un alimento verr� inserito nella lista della spesa
#define INGR_MAX 50  //quantit� max di ingredienti in una ricetta

int num_linee;

/**
La procedura rappresenta il menu degli alimenti. In base alla scelta che viene inserita, si hanno possibilit� diverse:

1) Attiva la procedura stampa_alimenti;

2) Attiva la procedura aggiunta_alimenti;

3) Attiva la procedura modifica_alimenti;

4) Torna al menu principale;

 *
 */

void alimenti(){

    int menu_select=0;

    num_linee=file_load_alimenti();

    fflush(stdin);
    system("cls");

    printf("Menu' Alimenti\nSeleziona un opzione\n\n1)Visualizza alimenti presenti in frigo\n2)Aggiungi un alimento\n3)Modifica le quantita' presenti\n4)Torna al menu'\n\n");

    scadenze(num_linee);

    scanf("%d",&menu_select);

    switch(menu_select){

        case 1:

            stampa_alimenti(num_linee);
            system("pause");
            fflush(stdin);
            alimenti();

        break;

        case 2:

        	aggiunta_alimenti(num_linee);
            alimenti();

        break;

        case 3:

            stampa_alimenti(num_linee);
            modifica_alimenti(num_linee);
            alimenti();

        break;

        case 4:

        	stampa_menu();

        break;

        default:

        	messaggio_errore();
            alimenti();

        break;


    }

}

/**
 * la procedura stampa gli alimenti presenti nel frigo e, in caso di assenza di alimenti, stampa
 * "il frigo e' vuoto"
 *
 * @param num_linee Contiene il numero di linee del file "alimenti.txt" che viene caricato nel programma
 *
 * @pre num_linee Il file e' gia' esistente al momento dell'accesso alla sezione "alimenti"
 *
 *
 */

void stampa_alimenti(int num_linee){


    fflush(stdin);
    system("cls");
    int i;
    char temp_quantita[10]; 	//stringa in cui � memorizzata l'unit� di misura dell'alimento( "g" o "ml")

    if (num_linee==0){

        printf("Il frigo e' vuoto!\n\n");

    }

    else{

        printf("Elenco degli alimenti presenti in frigo\n\n|%-50s|%-12s|%-10s|%-10s|%-7s|","Alimento","Scadenza","Numero","Quantita'","KCAL");  //il valore negativo serve per l'allineamento a sinistra
        printf("\n----------------------------------------------------------------------------------------------");

        for(i=0;i<num_linee;i++){

            if(strcmp(archivio_alimenti[i].tipo,"1")){

                strcpy(temp_quantita,archivio_alimenti[i].quantita);
                strcat(temp_quantita," ml");

                printf("\n|%-50s|%-s/%-s/%-6s|%-10s|%-10s|%-7s|%d)",archivio_alimenti[i].nome,archivio_alimenti[i].giorno,archivio_alimenti[i].mese,archivio_alimenti[i].anno,archivio_alimenti[i].numero,temp_quantita,archivio_alimenti[i].kcal,i+1);

            }

            else if(strcmp(archivio_alimenti[i].tipo,"2")){

                strcpy(temp_quantita,archivio_alimenti[i].quantita);
                strcat(temp_quantita," g");

                printf("\n|%-50s|%-2s/%-2s/%-6s|%-10s|%-10s|%-7s|%d)",archivio_alimenti[i].nome,archivio_alimenti[i].giorno,archivio_alimenti[i].mese,archivio_alimenti[i].anno,archivio_alimenti[i].numero,temp_quantita,archivio_alimenti[i].kcal,i+1);

            }

        }

        printf("\n----------------------------------------------------------------------------------------------\n\n");

    }

}

/**
 * La procedura permette di inserire nuovi alimenti.
   E' possibile effettuare una scelta interna:

		1- Se l'alimento � solido, e le sue quantit� si misurano in grammi.
		2- Se l'alimento � liquido e si misura in millilitri.

 * @param num_linee riceve in input il numero di linee di cui e' composto il file
 */

void aggiunta_alimenti(int num_linee){

	int i;
    int anno_int;		//variabile temporanea per la conversione in int della stringa anno
	int mese_int;		//variabile temporanea per la conversione in int della stringa mese
    int giorno_int;		//variabile temporanea per la conversione in int della stringa giorno
    int tipo_int; 		//variabile di appoggio per la scelta dell'unit� di misura dell'alimento
    int anno_attuale;   //variabile in cui salvare l'anno attuale (a cui poi dover aggiungere 1900)

    char selezione[10];	//stringa per memorizzare il numero di alimenti che si vogliono inserire
    int selezione_int; 	//variabile in cui � memorizzato il numero di alimenti che si vogliono inserire (case1), il numero dell'alimento che si vuole modificare( case3)

    system("cls");
    printf("Quanti alimenti vuoi aggiungere?Inserire un valore numerico\n\n");

    fflush(stdin);

    gets(selezione);

    if(isOnlyNumbers(selezione)==true) {

    	messaggio_errore();
        alimenti();

    }

    else if (isOnlyNumbers(selezione)==false){

        selezione_int=atoi(selezione);
    }

    for(i=0;i<selezione_int;i++){

        system("cls");
        fflush(stdin);

        printf("Inserire il nome dell'alimento:");
        gets(archivio_alimenti[num_linee].nome);

        printf("\nInserire il numero di confezioni o elementi dell'alimento inserito:");
        gets(archivio_alimenti[num_linee].numero);

		if(isOnlyNumbers(archivio_alimenti[num_linee].numero)==true){

			messaggio_errore();
			alimenti();
		}

        printf("\nInserire la tipologia di misura dell'alimento:\n\n1)Solido [GRAMMI]\n2)Liquido [MILLILITRI]\n\n");
        gets(archivio_alimenti[num_linee].tipo);

		if(isOnlyNumbers(archivio_alimenti[num_linee].tipo)==true){

			messaggio_errore();
			alimenti();
		}

        tipo_int = atoi(archivio_alimenti[num_linee].tipo);

        switch(tipo_int){

            case 1:

                printf("\nQual e' la quantita' in g del singolo elemento?[GRAMMI]:"); //TODO inserire controllo su input numerico
                gets(archivio_alimenti[num_linee].quantita);

                break;

            case 2:

                printf("\nQual e' la quantita' in ml del singolo elemento?[MILLILITRI]:"); //TODO inserire controllo su input numerico
                gets(archivio_alimenti[num_linee].quantita);

                break;

        }

        printf("\nInserire le KCAL dell'alimento:");
        gets(archivio_alimenti[num_linee].kcal);

		if(isOnlyNumbers(archivio_alimenti[num_linee].kcal)==true){

			messaggio_errore();
			alimenti();
		}

		system("cls");

    	//--------------------------------------------------------------------------
        //CONTROLLO INSERIMENTO DATE (SCADENZA)

        do {

    		printf("Inserisci il giorno di scadenza:");
    		gets(archivio_alimenti[num_linee].giorno);

    		printf("\n");

    		if(isOnlyNumbers(archivio_alimenti[num_linee].giorno)==true){

    			messaggio_errore();
    			alimenti();
    		}

    		giorno_int=atoi(archivio_alimenti[num_linee].giorno);

    		if (giorno_int <1 || giorno_int >31) {

    			printf("Giorno inesistente! Reinserire il giorno\n");
    			system("pause");
    			printf("\n\n");
    		}

    	} while(giorno_int <1 || giorno_int >31);


    	if (giorno_int==31) {

    		do {

    			system("cls");

    			printf("Inserisci mese di scadenza scegliendo fra i seguenti\n\n");

    			printf("1-Gennaio\n3-Marzo\n5-Maggio\n7-Luglio\n8-Agosto\n10-Ottobre\n12-Dicembre\n\n");

    			gets(archivio_alimenti[num_linee].mese);

        		if(isOnlyNumbers(archivio_alimenti[num_linee].mese)==true){

        			messaggio_errore();
        			alimenti();
        		}

        		mese_int=atoi(archivio_alimenti[num_linee].mese);

        		if(mese_int==2 || mese_int==4 || mese_int==6|| mese_int==9||mese_int==11) {

        			printf("\n\nHai scelto un mese non valido,riprovare\n");
        			system("pause");
        		}

    		} while (mese_int==2 || mese_int==4 || mese_int==6|| mese_int==9||mese_int==11);

    	}

    	else if (giorno_int==30|| giorno_int==29) {

    		do {

    			system("cls");

    			printf("Inserisci mese di scadenza scegliendo fra i seguenti\n\n");

    			printf("1-Gennaio\n3-Marzo\n4-Aprile\n5-Maggio\n6-Giugno\n7-Luglio\n8-Agosto\n9-Settembre\n10-Ottobre\n11-Novembre\n12-Dicembre\n\n");

    			gets(archivio_alimenti[num_linee].mese);

        		if(isOnlyNumbers(archivio_alimenti[num_linee].mese)==true){

        			messaggio_errore();
        			alimenti();
        		}

        		mese_int=atoi(archivio_alimenti[num_linee].mese);

    			if (mese_int==2) {

    				printf("\nHai scelto un mese non valido,riprovare\n");
    				system("pause");

    			}

    		} while (mese_int==2);

    	}

    	else

    		do {

       			printf("Inserisci mese di scadenza scegliendo fra i seguenti\n\n");

        		printf("1-Gennaio\n2-Febbraio\n3-Marzo\n4-Aprile\n5-Maggio\n6-Giugno\n7-Luglio\n8-Agosto\n9-Settembre\n10-Ottobre\n11-Novembre\n12-Dicembre\n\n");

        		gets(archivio_alimenti[num_linee].mese);

            	if(isOnlyNumbers(archivio_alimenti[num_linee].mese)==true){

            		messaggio_errore();
            		alimenti();
            	}


            mese_int=atoi(archivio_alimenti[num_linee].mese);

    		if  (mese_int < 1 || mese_int > 12) {

    			printf("Il mese inserito non esiste,riprovare\n");
    			system("pause");
    			system("cls");

    		}

    	} while (mese_int < 1 || mese_int > 12);


    	printf("\nInserire l' anno di scadenza:");
    	gets(archivio_alimenti[num_linee].anno);

		if(isOnlyNumbers(archivio_alimenti[num_linee].anno)==true){

			messaggio_errore();
			alimenti();
		}

		anno_int=atoi(archivio_alimenti[num_linee].anno);

		//--------------------------------------------------------------------------
		//CONTROLLO SCADENZA

		//Acquisisco l'orario e lo memorizzo nella struct tm
	    time_t rawtime;
	    struct tm *info;

	    time(&rawtime);
	    info = gmtime(&rawtime );

	    anno_attuale=info->tm_year;

	    anno_attuale=anno_attuale + 1900; //aggiungo 1900 perch� la libreria esterna inizia a contare da 0,ignorando ben 1900 anni.Senza l'addizione,risulterebbe come anno attuale il 118,e non 2018 (2018=1900+118)

	    if(anno_int<anno_attuale){

	    	printf("\n----------------------------------------------------------------------");
	    	printf("\nATTENZIONE!");
	    	printf("\n----------------------------------------------------------------------");

	    	printf("\nHai inserito un alimento gia' scaduto.L'inserimento e' stato annullato.\nE' consigliato cestinare questo alimento\n\n");
	    	system("pause");
	    	alimenti();

	    }

	    if((anno_int==anno_attuale) && (mese_int-1<info->tm_mon)){  //shift di -1 per il mese,in quanto tm_mon � un array da 0 a 11

	    	printf("\n----------------------------------------------------------------------");
	    	printf("\nATTENZIONE!");
	    	printf("\n----------------------------------------------------------------------");

	    	printf("\nHai inserito un alimento gia' scaduto.L'inserimento e' stato annullato.\nE' consigliato cestinare questo alimento\n\n");
	    	system("pause");
	    	alimenti();

	    }

	    if((anno_int==anno_attuale) && (mese_int-1==info->tm_mon) && (giorno_int<info->tm_mday)){  //shift di -1 per il mese,in quanto tm_mon � un array da 0 a 11

	    	printf("\n----------------------------------------------------------------------");
	    	printf("\nATTENZIONE!");
	    	printf("\n----------------------------------------------------------------------");

	    	printf("\nHai inserito un alimento gia' scaduto.L'inserimento e' stato annullato.\nE' consigliato cestinare questo alimento\n\n");
	    	system("pause");
	    	alimenti();

	    }

		//-------------------------------------------------------------------------

        num_linee++;  //incremento del numero di linee del file,in modo da non sovrascrivere alimenti precedentemente inseriti

        file_save_alimenti(num_linee);

    }

    printf("\n");
    system("pause");


}

/**
 * La procedura permette di modificare le quantita degli alimenti presenti nel frigo.
 *
 * @param num_linee riceve in input il numero di linee del file "alimenti.txt"
 */

void modifica_alimenti(int num_linee){

    char selezione[10]; //stringa per memorizzare il numero di alimenti che si vogliono inserire
    int selezione_int; 	//variabile in cui � memorizzato il numero di alimenti che si vogliono inserire (case1), il numero dell'alimento che si vuole modificare( case3)

    char nuova_quantita[10];
    int nuova_quantita_int;

    int vecchia_quantita;

    int i;

    printf("Di quale alimento si intende modificare le quantita' presenti?\n\nSe vuoi rimuovere un elemento dal frigo,digita una quantita' '0'\n\nDigitane il numero ad esso associato:");

    fflush(stdin);

    gets(selezione);

    if(isOnlyNumbers(selezione)==true) {

    	messaggio_errore();
        alimenti();

    }

    else if (isOnlyNumbers(selezione)==false){

        selezione_int=atoi(selezione);
    }

    selezione_int=selezione_int-1; 	//diminuzione del valore della variabile di 1 per allinearsi con l'array,in quanto l'utente vede e seleziona valori shiftati di 1,per evitare che vi sia un alimento indicato col valore 0

    vecchia_quantita=atoi(archivio_alimenti[selezione_int].quantita); //copio la vecciha quantit� presente in frigo per usarla nel confronto,in quanto � possibile solo diminuire le quantit�,non aumentarle

    do{

		printf("\nInserire la nuova quantita':");

		gets(nuova_quantita);

		if(isOnlyNumbers(nuova_quantita)==true) {

			messaggio_errore();
			alimenti();

		}

		else if (isOnlyNumbers(nuova_quantita)==false){

			nuova_quantita_int=atoi(nuova_quantita);
		}

		if(nuova_quantita_int>vecchia_quantita){

			printf("\n\n Non puoi aggiungere cibo!Solo rimuoverlo,se vuoi aggiungere cibo al frigo\nusare la funzione 'Aggiungi Alimenti'\n");
			system("pause");
		}

	}while(nuova_quantita_int>vecchia_quantita);

    strcpy(archivio_alimenti[selezione_int].quantita,nuova_quantita);

    if(nuova_quantita_int==0){    //nel caso venga inserito un valore pari a 0 nel campo quantit�,l'alimento verr�automaticamente rimosso

        for (i=selezione_int;i<num_linee;i++){ 		//ciclo per copiare i valori nella posizione precedente,in modo da rimuovere l'alimento e non lasciare spazi vuoti nell'elenco

            strcpy(archivio_alimenti[i].nome,archivio_alimenti[i+1].nome);
            strcpy(archivio_alimenti[i].giorno,archivio_alimenti[i+1].giorno);
            strcpy(archivio_alimenti[i].mese,archivio_alimenti[i+1].mese);
            strcpy(archivio_alimenti[i].anno,archivio_alimenti[i+1].anno);
            strcpy(archivio_alimenti[i].quantita,archivio_alimenti[i+1].quantita);
            strcpy(archivio_alimenti[i].kcal,archivio_alimenti[i+1].kcal);

            //copia del nome nella lista della spesa

            file_append_lista(archivio_alimenti[i].nome);

        }

        num_linee--;	//decremento del numero di linee del file, dopo l'eliminazione di un alimento

    }

    if(nuova_quantita_int<=SOGLIA_LISTA){

        //copia del nome nella lista della spesa

        file_append_lista(archivio_alimenti[i].nome);

    }

        file_save_alimenti(num_linee);	//aggiornamento del contenuto del file dopo le modifiche

        printf("\n\n");
        system("pause");

}

/**
 * Questa procedura permette di capire quali sono gli alimenti, presenti nello Smart Fridge, che sono scaduti o sono in scadenza.
 * Viene utilizzata all'interno del sottomen� "alimenti".
 *
 * @pre devono esserci alimenti presenti nello Smart Fridge.
 *
 * @param num_linee, ovvero il numero di linee del file "alimenti.txt"
 */

void scadenze(int num_linee){

	int anno_int;          //conversione in int dell'anno di scadenza dell'alimento
	int mese_int;		   //conversione in int del mese di scadenza dell'alimento
	int giorno_int;		   //conversione in int del giorno di scadenza dell'alimento

	int anno_attuale;   	//variabile in cui salvare l'anno attuale (a cui poi dover aggiungere 1900)
	int flag_scadenza=0;	//valore flag per indicare se ci sono alimenti in scadenza
	int flag_scaduto=0;		//valore flag per indicare se un alimento � scaduto,serve per non ripetere la stampa degli alimenti ANCORA IN SCADENZA
	int i;
	int j;
	int k;
	int *ricette_trovate;

	int tot_giorni_anno=0; //variabile per salvare il numero del giorno in cui scade l'alimento,da 0 a 365

	//Acquisisco l'orario e lo memorizzo nella struct tm
    time_t rawtime;
    struct tm *info;

    time(&rawtime);
    info = gmtime(&rawtime );

    anno_attuale=info->tm_year;

    anno_attuale=anno_attuale + 1900; //aggiungo 1900 perch� la libreria esterna inizia a contare da 0,ignorando ben 1900 anni.Senza l'addizione,risulterebbe come anno attuale il 118,e non 2018 (2018=1900+118)

    printf("\n-----------------------------------------------------------");
    printf("\nALIMENTI IN SCADENZA");
    printf("\n-----------------------------------------------------------");

    for(i=0;i<num_linee;i++){

    	anno_int=atoi(archivio_alimenti[i].anno);
    	mese_int=atoi(archivio_alimenti[i].mese);
    	giorno_int=atoi(archivio_alimenti[i].giorno);

    	tot_giorni_anno=0;
    	flag_scaduto=0;

    	//in base al mese di scadenza dell'alimento,sommo il numero di giorni dei mesi precedenti
    	//Es. Marzo(case 3) equivale alla somma  dei giorni di Gennaio (31) e Febbraio (28) = 59 , + i giorni del mese stesso
    	//Quindi,se avremo un alimento che scade il 10 Marzo,avremo che il contatore totale dei giorni dell'anno ammonter� a 69.
    	//Questo numero sar� poi utilizzato per il controllo di scadenza,dove confronter� i giorni di scadenza del cibo,con i giorni attualmente passati dall'inizio dell'anno


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

    	//------------------------------------------------------------
    	//CONTROLLO SCADUTI

    	if((anno_attuale==anno_int) && (tot_giorni_anno<info->tm_yday)){

    		flag_scadenza=0; //indica che c'� effettivamente cibo in scadenza
    		flag_scaduto=1;  //L'alimento � scaduto

    	}

    	if ((anno_attuale>anno_int)){

        		flag_scadenza=0; //indica che c'� effettivamente cibo in scadenza
        		flag_scaduto=1;  //L'alimento � scaduto

    	}

    	//-------------------------------------------------------------
    	//CONTROLLO IN SCADENZA

    	if((anno_attuale==anno_int) && (tot_giorni_anno-SOGLIA_SCADENZA<=info->tm_yday)){

    		flag_scadenza=1; //indica che c'� effettivamente cibo in scadenza

    		if(flag_scaduto==0){

    			printf("\n%s",archivio_alimenti[i].nome);  //TODO Inserire consiglio ricette anche nelle altre condizioni if

    			ricette_trovate=ricerca(archivio_alimenti[i].nome);

    			k=ricette_trovate[0];   //la prima posizione dell'array ricette_trovate contiene il numero di ricette trovate,utile quindi al corretto numero di stampe

    			for(j=0;j<k;j++){

        			printf("\nPotresti cucinare:");

        			printf("%s",archivio_ricette[ricette_trovate[j+1]].nome);  //il resto delle posizioni dell'array,quindi da ricette_trovate[1] in poi,contiene
        																	   //la posizione nell'array di struct della ricetta contenente l'alimento in scadenza

    			}

    		}
    	}

    	//controllo della scadenza nel caso di alimenti che scadono l'anno dopo (solo nel caso di (Dicembre 20XX) -> (Gennaio 20XX+1)

    	//ALGORITMO
    	//[(N.Giorni_Anno - Giorno_attuale) + Giorno_di_scadenza] < Soglia_di_scadenza

    	//Se il risultato dell'operazione fra le parentesi � minore della soglia di scadenza,l'alimento � in scadenza

    	if ((anno_attuale<anno_int)  && (mese_int==1) && (((364-info->tm_yday)+tot_giorni_anno)<=SOGLIA_SCADENZA)){

        		flag_scadenza=1; //indica che c'� effettivamente cibo in scadenza

        		if(flag_scaduto==0){

        			printf("\n%s",archivio_alimenti[i].nome);

                	//printf("Potresti cucinare:%s",);

        		}

    	}

    }

    if(flag_scadenza==0){

    	printf("\nNessun alimento in scadenza\n\n");
    }

    printf("\n\n\n");

    printf("\n***********************************************************");
    printf("\nALIMENTI SCADUTI\nE' consigliato rimuovere questi alimenti dal frigo)");
    printf("\n***********************************************************");

    for(i=0;i<num_linee;i++){

    	anno_int=atoi(archivio_alimenti[i].anno);
    	mese_int=atoi(archivio_alimenti[i].mese);
    	giorno_int=atoi(archivio_alimenti[i].giorno);

    	tot_giorni_anno=0;
    	flag_scaduto=0;

    	//in base al mese di scadenza dell'alimento,sommo il numero di giorni dei mesi precedenti
    	//Es. Marzo(case 3) equivale alla somma  dei giorni di Gennaio (31) e Febbraio (28) = 59 , + i giorni del mese stesso
    	//Quindi,se avremo un alimento che scade il 10 Marzo,avremo che il contatore totale dei giorni dell'anno ammonter� a 69.
    	//Questo numero sar� poi utilizzato per il controllo di scadenza,dove confronter� i giorni di scadenza del cibo,con i giorni attualmente passati dall'inizio dell'anno


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

    	//------------------------------------------------------------
    	//CONTROLLO SCADUTI

    	if((anno_attuale==anno_int) && (tot_giorni_anno<info->tm_yday)){

            printf("\n%s",archivio_alimenti[i].nome);

    	}

    	if ((anno_attuale>anno_int)){

                printf("\n%s",archivio_alimenti[i].nome);

    	}
    }

}

