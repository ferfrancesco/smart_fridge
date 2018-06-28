#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "operazioni_file.h"
#include "operazioni_varie.h"
#include "alimenti.h"
#include "ricette.h"

//inclusione valori bool
typedef int bool;
#define true 1
#define false 0

char stelle[5]={0};

void ricette(){

    int i;

    int num_linee=file_load_ricette();
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

            if(controllo_numerico(selezione)==false) {

                ricette();

            }

            else if (controllo_numerico(selezione)==true){

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

            if(controllo_numerico(selezione)==false) {

                ricette();

            }

            else if (controllo_numerico(selezione)==true){

                strcpy(archivio_ricette[num_linee].difficolta,selezione);
            }

            /*---------------------------------------------------------------*/

            printf("\nQuanti ingredienti ha questa ricetta?(Inserire valori numerici):");
            gets(selezione);

            if(controllo_numerico(selezione)==false) {

                ricette();

            }

            else if (controllo_numerico(selezione)==true){

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

            if(controllo_numerico(selezione)==false) {

                ricette();

            }

            else if (controllo_numerico(selezione)==true){

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
    }

}

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

char* stampa_stelle(int num){

    int i;
    int int_difficolta;

    char stars[5]={0};  //definisco un array locale

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

