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

#define LUNGH_MAX_NOME 50

int menu_inserito=false; //flag controllo inserimento menù della settimana

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
        //    statistiche();
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

  //  char temp_nome_file[40];
    int menu_select=0;
    int i;
    FILE *fp;

    fflush(stdin);
    system("cls");

    printf("Menu' settimanale:\n\n1)Visualizza o Inserisci\n2)Modifica\n3)Torna al menu' precedente\n\n");

    scanf("%d",&menu_select);

    switch(menu_select){

        case 1:

            if(menu_inserito==false){    //controllo se il menu' settimanale è stato già inserito.in caso contrario,do messaggio di errore

                /*	strcpy(temp_nome_file,"menu_sett.txt");	//caricamento del file menu

                    fp = fopen (temp_nome_file,"r");

                    if ((fp!=NULL) && (conta_linee(temp_nome_file)==7)){   //controllo la presenza del file. se il file è presente e vi sono 7 righe,il menu' è stato già inserito

                        menu_inserito=true;

                    }

                    fclose(fp);*/

                fflush(stdin);
                system("cls");
                printf("Il menu' della settimana non e' stato ancora definito.Vuoi definirlo ora?\n\n1)Si\n2)No\n\n");   //propongo l'inserimento del menu della settimana

                scanf("%d",&menu_select);

                switch(menu_select){

                    case 1:

                        fflush(stdin);
                        system("cls");

                        printf("Inserire il piatto del %s:",giorno[0].dayname);			//popolo il primo giorno della settimana
                        gets(giorno[0].pietanza);

                        for(i=1;i<7;i++){

                            fflush(stdin);
                            printf("\nInserire il piatto del %s:",giorno[i].dayname);		//popolo il resto della settimana
                            gets(giorno[i].pietanza);

                        }

                        menu_inserito=true;

                        file_save_menu_sett();

                        printf("\n---------------------------------\nTornerai ora al menu' precedente\n");
                        system("pause");
                        menu_sett();

                        break;

                    case 2:
                        menu_sett();
                        break;

                    default:
                        messaggio_errore();
                        menu_sett();
                        break;
                }
            }

            else if (menu_inserito==true){

                system("cls");

                file_load_menu_sett();

                for(i=0;i<7;i++){

                    printf("%-10s:%s\n\n",giorno[i].dayname,giorno[i].pietanza);

                }

                printf("\n---------------------------------\nTornerai ora al menu' precedente\n");
                system("pause");
                menu_sett();

            }

            break;

        case 2:
            //	ricette();
            break;

        case 3:
            varie();
            break;

        default:
            messaggio_errore();
            varie();
            break;

    }

}

void lista(){

    int menu_selez;
    int num_linee_lista;
    int i;

    system("cls");
    printf("Scegli un opzione\n\n1)Visualiza lista della spesa\n2)Aggiungi elemento alla lista\n3)Rimuovi elemento dalla lista\n4)Torna al menu' precedente\n\n");

    fflush(stdin);

    scanf("%d",&menu_selez);

    switch(menu_selez){

        case 1:

            system("cls");
            printf("Questa e' la lista della spesa generata automaticamente\n\n");

            num_linee_lista=conta_linee("lista_spesa.txt");

            file_load_lista(num_linee_lista);

            for(i=0;i<num_linee_lista;i++){

                printf("%d)%s\n",i+1,lista_spesa[i]);
            }

            printf("\n\n");
            system("pause");
            lista();

            break;

        case 2:

            break;

        case 3:

            break;

        case 4:
            varie();
            break;

        default:
            messaggio_errore();
            lista();
            break;
    }

}
/*
void statistiche(){

	int selezione;

	system("cls");
	printf("Qui puoi visualizzare gli alimenti più consumati e le ricette più preparate\nCosa vuoi visualizzare?\n\n1)Alimenti piu' consumati\n2)Ricette piu' preparate\n\n");

	scanf("%d",&selezione);

	switch(selezione){

		case 1:

			int num_linee;
			num_linee=file_load_consumazioni();

			system("cls");
			printf("Ecco un elenco dei 5 alimenti più consumati");

			ordinamento(num_linee,archivio_consumazioni.consumazioni,archivio_cons_ordinato.consumazioni);

	        printf("Elenco degli alimenti presenti in frigo\n\n|%-50s|%-12s|%-10s|%-10s|%-7s|","Alimento","Scadenza","Numero","Quantita'","KCAL");  //il valore negativo serve per l'allineamento a sinistra
	        printf("\n----------------------------------------------------------------------------------------------");

	        for(i=0;i<5;i++){

	                printf("\n|%-50s|%s|%d)",archivio_alimenti[i].nome,archivio_alimenti[i].giorno,archivio_alimenti[i].mese,archivio_alimenti[i].anno,archivio_alimenti[i].numero,temp_quantita,archivio_alimenti[i].kcal,i+1);

	            }

			break;

		case 2:

			break;

		default:
            messaggio_errore();
            statistiche();
			break;
	}

}
/*
void ordinamento(int num_linee,char array_num[],char array_dest_num[],char array_nomi[],char array_dest_nomi[]){

	int i;

	for(i=0;i<num_linee;i++){

		array_dest[i]=atoi(array_char[i]);  //converto i valori da ordinare da char a int

	}

	selection_sort(array_dest,num_linee);  //ordino i valori int

}

void selection_sort(int array_int[], int num_linee) {

	int i;
	int j;
	int p;
	int min;

	char nome_temp[LUNGH_MAX_NOME];

	for (i=0; i < num_linee-1; i++){

		min = array_int[i]; p = i; // p = posizione del minimo
		for (j = i+1; j < num_linee; j++) { // ricerca del minimo

				if (array_int[j] < min) {

					min = array_int[j]; // salva il minimo
					p = j; // aggiorna posizione del minimo

				}

				array_int[p] = array_int[i]; // scambio
				array_int[i] = min;


			}
	}

}*/
