#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "operazioni_file.h"
#include "alimenti.h"
#include "ricette.h"
#include "varie.h"
#include "altre_procedure.h"

//inclusione valori bool
typedef int bool;
#define true 1
#define false 0

#define CONSUM_MAX 100
#define LUNGH_MAX_NOME 50
#define MAX_LISTA 50

/**
 * Questa procedura stampa il menu per la categoria "varie".
 * E' possibile effettuare diverse scelte al suo interno.
 *
 * @pre E' necessario che nel menu principale dello Smart Fridge sia selezionata la categoria "varie"
 *
 */

void varie(){

    int menu_select=0;

    fflush(stdin);
    system("cls");

    printf("Menu' Varie\nSeleziona un opzione\n\n1)Menu' della settimana\n2)Lista della spesa\n3)Statistiche\n4)Torna al menu'\n\n");

    scanf("%d",&menu_select);

    switch(menu_select){

        case 1:
            menu_sett();
            break;

        case 2:
            lista();
            break;

        case 3:
            statistiche();
            break;

        case 4:
        	stampa_menu();
        	break;

        default:
            messaggio_errore();
            varie();
            break;

    }

}


/**
 * Procedura che stampa le diverse opzioni disponibili riguardo il menu settimanale
 * @pre per selezionare la prima scelta del menu, c'e' bisogno che il menu sia gia' stato inserito in precedenza
 */

void menu_sett(){

    int menu_select=0;
    int menu_select1=0;
    int i;

    char selezione[10];
    int selezione_int;

    char pietanza[LUNGH_MAX_NOME];

    dayname_fill(); 								//inizializzazione giorni della settimana per il menù settimanale

    file_load_menu_sett();

    system("cls");
    printf("Menu' settimanale:\n\n1)Visualizza menu'\n2)Inserisci pasto\n3)Cancella menu'\n4)Torna al menu' precedente\n\n");

    fflush(stdin);
    scanf("%d",&menu_select);

    switch(menu_select){

        case 1:

            system("cls");

            for(i=0;i<7;i++){

            	  printf("***************%-10s***************",giorno[i].dayname);
            	  printf("\nPranzo:%s\nCena:%s",giorno[i].pietanza[0],giorno[i].pietanza[1]);
            	  printf("\n\n");

            }

            printf("Tornerai ora al menu' precedente\n");
            system("pause");
            menu_sett();

            break;

        case 2:

        	system("cls");
        	printf("In che giorno vuoi inserire il pasto?\n\n1)Lunedi'\n2)Martedi'\n3)Mercoledi'\n4)Giovedi'\n5)Venerdi'\n6)Sabato\n7)Domenica\n");
        	fflush(stdin);
        	gets(selezione);

        	if(isOnlyNumbers(selezione)==true) {

        	    	messaggio_errore();
        	        menu_sett();

        	}

        	selezione_int=atoi(selezione);

        	if((selezione_int<=0) || (selezione_int>7)){

        		printf("\nDevi inserire un valore da 1 a 7\n");
        		system("pause");
        		menu_sett();

        	}

        	selezione_int--; //mi allineo all'array

        	printf("Vuoi inserire il pranzo o la cena?\n\n1)Pranzo\n2)Cena\n");

        	fflush(stdin);
        	scanf("%d",&menu_select1);

        	switch(menu_select1){

        	case 1:

        		do{

					printf("\nInserisci il pasto:");
					fflush(stdin);
					gets(pietanza);

					if(pietanza[0]=='\0'){

						printf("\nIl campo non puo' essere vuoto");
					}

        		}while(pietanza[0]=='\0');

        		strcpy(giorno[selezione_int].pietanza[0],pietanza);

        		break;

        	case 2:

        		do{

					printf("\nInserisci il pasto:");
					fflush(stdin);
					gets(pietanza);

					if(pietanza[0]=='\0'){

						printf("\nIl campo non puo' essere vuoto");
					}

        		}while(pietanza[0]=='\0');

        		strcpy(giorno[selezione_int].pietanza[1],pietanza);
        		break;

        	default:

                messaggio_errore();
                menu_sett();
                break;

        	}

            file_save_menu_sett();

            printf("\nInserimento completato,tornerai ora al menu' precedente\n");
            system("pause");
            menu_sett();

            break;

        case 3:

        	dayname_fill();
        	file_save_menu_sett();
        	printf("\n\nCancellazione eseguita\n\n");
        	system("pause");
        	menu_sett();
        	break;

        case 4:
            varie();
            break;

        default:
            messaggio_errore();
            varie();
            break;

    }

}


/**
 * Questa procedura permette di accedere al sottomenu' riguardante la lista della spesa nella categoria "varie"
 *
 */

