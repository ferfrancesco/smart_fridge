#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "operazioni_file.h"
#include "operazioni_varie.h"
#include "alimenti.h"

//inclusione valori bool
typedef int bool;
#define true 1
#define false 0

void alimenti(){

    int num_linee=file_load_alimenti();
    int menu_select=0;
    int i;
    int alimenti_temp; //variabile di appoggio
    char selezione[10]; //alimento selezionato
    int selezione_int; //selezione in forma di intero
   // int alimenti_selez;

    fflush(stdin);
    system("cls");

    printf("Menu' Alimenti\nSeleziona un opzione\n\n1)Visualizza alimenti presenti in frigo\n2)Aggiungi un alimento\n3)Modifica le quantita' presenti\n4)Torna al menu'\n\n");

    scanf("%d",&menu_select);

    switch(menu_select){

        case 1:

            stampa_alimenti(num_linee);

            system("pause");
            fflush(stdin);

            alimenti();

            break;

        case 2:

            system("cls");
            printf("Quanti alimenti vuoi aggiungere?Inserire un valore numerico\n\n");
            fflush(stdin);

            gets(selezione);

            if(controllo_numerico(selezione)==false) {

                alimenti();

            }

            else if (controllo_numerico(selezione)==true){

                selezione_int=atoi(selezione);
            }

            for(i=0;i<selezione_int;i++){

                system("cls");
                fflush(stdin);

                printf("Inserire il nome dell'alimento:");
                gets(archivio_alimenti[num_linee].nome);

                printf("\nInserire la scadenza dell'alimento nel formato (dd/mm/yyyy):");
                gets(archivio_alimenti[num_linee].data);

                printf("\nInserire la quantita' dell'alimento inserito:");
                gets(archivio_alimenti[num_linee].numero);

                printf("\nInserire la tipologia di misura dell'alimento:\n\n1)Solido [GRAMMI]\n2)Liquido [MILLILITRI]\n\n");
                gets(archivio_alimenti[num_linee].tipo);

                alimenti_temp = atoi(archivio_alimenti[num_linee].tipo);

                switch(alimenti_temp){

                    case 1:

                        printf("\nQual'e' la quantita' in g del singolo elemento?[GRAMMI]:");
                        gets(archivio_alimenti[num_linee].quantita);

                        break;

                    case 2:

                        printf("\nQual'e' la quantita' in ml del singolo elemento?[MILLILITRI]:");
                        gets(archivio_alimenti[num_linee].quantita);

                        break;

                }

                printf("\nInserire le KCAL dell'alimento:");
                gets(archivio_alimenti[num_linee].kcal);

                num_linee++;  //incremento il numero di linee del file,in modo da non sovrascrivere alimenti precedenti

                file_save_alimenti(num_linee);

            }

            printf("\n\n");
            system("pause");
            alimenti();


            break;

        case 3:

            stampa_alimenti(num_linee);

            printf("Di quale alimento si intende modificare le quantita' presenti?\n\nSe vuoi rimuovere un elemento dal frigo,digita una quantita' '0'\n\nDigitane il numero ad esso associato:");

            fflush(stdin);

            gets(selezione);

            if(controllo_numerico(selezione)==false) {

                alimenti();

            }

            else if (controllo_numerico(selezione)==true){

                selezione_int=atoi(selezione);
            }

            selezione_int=selezione_int-1; //diminuisco il valore di 1 per allinearmi con l'array,in quanto l'utente vede e seleziona valori shiftati di 1,per evitare che vi sia un alimento indicato col valore 0

            printf("\nInserire la nuova quantita':");

            gets(archivio_alimenti[selezione_int].quantita);

            if(strcmp(archivio_alimenti[selezione_int].quantita,"0")==0 ){             //nel caso venga inserito un valore pari a zero nel campo quantita',l'alimento verrà automaticamente rimosso

                FILE *fp;
                fp = fopen ("lista_spesa.txt","a");

                to_und_conversion(archivio_alimenti[selezione_int].nome);

                fprintf(fp,"%s,\n",archivio_alimenti[selezione_int].nome);

                to_space_conversion(archivio_alimenti[selezione_int].nome);

                fclose(fp);

                for (i=selezione_int;i<num_linee;i++){

                    strcpy(archivio_alimenti[i].nome,archivio_alimenti[i+1].nome);           //copio i valori nella posizione precedente,in modo da rimuovere l'alimento e non lasciare buchi nell'elenco
                    strcpy(archivio_alimenti[i].data,archivio_alimenti[i+1].data);
                    strcpy(archivio_alimenti[i].quantita,archivio_alimenti[i+1].quantita);
                    strcpy(archivio_alimenti[i].kcal,archivio_alimenti[i+1].kcal);


                }

                num_linee--;

                file_save_alimenti(num_linee); //aggiorno il contenuto del file

                printf("\n\n");
                system("pause");
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

}

void stampa_alimenti(int num_linee){


    fflush(stdin);
    system("cls");
    int i;
    char temp_quantita[10]; //variabile temporanea per la visualizzazione della quantita' in g o ml

    if (num_linee==0){

        printf("Il frigo e' vuoto!\n\n");
        system("pause");
        // alimenti();

    }

    else{

        printf("Elenco degli alimenti presenti in frigo\n\n|%-50s|%-11s|%-10s|%-10s|%-7s|","Alimento","Scadenza","Numero","Quantita'","KCAL");  //il valore negativo serve per l'allineamento a sinistra
        printf("\n----------------------------------------------------------------------------------------------");

        for(i=0;i<num_linee;i++){

            if(strcmp(archivio_alimenti[i].tipo,"1")){

                strcpy(temp_quantita,archivio_alimenti[i].quantita);
                strcat(temp_quantita," ml");

                printf("\n|%-50s|%-11s|%-10s|%-10s|%-7s|%d)",archivio_alimenti[i].nome,archivio_alimenti[i].data,archivio_alimenti[i].numero,temp_quantita,archivio_alimenti[i].kcal,i+1);

            }

            else if(strcmp(archivio_alimenti[i].tipo,"2")){

                strcpy(temp_quantita,archivio_alimenti[i].quantita);
                strcat(temp_quantita," g");

                printf("\n|%-50s|%-11s|%-10s|%-10s|%-7s|%d)",archivio_alimenti[i].nome,archivio_alimenti[i].data,archivio_alimenti[i].numero,temp_quantita,archivio_alimenti[i].kcal,i+1);

            }

        }

        printf("\n----------------------------------------------------------------------------------------------\n\n");

    }

}
