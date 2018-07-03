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
#define LUNGH_MAX_NOME 50 //Luneghezza massima per il nome di un alimento

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

    num_linee=file_load_ricette();
    int menu_select=0;

    fflush(stdin);
    system("cls");

    printf("Menu' Ricette\nSeleziona un opzione\n\n1)Visualizza ricette salvate\n2)Ricerca ricette\n3)Aggiungi una ricetta\n4)Rimuovi una ricetta\n5)Torna al menu'\n\n");

    scanf("%d",&menu_select);

    switch(menu_select){

        case 1:

        	visualizza_ricette();
            ricette();

        break;

        case 2:

        	ricerca_ricette();
        	ricette();

            break;

        case 3:

        	aggiungi_ricette();
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

	//todo inserire messaggio d'errore quando nel sistema non sono presenti ricette "Non ci sono ricette!"
    int i;

    if(num_linee==0){

    	printf("Nessuna ricetta salvata!\n\n");
    	system("pause");
    	ricette();
    }

    else{

        printf("Elenco delle ricette\n\n");
        printf("|%-50s|%-12s|","Nome Ricetta","Difficolta'");
        printf("\n-----------------------------------------------------------------\n");

        for(i=0;i<num_linee;i++){

            printf("|%-50s|",archivio_ricette[i].nome);

            printf("%-12s|%d)\n",stampa_stelle(i),i+1);
        }

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

/**
 * Questa procedura permette di stampare le informazioni e le caratteristiche relative ad una
 * particolare ricetta inserita nel sistema.
 *
 * @pre devono esserci ricette inserite nel sistema.
 *
 * @param num, prende in input il numero della ricetta di cui visualizzarne le caratteristiche.
 */

void stampa_ricetta(int num){

	//todo inserire messaggio d'errore quando nel sistema non sono presenti ricette "Non ci sono ricette!"

    int i;
    int temp_int; //variabile intera temporanea per i cicli di stampa di ingredienti e procedure
    int num_preparazioni_int;  //variabile intera temporanea per l'incremento di num_preparazioni

    int menu_select=0;

    printf("%s\nDifficolta':%s\n",archivio_ricette[num].nome,stampa_stelle(num));
    printf("------------------------------------------------------------------\n");
    printf("Ingredienti:\n\n");

    temp_int=atoi(archivio_ricette[num].num_ingredienti); //converto in intero il num degli ingredienti per l'uso in un ciclo

    for(i=0;i<temp_int;i++){

        printf("%s\n",archivio_ricette[num].ingredienti[i]);

    }

    printf("\n------------------------------------------------------------------");

    printf("\nIntendi semplicemente visualizzare la ricetta o la vuoi preparare?\n\n1)Visualizzare\n2)Preparare\n\n");
    scanf("%d",&menu_select);

    switch(menu_select){

			case 1:

				printf("\nOK!Visualizzerai ora la ricetta\n");
				system("pause");

			break;

			case 2:

				num_preparazioni_int=atoi(archivio_ricette[num].num_preparazioni);

				num_preparazioni_int++;

				sprintf(archivio_ricette[num].num_preparazioni, "%d", num_preparazioni_int);

				printf("\nOK!Verra' memorizzato che hai gia' cucinato questa ricetta %s volte\n",archivio_ricette[num].num_preparazioni);

				file_save_ricette(num_linee); //salvo le ricette su file per salvare il contatore del numero di volte che la ricetta è stata cucinata aggiornato

				system("pause");


			break;

			default:

				messaggio_errore();
				ricette();

			break;

    }

    printf("\n------------------------------------------------------------------");

    printf("\nProcedura:\n");

    temp_int=atoi(archivio_ricette[num].num_step);

    fflush(stdin);

    for(i=0;i<temp_int;i++){

        printf("\n%d)%s",i+1,archivio_ricette[num].procedura[i]);
        getchar();

    }

}

//todo commenta (ricordati di usare l'algoritmo di scrematura--->
//fedelucio vuole un ingrediente o un gruppo di ingredienti.

/**
 * La funzione "ricerca" prende in input una stringa (che rappresenta un alimento) e restituisce
 * la ricetta (o le ricette) che contengono quell'ingrediente.
 *
 * @pre Si deve accedere prima alla procedura "ricerca_ricette"
 *
 * @param alimento,ovvero l'ingrediente con il quale ricercare le corrispondenze
 * @return ricette_con_alimento,ovvero un array di indici interi che indicano le posizioni delle corrispondenze
 */

int* ricerca(char alimento[]){

	int num_linee;
	static int ricette_con_alimento[MAX_RICETTE];  //static necessario per il return dell'array
	int i;
	int j;
	int k=1;
	int num_ingredienti_int;

	char *risultato;

	num_linee=file_load_ricette();

	for(i=0;i<num_linee;i++){

		num_ingredienti_int=atoi(archivio_ricette[i].num_ingredienti);

		for(j=0;j<num_ingredienti_int;j++){

			risultato=strstr(archivio_ricette[i].ingredienti[j],alimento); //scansiono,cercando anche in sottostringhe,l'elenco degli ingredienti di ogni ricetta.

			if(risultato != NULL){								//se viene trovata una corrispondenza,trascrivo il valore dell'indice i in un array,salvando quindi effettivamente,
																//la posizione nell'array di struct della ricetta contenente l'ingrediente
				ricette_con_alimento[k]=i;

				k++;
			}
		}


	}

	ricette_con_alimento[0]=k-1;			// salvo nella posizione 0 il numero di ricette (corrispondenze) trovate, ovvero k-1.

	return ricette_con_alimento;

}

/**
 * E' la procedura che ci permette di accedere alla funzione "ricerca", per trovare le
 * corrispondenze tra un alimento e le ricette disponibili all'interno del sistema.
 */
void ricerca_ricette(){

	char nome_alimento[LUNGH_MAX_NOME];

	char* nome_alimento_low;

	int *ricette_trovate;
	int i;
	int j;

	system("cls");
	printf("Ricerca ricette in base ai suoi ingredienti\n\n");
	printf("Inserire il nome dell'ingrediente:");

	fflush(stdin);

	gets(nome_alimento);

	nome_alimento_low=low_conversion(nome_alimento);

	ricette_trovate=ricerca(nome_alimento_low);

	j=ricette_trovate[0];   //la prima posizione dell'array ricette_trovate contiene il numero di ricette trovate,utile quindi al corretto numero di stampe

	for(i=0;i<j;i++){

		printf("%s\n",archivio_ricette[ricette_trovate[i+1]].nome);  //il resto delle posizioni dell'array,quindi da ricette_trovate[1] in poi,contiene
																   //la posizione nell'array di struct della ricetta contenente l'alimento in scadenza

	}

	printf("\n\n");
	system("pause");

}

void visualizza_ricette(){

    char selezione[10];
    int selezione_int;

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

}

void aggiungi_ricette(){  //TODO aggiungi inserimento numero volte cucinate

    char selezione[10];
    int selezione_int;

    int i;

    system("cls");
    fflush(stdin);

    char nome_alimento [LUNGH_MAX_NOME];
    char* nome_alimento_low;

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
        gets(nome_alimento);

       nome_alimento_low=low_conversion(nome_alimento);

       strcpy(archivio_ricette[num_linee].ingredienti[i],nome_alimento_low);

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


}