void lista(){

    int menu_selez;		 //variabile che memorizza la scelta nel menu' da parte dell'utente
    int num_linee;
    int i;

    char selezione[10];
    int selezione_int;

    num_linee=file_load_lista();

    system("cls");
    printf("Scegli un opzione\n\n1)Visualizza lista\n2)Aggiungi elemento\n3)Rimuovi elemento\n4)Cancella lista\n5)Torna al menu' precedente\n\n");

    fflush(stdin);

    scanf("%d",&menu_selez);

    switch(menu_selez){

        case 1:

            system("cls");
            printf("Questa e' la lista della spesa\n\n");

            if(num_linee==0){

            	printf("La lista e' vuota\n\n");
            	system("pause");
            	lista();
            }

            for(i=0;i<num_linee;i++){

                printf("%d)%s\n",i+1,lista_spesa[i]);
            }

            printf("\n\n");
            system("pause");
            lista();

            break;

        case 2:

        	printf("\n\nCosa vuoi aggiungere alla lista?\n");

        	fflush(stdin);
        	gets(lista_spesa[num_linee]);

        	num_linee++;
        	file_save_lista(num_linee);

        	printf("\nElemento aggiunto!\n");
        	system("pause");
        	lista();

            break;

        case 3:

            system("cls");
            printf("Questa e' la lista della spesa\n\n");

            if(num_linee==0){

            	printf("La lista e' vuota\n\n");
            	system("pause");
            	lista();
            }

            for(i=0;i<num_linee;i++){

                printf("%d)%s\n",i+1,lista_spesa[i]);
            }

            do{

				printf("\n\nChe elemento vuoi rimuovere?Inserire un valore numerico\n\n");

				fflush(stdin);

				gets(selezione);

				if(isOnlyNumbers(selezione)==true) {

					messaggio_errore();
					lista();

				}

				selezione_int=atoi(selezione);

				if((selezione_int>num_linee) || (selezione_int<1)){

					printf("\nSeleziona un elemento corretto");

				}

            }while((selezione_int>num_linee) || (selezione_int<1));

			selezione_int--; //mi allineo all'array

			for(i=selezione_int;i<num_linee;i++){

				strcpy(lista_spesa[i],lista_spesa[i+1]);

			}

			num_linee--;
			file_save_lista(num_linee);

			printf("\nElemento Rimosso!\n");
			system("pause");
			lista();

            break;

        case 4:

        	memset(&lista_spesa[0], 0, MAX_LISTA);  //Cancello ogni elemento all'intero della matrice lista_spesa

			num_linee=0;

			file_save_lista(num_linee);

			printf("\n\nLista cancellata!\n");
			system("pause");
			lista();

        	break;

        case 5:
            varie();
            break;

        default:
            messaggio_errore();
            lista();
            break;
    }

}


/**
 *Questa procedura permette di accedere ad un sottomenu', interno alla categoria "varie", che permette di visualizzare le statistiche relative ai cibi più consumati e alle ricette più preparate.
 *
 *@pre bisogna accedere prima al sottomenu' della categoria "varie" per visualizzare le statistiche.
 *@post verranno visualizzare le statistiche relative a:
 *		1) Alimenti piu' consumati;
 *		2) Ricette piu' preparate;
 *In entrambe le opzioni, gli array che devono essere ordinati ( che sono campi di struct) ,vengono copiati
 * in array locali e poi ordinati
 *
 */

void statistiche(){

	int selezione;	//variabile che memorizza la selezione dell'utente nel sottomenu'
	int num_linee;	//numero di linee di cui e' composto il file "consumazioni.txt"
	int i;
	//int j;

	char nomi_temp[CONSUM_MAX][LUNGH_MAX_NOME]; //array locale in cui copiare il campo dei nomi di una delle struct di cui si devono ordinare i numeri
	int valori_ordinare[CONSUM_MAX]; 			//array locale in cui copiare il campo della struct da ordinare (composto da interi)

	system("cls");
	printf("Qui puoi visualizzare gli alimenti più consumati e le ricette più preparate\nCosa vuoi visualizzare?\n\n1)Alimenti piu' consumati\n2)Ricette piu' preparate\n3)Ritorna al menu' precedente\n\n");

	scanf("%d",&selezione);

	switch(selezione){

		case 1:

			num_linee=file_load_consumazioni();

			for(i=0;i<num_linee;i++){

				valori_ordinare[i]=atoi(archivio_consumazioni[i].consumazioni);  //converto i valori da ordinare da char a int
				strcpy(nomi_temp[i],archivio_consumazioni[i].nome);

			}

			selection_sort(valori_ordinare,nomi_temp,num_linee);

			system("cls");
			printf("Ecco un elenco dei 5 alimenti piu' consumati");

			printf("\n\n|%-50s|%-12s|","Alimento","Consumazioni");  //il valore negativo serve per l'allineamento a sinistra
	        printf("\n-----------------------------------------------------------------");

	        if(num_linee<5){

				for(i=num_linee-1;i>=0;i--){

					printf("\n|%-50s|%12d|%d)",nomi_temp[i],valori_ordinare[i],num_linee-i);

				}
	        }

	        else{

		        for(i=num_linee-1;i>num_linee-6;i--){

		           printf("\n|%-50s|%12d|%d)",nomi_temp[i],valori_ordinare[i],num_linee-i);

		        }

	        }

	        printf("\n\n");
	        system("pause");
	        varie();

			break;

		case 2:

			num_linee=file_load_ricette();

			for(i=0;i<num_linee;i++){

				valori_ordinare[i]=atoi(archivio_ricette[i].num_preparazioni);  //converto i valori da ordinare da char a int
				strcpy(nomi_temp[i],archivio_ricette[i].nome);

			}

			selection_sort(valori_ordinare,nomi_temp,num_linee);

			system("cls");
			printf("Ecco un elenco delle ricette piu' preparate");

			printf("\n\n|%-50s|%-12s|","Ricetta","Preparazioni");  //il valore negativo serve per l'allineamento a sinistra
	        printf("\n-----------------------------------------------------------------");

		    for(i=num_linee-1;i>=0;i--){

		        printf("\n|%-50s|%12d|%d)",nomi_temp[i],valori_ordinare[i],num_linee-i);

		    }

	        printf("\n\n");
	        system("pause");
	        varie();

			break;

		case 3:

			varie();
			break;

		default:
            messaggio_errore();
            statistiche();
			break;
	}

}
