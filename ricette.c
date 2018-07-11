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

/**
 * Questo array serve a conservare il numero di stelle indicanti la difficoltà di una ricetta.
 */

char stelle[5]={0};  //inizialiazzo l'array della stampa delle stelle
int num_linee;


//----------------------------------------------------------------------------
//PROCEDURE RICETTE VARIE


/**
 * 	Questa procedura permette di stampare il sottomenu per la categoria "ricette".
 * 		E' possibile :
 * 	1) 	Visualizzare le ricette salvate nel sistema
 * 	2)	Ricercare corrispondenza ricette per ingrediente o per numero di Kcal
 * 	3)	Aggiungere una ricetta
 * 	4)  Modificare una ricetta
 * 	5)	Rimuovere una ricetta
 * 	6)	Tornare al menu
 */

void ricette(){

    num_linee=file_load_ricette();
    int menu_select=0;

    fflush(stdin);
    system("cls");

    printf("Menu' Ricette\nSeleziona un opzione\n\n1)Visualizza ricette salvate\n2)Ricerca ricette\n3)Aggiungi una ricetta\n4)Modifica una ricetta\n5)Rimuovi una ricetta\n6)Torna al menu'\n\n");

    scanf("%d",&menu_select);

    switch(menu_select){

        case 1:

        	visualizza_ricette();  //TODO Fixa crash quando l'input è nullo
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
            modifica_ricette();
            ricette();
            break;

        case 5:

        	rimuovi_ricette();
			ricette();

        	break;

        case 6:
            stampa_menu();
            break;

        default:
            messaggio_errore();
            ricette();
            break;

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

char* stampa_stelle(int difficolta){

    int i;

    char stars[6]={0}; //definisco un array locale

    for(i=0;i<difficolta;i++){

        strcat(stars,"*");  //accodo una stella fino a raggiungere il valore di difficoltà

    }

    strcpy(stelle,stars); //copio l'array locale nell'array globale

    return stelle;
}


//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//VISUALIZZAZIONE RICETTE


/**
 * Questa procedura richiama le sottoprocedure "stampa_elenco_ricette" e, a sua volta, stampa_ricette
 */

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

/**
 * Questa procedura permette di visualizzare l'elenco delle ricette inserite nel sistema.
 *
 * @pre E' necessario che il file delle ricette sia gia' esistente nel sistema
 *
 * @param num_linee, ovvero il numero di linee di cui il file "ricette.txt" e' costituito
 */

void stampa_elenco_ricette(int num_linee){

    int i;
    int int_difficolta;

    if(num_linee==0){

    	printf("Nessuna ricetta salvata!\n\n");
    	system("pause");
    	ricette();
    }

    else{

        printf("Elenco delle ricette\n\n");
        printf("|%-50s|%-12s|%-9s|","Nome Ricetta","Difficolta'","KCAL 100g");
        printf("\n---------------------------------------------------------------------------\n");

        for(i=0;i<num_linee;i++){

            printf("|%-50s|",archivio_ricette[i].nome);

            int_difficolta = atoi(archivio_ricette[i].difficolta);

            printf("%-12s|%-9s|%d)\n",stampa_stelle(int_difficolta),archivio_ricette[i].kcal,i+1);
        }

    }

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

    int i;
    int temp_int; 			   //variabile intera temporanea per i cicli di stampa di ingredienti e procedure
    int num_preparazioni_int;  //variabile intera temporanea per l'incremento di num_preparazioni
    int int_difficolta;

    int menu_select=0;

    int_difficolta = atoi(archivio_ricette[num].difficolta);

    printf("%s\nDifficolta':%s\n",archivio_ricette[num].nome,stampa_stelle(int_difficolta));
    printf("------------------------------------------------------------------\n");
    printf("Ingredienti:\n\n");

    temp_int=atoi(archivio_ricette[num].num_ingredienti); //converto in intero il num degli ingredienti per l'uso in un ciclo

    for(i=0;i<temp_int;i++){

    	archivio_ricette[num].ingredienti[i][0]=toupper(archivio_ricette[num].ingredienti[i][0]); 	//converto il primo carattere per una questione estetica durante la stampa degli ingredienti

    	printf("%s\n",archivio_ricette[num].ingredienti[i]);

        archivio_ricette[num].ingredienti[i][0]=tolower(archivio_ricette[num].ingredienti[i][0]);   //riporto a minuscolo,serve che l'ingrediente sia salvato in minuscolo per la ricerca
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


//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//RICERCA RICETTE


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
	int k=1;									  //contatore che parte da 1, poiche in posizione 0 verra' memorizzato il numero di corrispondenze trovate
	int num_ingredienti_int;					  // memorizza la conversione del numero di ingredienti di una ricetta da stringa ad intero

	char *risultato;							  //memorizza la stringa trovata facendo la corrispondenza tra l'alimento inserito in input e ogni ingrediente di ogni ricetta

	num_linee=file_load_ricette();

	for(i=0;i<num_linee;i++){

		num_ingredienti_int=atoi(archivio_ricette[i].num_ingredienti);

		for(j=0;j<num_ingredienti_int;j++){

			risultato=strstr(archivio_ricette[i].ingredienti[j],alimento); //scansiono,cercando anche in sottostringhe,l'elenco degli ingredienti di ogni ricetta.

			if(risultato != NULL){										   //se viene trovata una corrispondenza,trascrivo il valore dell'indice i in un array,salvando quindi effettivamente,
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

	char nome_alimento[LUNGH_MAX_NOME];//memorizza il nome dell'alimento di cui cercare un'eventuale corrispondenza di ricetta

	char* nome_alimento_low;		   //conversione in minuscolo della stringa "nome_alimento"

	int *ricette_trovate;			   //variabile locale che indica il numero di corrispondenze tra alimento e ricette trovate, da mettere nella prima posizione dell'array
	int i;
	int j;
	int selezione;

	int num_linee;
	char nomi_temp[CONSUM_MAX][LUNGH_MAX_NOME];
	int valori_ordinare[CONSUM_MAX];

	system("cls");
	printf("Con quale parametro vuoi cercare le ricette?\n\n1)Ricerca per ingrediente\n2)Visualizza per ordine di KCAL\n\n");
	scanf("%d",&selezione);

	switch(selezione){

		case 1:

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

		break;

		case 2:

			num_linee=file_load_ricette();

			for(i=0;i<num_linee;i++){

				valori_ordinare[i]=atoi(archivio_ricette[i].kcal);  //converto i valori da ordinare da char a int
				strcpy(nomi_temp[i],archivio_ricette[i].nome);

			}

			selection_sort(valori_ordinare,nomi_temp,num_linee);

			system("cls");
			printf("Elenco delle ricette ordinate in modo decrescente in base alle KCAL");

			printf("\n\n|%-50s|%-12s|","Ricetta","KCAL");  //il valore negativo serve per l'allineamento a sinistra
	        printf("\n-----------------------------------------------------------------\n");

			for(i=num_linee-1;i>=0;i--){

				printf("|%-50s|%12d|%d)\n",nomi_temp[i],valori_ordinare[i],num_linee-i);

			}

	        printf("\n\n");
	        system("pause");

		break;

		default:

			messaggio_errore();
			ricerca_ricette();

			break;

	}

}


//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//GESTIONE RICETTE

/**
 * Questa procedura permette di aggiungere ricette alla lista di ricette presenti all'interno del sistema.
*
* @pre E' necessario accedere al sottomenu' della categoria "ricette" e selezionare la voce "aggiungi ricetta"
* @post il sistema aggiungera' una ricettaal file "ricette.txt"
* E' possibile immettere il nome della ricetta, gli ingredienti, la difficolta' e gli steps.
* **/

void aggiungi_ricette(){

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

    printf("\nDa 1 a 5 Quanto e' difficile questa ricetta?(Inserire valori numerici):");
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

    printf("\nQuante KCAL ha approssimativamente questa ricetta per 100g?(Inserire valori numerici):");
    gets(selezione);

    if(isOnlyNumbers(selezione)==true) {

    	messaggio_errore();
        ricette();

    }

    else if (isOnlyNumbers(selezione)==false){

        strcpy(archivio_ricette[num_linee].kcal,selezione);
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

    strcpy(archivio_ricette[num_linee].num_preparazioni,"0");

    num_linee++; //incremento il nmero di linee per non sovrascrivere vecchie ricette

    file_save_ricette(num_linee);

    printf("\n------------------------------------------------------------------");
    printf("\nRicetta inserita correttamente.Verrai ora riportato al menu delle ricette\n\n");
    system("pause");


}

/**
 * Questa procedura permette di modificare le caratteristiche di una ricetta, ovvero nome, difficolta', kcal, ingredienti o procedura.
 * Si accede ad un sottomenu' di modifica, dal quale si immette la scelta relativa al dato da modificare.
 * 1)nome
 * 2)difficolta'
 * 3)kcal
 * 4)ingredienti
 * 5)procedura
 *
 * @pre Per accedere al sottomenu' di modifica e' necessario accedere alla categoria "ricette" del programma
 * @pre E' necessario che ci siano ricette all'interno del programma
 *
 * @post si ha l'effettiva modifica dei dati di una ricetta
 *
 */

void modifica_ricette(){

	char selezione[10]; // stringa che memorizza la scelta dell'utente su che ricetta modificare
	int selezione_int;	//conversione di "selezione" in intero

	int selezione_menu;	//scelta dell'utente su qualce parametro di una ricetta modificare

	char nuovo_dato[200];// stringa che memorizza il nuovo dato da sostituire al precedente
	int nuovo_dato_int;	// conversione di "nuovo_dato" in intero, se questo e' un dato numerico

	system("cls");
	stampa_elenco_ricette(num_linee);

    printf("\n\nChe ricetta si desidera modificare?Inserire un valore numerico:");

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

    printf("Cosa vorresti modificare?\n\n1)Nome\n2)Difficolta'\n3)KCAL\n4)Ingredienti\n5)Procedura\n-----------------------\n6)Annulla\n\n");
    scanf("%d",&selezione_menu);

    switch(selezione_menu){

    	case 1:

    		printf("\nInserisci il nuovo nome:");
    		fflush(stdin);
    		gets(nuovo_dato);

    		strcpy(archivio_ricette[selezione_int].nome,nuovo_dato);

    		file_save_ricette(num_linee);

    	break;

    	case 2:

    		do{
    			printf("\nDa 1 a 5 Quanto e' difficile questa ricetta?(Inserire valori numerici):");
    			fflush(stdin);
    			gets(nuovo_dato);

				if(isOnlyNumbers(nuovo_dato)==true) {

					messaggio_errore();
					ricette();

				}

				nuovo_dato_int=atoi(nuovo_dato);

				if((nuovo_dato_int>0) && (nuovo_dato_int<6)) {

					strcpy(archivio_ricette[selezione_int].difficolta,nuovo_dato);

				}

				else{
						printf("Scelta inserita non valida!\n");
				}

    		} while((nuovo_dato_int<0) && (nuovo_dato_int>6));

    		file_save_ricette(num_linee);

    	break;

    	case 3:

			printf("\nInserire il nuovo valore di KCAL(Inserire valori numerici):");
			fflush(stdin);
			gets(nuovo_dato);

			if(isOnlyNumbers(nuovo_dato)==true) {

				messaggio_errore();
				ricette();

			}

			strcpy(archivio_ricette[selezione_int].kcal,nuovo_dato);

			file_save_ricette(num_linee);

    	break;

    	case 4:

    		modifica_ingredienti(selezione_int);
    		ricette();

    	break;


    	case 5:

    		modifica_procedura(selezione_int);
			ricette();

    	break;

    	default:

        	messaggio_errore();
        	ricette();

        break;
    }

    printf("\n\n");
    system("pause");
    ricette();

}

/**
 * Questa procedura permette di aggiungere, modificare o rimuovere un ingrediente da una ricetta gia' esistente all'interno del sistema Smart Fridge.
 * @pre e' necessario prima accedere alla categoria "ricette", poi al sottomenu' di modifica di una ricetta.
 * @pre e' necessario che ci siano ricette all'interno dello Smart Fridge
 *
 * @param ingrediente, ovvero il numero dell'ingrediente che, eventualmente, si vuole modificare
 */

void modifica_ingredienti(int ingrediente){

	char selezione[10];	//stringa che memorizza la selezione dell'utente sull'ingrediente da modificare
	int selezione_int;	//conversione ddi "selezione"

	int selezione_menu;	//memorizza la scelta dell'utente su cosa fare (aggiungere, modificare o rimuovere un ingrediente da una ricetta)
	int i;

	char nuovo_dato[200]; //stringa che memorizza il nuovo ingrediente (o la modifica di un ingrediente gia' esistente)
	char* nuovo_dato_low; //conversione di "nuovo_dato" in minuscolo
	int nuovo_dato_int;	  // conversione di "nuovo_dato" in intero, se dovesse essere un dato di tipo numerico

	int num_ingredienti;  //contatore che viene incrementato, qualora venissero aggiunti ingredienti

	system("cls");
	printf("Che operazione vuoi eseguire?\n\n1)Aggiungi un ingrediente\n2)Modifica un ingrediente\n3)Rimuovi un ingrediente\n4)Torna al menu'\n\n");

	fflush(stdin);

	scanf("%d",&selezione_menu);

	switch(selezione_menu){

	case 1:

		system("cls");
		printf("Inserire il nome del nuovo ingrediente\n\n");
		fflush(stdin);
		gets(nuovo_dato);

        nuovo_dato_low=low_conversion(nuovo_dato);

        num_ingredienti=atoi(archivio_ricette[ingrediente].num_ingredienti);

        num_ingredienti++;

        sprintf(archivio_ricette[ingrediente].num_ingredienti, "%d", num_ingredienti);

        strcpy(archivio_ricette[ingrediente].ingredienti[num_ingredienti],nuovo_dato_low);

        file_save_ricette(num_linee);

	break;

	case 2:

		system("cls");
		printf("Elenco degli ingredienti\n\n");

		num_ingredienti=atoi(archivio_ricette[ingrediente].num_ingredienti);

		for(i=0;i<num_ingredienti;i++){

			printf("%d)%s\n",i+1,archivio_ricette[ingrediente].ingredienti[i]);

		}

		do{

		printf("\n\nChe ingrediente si intende modificare?\n\n");
		fflush(stdin);
		gets(selezione);

		if(isOnlyNumbers(selezione)==true) {

			messaggio_errore();
			modifica_ingredienti(ingrediente);

		}

		selezione_int=atoi(selezione);

		if(selezione_int>num_ingredienti){

			printf("\nHai selezionato un ingrediente non esistente,riprova");
		}

		}while(selezione_int>num_ingredienti);

		selezione_int--; //decremento di uno per allinearmi con l'array

		printf("\nInserire il nuovo nome dell' ingrediente\n\n");
		fflush(stdin);
		gets(nuovo_dato);

        nuovo_dato_low=low_conversion(nuovo_dato);

        strcpy(archivio_ricette[ingrediente].ingredienti[selezione_int],nuovo_dato_low);

        file_save_ricette(num_linee);

	break;

	case 3:

		system("cls");
		printf("Elenco degli ingredienti\n\n");

		num_ingredienti=atoi(archivio_ricette[ingrediente].num_ingredienti);

		for(i=0;i<num_ingredienti;i++){

			printf("%d)%s\n",i+1,archivio_ricette[ingrediente].ingredienti[i]);

		}

		do{

		printf("\n\nChe ingrediente si intende rimuovere?\n\n");
		fflush(stdin);
		gets(selezione);

		selezione_int=atoi(selezione);

		if(selezione_int>num_ingredienti){

			printf("\nHai selezionato un ingrediente non esistente,riprova");
		}

		}while(selezione_int>num_ingredienti);

		selezione_int--; //decremento di uno per allinearmi con l'array

	    for (i=selezione_int;i<num_ingredienti;i++){ 		//ciclo per copiare i valori nella posizione precedente,in modo da rimuovere l'alimento e non lasciare spazi vuoti nell'elenco

	       strcpy(archivio_ricette[ingrediente].ingredienti[i],archivio_ricette[ingrediente].ingredienti[i+1]);

	    }

	    num_ingredienti--;

	    sprintf(archivio_ricette[ingrediente].num_ingredienti, "%d", num_ingredienti);

	    file_save_ricette(num_linee);

	break;

	case 4:

		ricette();

	break;

	default:

    	messaggio_errore();
    	ricette();

    break;

	}

	printf("\n\n");
	system("pause");

}

/**
 * Questa procedura permette di modificare i passi di una ricetta.
 * @pre e' necessario accedere al sottomenu' di modifica di una ricetta e poi selezionare la modifica della procedura della ricetta
 * @pre devono esserci ricette all'interno dello Smart Fridge
 * @param step,ovvero il numero dello step che si intende modificare o eliminare
 */

void modifica_procedura(int step){

	num_linee=file_load_ricette();

	char selezione[10];
	int selezione_int;

	int selezione_menu;
	int i;

	char nuova_posizione[10]; //stringa che memorizza la posizione del nuovo step, qualora se ne dovesse aggiungere uno
	int nuova_posizione_int;  //conversione di "nuova_posizione" in intero

	char nuovo_dato[200];	  //stringa che memorizza temporaneamente il nuovo step che si andra' ad aggiungere o a sostituire al precedente
	char* nuovo_dato_low;	  //conversione in minuscolo di "nuovo_dato"
	int nuovo_dato_int;		  //conversione di "nuovo_dato" in intero se si tratta di un dato numerico

	int num_step;	 		  //contatore che viene incrementato, qualora venissero aggiunti steps alla ricetta

	char step_temp[4000];  //variabile temporanea in cui copiare uno step prima della copia
	char step_temp1[4000];  //variabile temporanea in cui copiare uno step prima della copia

	system("cls");
	printf("Che operazione vuoi eseguire?\n\n1)Aggiungi uno step\n2)Modifica uno step\n3)Rimuovi uno step\n4)Torna al menu'\n\n");

	fflush(stdin);

	scanf("%d",&selezione_menu);

	switch(selezione_menu){

	case 1:

		system("cls");
		printf("Elenco degli step\n\n");

		num_step=atoi(archivio_ricette[step].num_step);

		for(i=0;i<num_step;i++){

			printf("%d)%s\n",i+1,archivio_ricette[step].procedura[i]);

		}

		printf("\nInserire il nuovo step\n\n");
		fflush(stdin);
		gets(nuovo_dato);

		printf("\nInserire la posizione dello step\n\n");
		fflush(stdin);
		gets(nuova_posizione);

		if(isOnlyNumbers(nuova_posizione)==true) {

			messaggio_errore();
			modifica_procedura(step);

		}

        num_step=atoi(archivio_ricette[step].num_step);
        nuova_posizione_int=atoi(nuova_posizione);

        num_step++;

        sprintf(archivio_ricette[step].num_step, "%d", num_step);

        for(i=num_step;i>=nuova_posizione_int;i--){

        	strcpy(archivio_ricette[step].procedura[i],archivio_ricette[step].procedura[i-1]);

        }

        nuova_posizione_int--;

        strcpy(archivio_ricette[step].procedura[nuova_posizione_int],nuovo_dato);

        file_save_ricette(num_linee);

	break;

	case 2:

		system("cls");
		printf("Elenco degli step\n\n");

		num_step=atoi(archivio_ricette[step].num_step);

		for(i=0;i<num_step;i++){

			printf("%d)%s\n",i+1,archivio_ricette[step].procedura[i]);

		}

		do{

		printf("\n\nChe step si intende modificare?\n\n");
		fflush(stdin);
		gets(selezione);

		if(isOnlyNumbers(selezione)==true) {

			messaggio_errore();
			modifica_procedura(step);

		}

		selezione_int=atoi(selezione);

		if(selezione_int>num_step){

			printf("\nHai selezionato uno step non esistente,riprova");
		}

		}while(selezione_int>num_step);

		printf("\nInserire lo step modificato\n\n");
		fflush(stdin);
		gets(nuovo_dato);

		selezione_int--; //decremento di uno per allinearmi con l'array

        strcpy(archivio_ricette[step].procedura[selezione_int],nuovo_dato);

        file_save_ricette(num_linee);

	break;

	case 3:

		system("cls");
		printf("Elenco degli step\n\n");

		num_step=atoi(archivio_ricette[step].num_step);

		for(i=0;i<num_step;i++){

			printf("%d)%s\n",i+1,archivio_ricette[step].procedura[i]);

		}

		do{

		printf("\n\nChe step si intende rimuovere?\n\n");
		fflush(stdin);
		gets(selezione);

		selezione_int=atoi(selezione);

		if(selezione_int>num_step){

			printf("\nHai selezionato uno step non esistente,riprova");
		}

		}while(selezione_int>num_step);

		selezione_int--; //decremento di uno per allinearmi con l'array

	    for (i=selezione_int;i<num_step;i++){ 		//ciclo per copiare i valori nella posizione precedente,in modo da rimuovere l'alimento e non lasciare spazi vuoti nell'elenco

	       strcpy(archivio_ricette[step].procedura[i],archivio_ricette[step].procedura[i+1]);

	    }

	    num_step--;

	    sprintf(archivio_ricette[step].num_step, "%d", num_step);

	    file_save_ricette(num_linee);


	break;

	case 4:

		ricette();

	break;

	default:

    	messaggio_errore();
    	ricette();

    break;

	}

	printf("\n\n");
	system("pause");

}

/**
 * Questa procedura permette di rimuovere una ricetta dal sistema Smart Fridge.
 * @pre e' necessario accedere al sottomenu' della categoria "ricette" e selezionare "rimuovi una ricetta"
 * @post rimuove una ricetta
 *
 */

void rimuovi_ricette(){

    char selezione[10];
    int selezione_int;

    int valore_temp; //valore temporaneo per ciclare la copia di ingredienti e procedura

    int i;
    int j;

    system("cls");
    stampa_elenco_ricette(num_linee);

    printf("\n\nChe ricetta si desidera eliminare?Inserire un valore numerico:");

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

    for(i=selezione_int;i<num_linee;i++){

    	strcpy(archivio_ricette[i].nome,archivio_ricette[i+1].nome);
    	strcpy(archivio_ricette[i].difficolta,archivio_ricette[i+1].difficolta);
    	strcpy(archivio_ricette[i].num_preparazioni,archivio_ricette[i+1].num_preparazioni);
    	strcpy(archivio_ricette[i].kcal,archivio_ricette[i+1].kcal);

    	strcpy(archivio_ricette[i].num_ingredienti,archivio_ricette[i+1].num_ingredienti);

    	valore_temp=atoi(archivio_ricette[i].num_ingredienti);

    	for(j=0;j<valore_temp;j++){

    		strcpy(archivio_ricette[i].ingredienti[j],archivio_ricette[i+1].ingredienti[j]);
    	}

    	strcpy(archivio_ricette[i].num_step,archivio_ricette[i+1].num_step);

    	valore_temp=atoi(archivio_ricette[i].num_step);

    	for(j=0;j<valore_temp;j++){

    		strcpy(archivio_ricette[i].procedura[j],archivio_ricette[i+1].procedura[j]);
    	}


    }

    num_linee--;

    file_save_ricette(num_linee);
    printf("\n\n");
    system("pause");

}


//----------------------------------------------------------------------------
