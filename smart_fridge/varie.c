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
#include "varie.h"

//inclusione valori bool
typedef int bool;
#define true 1
#define false 0

int menu_inserito=false; //flag controllo inserimento menù della settimana

void varie(){

    int menu_select=0;

    fflush(stdin);
    system("cls");

    printf("Menu' Varie\nSeleziona un opzione\n\n1)Imposta il menu' della settimana\n2)Genera Lista della spesa\n3)Torna al menu'\n\n");

    scanf("%d",&menu_select);

    switch(menu_select){

        case 1:
            menu_sett();
            break;

        case 2:
            lista();
            break;

        case 3:
            stampa_menu();
            break;

        default:
            messaggio_errore();
            varie();
            break;

    }

}

void memos(){

    printf("\n\n---------------------------------------------\n\nSEZIONE MEMOS");
}

void menu_sett(){

    char temp_nome_file[40];
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

                    if (/*(fp!=NULL) && (conta_linee(temp_nome_file)==7)){   //controllo la presenza del file. se il file è presente e vi sono 7 righe,il menu' è stato già inserito

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

