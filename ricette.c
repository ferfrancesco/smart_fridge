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

//inclusione valori bool
typedef int bool;
#define true 1
#define false 0

#define MAX_RICETTE 50  //quantità max di ricette

int num_linee;

/**
 * Questo array serve a conservare il numero di stelle indicanti la difficoltà di una ricetta.
 */

char stelle[5]={0};

/**
 * 		Questa procedura permette di stampare il sottomenu per la categoria "ricette".
 * 		E' possibile :
 * 	1) 	Visualizzare le ricette salvate nel sistema
 * 	2)	Ricercare corrispondenza ricette per ingrediente o per un gruppo di ingredienti
 * 	3)	Aggiungere una ricetta
 * 	4)  Rimuovere una ricetta
 * 	5)	Modificare una ricetta
 * 	6)	Tornare al menu
 */

void ricette(){

    int i;

    num_linee=file_load_ricette();
    int menu_select=0;

    char selezione[10];
    int selezione_int;

    fflush(stdin);
    system("cls");

    printf("Menu' Ricette\nSeleziona un opzione\n\n1)Visualizza ricette salvate\n2)Ricerca ricette\n3)Aggiungi una ricetta\n4)Rimuovi una ricetta\n5)Torna al menu'\n\n");

    scanf("%d",&menu_select);

    switch(menu_select){

        case 1:

            system("cls");
            stampa_elenco_ricette(num_linee);

            printf("\n\nChe ricetta si desidera visualizzare?Inserire un valore numerico:");

            fflush(stdin);
            gets(selezione);

            if(isOnlyNumbers(selezione)==true) {

            	messaggio_errore();
                ricette();

            }

            else if (isOnlyNumbers(selezione)==false){

                selezione_int=atoi(selezione);
            }

            selezione_int--; //decremento di 1 per allinearmi con l'array

            system("cls");

            stampa_ricetta(selezione_int);

            printf("\n------------------------------------------------------------------");
            printf("\nFinito!Tornerai ora al menu' delle ricette\n\n");
            system("pause");
            ricette();

            break;

        case 2:
            //	ricette();
            break;

        case 3:

            system("cls");
            fflush(stdin);

            printf("Inserire il nome della ricetta:");
            gets(archivio_ricette[num_linee].nome);

            /*---------------------------------------------------------------*/

            printf("\nDa 1 a 5 Quanto è difficile questa ricetta?(Inserire valori numerici):");
            gets(selezione);

            if(isOnlyNumbers(selezione)==true) {

            	messaggio_errore();
                ricette();

            }

            selezione_int=atoi(selezione);

			if((selezione_int>0) && (selezione_int<6)) {

				strcpy(archivio_ricette[num_linee].difficolta,selezione);

            }

				else{
						printf("Scelta inserita non valida!\n");
						system("pause");
						ricette();
				}

            /*---------------------------------------------------------------*/

            printf("\nQuanti ingredienti ha questa ricetta?(Inserire valori numerici):");
            gets(selezione);

            if(isOnlyNumbers(selezione)==true) {

            	messaggio_errore();
                ricette();

            }

            else if (isOnlyNumbers(selezione)==false){

                strcpy(archivio_ricette[num_linee].num_ingredienti,selezione);
            }

            selezione_int = atoi(selezione);

            for(i=0;i<selezione_int;i++){

                printf("\nInserire l'ingrediente N%d:",i+1);
                gets(archivio_ricette[num_linee].ingredienti[i]);

            }

            /*---------------------------------------------------------------*/

            printf("\nQuanti step ha questa ricetta?(Inserire valori numerici):");
            gets(selezione);

            if(isOnlyNumbers(selezione)==true) {

            	messaggio_errore();
                ricette();

            }

            else if (isOnlyNumbers(selezione)==false){

                strcpy(archivio_ricette[num_linee].num_step,selezione);
            }

            selezione_int = atoi(selezione);

            for(i=0;i<selezione_int;i++){

                printf("\nInserire lo step N%d:",i+1);
                gets(archivio_ricette[num_linee].procedura[i]);

            }

            num_linee++; //incremento il nmero di linee per non sovrascrivere vecchie ricette

            file_save_ricette(num_linee);

            printf("\n------------------------------------------------------------------");
            printf("\nRicetta inserita correttamente.Verrai ora riportato al menu delle ricette\n\n");
            system("pause");
            ricette();

            break;

        case 4:
            //stampa_menu();
            break;

        case 5:
            stampa_menu();
            break;

        default:
            messaggio_errore();
            ricette();
            break;


            //TODO INSERISCI POSSIBILITA DI MODIFICARE RICETTE ALL'INTERNO DEL MENU RICETTE
    }

}


/**
 * Questa procedura permette di visualizzare l'elenco delle ricette inserite nel sistema.
 *
 * @pre E' necessario che il file delle ricette sia gia' esistente nel sistema
 *
 * @param num_linee, ovvero il numero di linee di cui il file "ricette.txt" e' costituito
 */
void stampa_elenco_ricette(int num_linee){

    int i;

    printf("Elenco delle ricette\n\n");
    printf("|%-50s|%-12s|","Nome Ricetta","Difficolta'");
    printf("\n-----------------------------------------------------------------\n");

    for(i=0;i<num_linee;i++){

        printf("|%-50s|",archivio_ricette[i].nome);

        printf("%-12s|%d)\n",stampa_stelle(i),i+1);

    }

}

/**
 * Questa funzione permette di calcolare il numero di stelline da visualizzare relativamente alla difficolta di una ricetta
 *
 * @pre Deve essere inserito un numero intero nel campo difficolta' di una ricetta
 *
 * @param num, ovvero il numero intero che indica la difficolta' di una ricetta
 *
 * @return il numero di stelle che saranno visualizzate in output, in base al numero intero inserito
 */

char* stampa_stelle(int num){

    int i;
    int int_difficolta;

    char stars[5]={0}; //definisco un array locale

    int_difficolta = atoi(archivio_ricette[num].difficolta);


    	for(i=0;i<int_difficolta;i++){

        strcat(stars,"*");  //accodo una stella fino a raggiungere il valore di difficoltà

    }

    strcpy(stelle,stars); //copio l'array locale nell'array globale

    return stelle;




}

void stampa_ricetta(int num){

    int i;
    int temp_int; //variabile intera temporanea per i cicli di stampa di ingredienti e procedure

    printf("%s\nDifficolta':%s\n",archivio_ricette[num].nome,stampa_stelle(num));
    printf("------------------------------------------------------------------\n");
    printf("Ingredienti:\n\n");

    temp_int=atoi(archivio_ricette[num].num_ingredienti); //converto in intero il num degli ingredienti per l'uso in un ciclo

    for(i=0;i<temp_int;i++){

        printf("%s\n",archivio_ricette[num].ingredienti[i]);

    }

    printf("\n------------------------------------------------------------------");

    printf("\nProcedura:\n");

    temp_int=atoi(archivio_ricette[num].num_step);

    for(i=0;i<temp_int;i++){

        printf("\n%d)%s",i+1,archivio_ricette[num].procedura[i]);
        getchar();

    }

}

int* ricerca_ricetta(char alimento[]){

	int num_linee;
	static int ricette_con_alimento[MAX_RICETTE];  //static necessario per il return dell'array
	int i;
	int j;
	int k=0;
	int num_ingredienti_int;

	char *ricerca;

	num_linee=file_load_ricette();

	for(i=0;i<num_linee;i++){

		num_ingredienti_int=atoi(archivio_ricette[i].num_ingredienti);

		for(j=0;j<num_ingredienti_int;j++){

			ricerca=strstr(archivio_ricette[i].ingredienti[j],alimento); //scansiono,cercando anche in sottostringhe,l'elenco degli ingredienti di ogni ricetta.

			if(ricerca != NULL){								//se viene trovata una corrispondenza,trascrivo il valore dell'indice i in un array,salvando quindi effettivamente,la ricetta contenente l'ingrediente

				ricette_con_alimento[k]=i;

				k++;
			}
		}


	}

	return ricette_con_alimento;

}

