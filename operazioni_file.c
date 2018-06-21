#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

//inclusione valori bool
typedef int bool;
#define true 1
#define false 0

//OPERAZIONI VARIE
int conta_linee(char nome_file[40]){

    int num_linee=0;

    FILE *fp;
    fp = fopen (nome_file,"r");

    if (fp==NULL){			//controllo presenza file
        printf("\n Errore nel caricamento del file");
        exit(1);
    }

    while(!feof(fp)){

        if(fgetc(fp) == '\n')
            num_linee++;   //conta il numero di linee,cercando un eventuale /n

    }

    fclose(fp);

    return num_linee;
}

void to_und_conversion(char stringa[]){

    int i;

    for(i=0;i<strlen(stringa);i++){

        if(stringa[i]==' ')
            stringa[i]='_';

    }
}

void to_space_conversion(char stringa[]){

    int i;

    for(i=0;i<strlen(stringa);i++){

        if(stringa[i]=='_')
            stringa[i]=' ';

    }
}


//OPERAZIONI DI CARICAMENTO DEI FILE
int file_load_alimenti(){

    int i=0;
    int num_linee=0;

    FILE *fp;
    fp = fopen ("alimenti.txt","r");

    if (fp==NULL){			//controllo presenza file
        system("cls");
        printf("Errore nel caricamento del file\n");
        system("pause");
        exit(1);
    }

    while(!feof(fp)){

        fscanf(fp,"%50[^,],%12[^,],%15[^,],%5[^,],%10[^,],%15[^,],\n",archivio_alimenti[i].nome,archivio_alimenti[i].data,archivio_alimenti[i].numero,archivio_alimenti[i].tipo,archivio_alimenti[i].quantita,archivio_alimenti[i].kcal);	//utilizzo [^,] in quanto utilizzare %s leggeva l'intera stringa,virgole incluse,

        i++;
        num_linee++;

        to_space_conversion(archivio_alimenti[i].nome);

    }

    fclose(fp);

    return num_linee;

}

int file_load_ricette(){

    int i=0;
    int j=0;
    int temp_int=0; //per la conversione da char a int per l'uso nel ciclo di acquisizione
    int num_linee=0;

    FILE *fp;
    fp = fopen ("ricette.txt","r");

    if (fp==NULL){			//controllo presenza file
        system("cls");
        printf("Errore nel caricamento del file\n");
        system("pause");
        exit(1);
    }

    while(!feof(fp)){

        fscanf(fp,"%50[^,],%5[^,],%5[^,],",archivio_ricette[i].nome,archivio_ricette[i].difficolta,archivio_ricette[i].num_ingredienti); //utilizzo [^,] in quanto utilizzare %s leggeva l'intera stringa,virgole incluse

        temp_int = atoi(archivio_ricette[i].num_ingredienti);  //converto il numero di step in intero per l'uso nel ciclo

        for(j=0;j<temp_int;j++){

            fscanf(fp,"%100[^,],",archivio_ricette[i].ingredienti[j]);  //acquisizione degli ingredienti

        }

        fscanf(fp,"%5[^,],",archivio_ricette[i].num_step);

        temp_int = atoi(archivio_ricette[i].num_step);

        for(j=0;j<temp_int;j++){

            fscanf(fp,"%4000[^,],\n",archivio_ricette[i].procedura[j]);

        }

       i++;
       num_linee++;

    }

    fclose(fp);

    return num_linee;

}

int file_load_menu_sett(){

    int i;
    int num_linee=conta_linee("menu_sett.txt");

    FILE *fp;
    fp = fopen ("menu_sett.txt","r");

    if (fp==NULL){			//controllo presenza file
        printf("\n Errore nel caricamento del file");
        exit(1);
    }

    while(!feof(fp)){

        for	(i=0;i<7;i++){

            fscanf(fp,"%s\n",giorno[i].pietanza);	//utilizzo [^,] in quanto utilizzare %s leggeva l'intera stringa,virgole incluse,

            to_space_conversion(giorno[i].pietanza);

        }

    }

    fclose(fp);

    return num_linee;

}

int file_load_lista(int num_linee){

    int i;

    FILE *fp;
    fp = fopen ("lista_spesa.txt","r");

    if (fp==NULL){			//controllo presenza file
        printf("\n Errore nel caricamento del file");
        exit(1);
    }

    //while(!feof(fp)){

    for	(i=0;i<num_linee;i++){

        fscanf(fp,"%[^,]\n",lista_spesa[i]);	//utilizzo [^,] in quanto utilizzare %s leggeva l'intera stringa,virgole incluse,

        to_space_conversion(lista_spesa[i]);

        //	}

    }

    fclose(fp);

    return num_linee;

}


//OPERAZIONI DI SALVATAGGIO DEI FILE
void file_save_alimenti(int num_linee){

    FILE *fp;
    int i;

    fp = fopen ("alimenti.txt","w");  //apro il file per aggiungere elementi

    for(i=0;i<num_linee;i++){

        to_und_conversion(archivio_alimenti[i].nome);   //converto il nome con gli underscore per prepararlo al salvataggio su file

        fprintf(fp,"%s,%s,%s,%s,%s,%s,\n",archivio_alimenti[i].nome,archivio_alimenti[i].data,archivio_alimenti[i].numero,archivio_alimenti[i].tipo,archivio_alimenti[i].quantita,archivio_alimenti[i].kcal);

        to_space_conversion(archivio_alimenti[i].nome);  //riporto il nome da underscore a spazi

    }

    fclose(fp);
}

void file_save_ricette (int num_linee){

    FILE *fp;
    int i=0;
    int j=0;
    int temp_int=0;

    fp = fopen ("ricette.txt","w");  //apro il file per aggiungere elementi

    for(i=0;i<num_linee;i++){

        fprintf(fp,"%s,%s,%s,",archivio_ricette[i].nome,archivio_ricette[i].difficolta,archivio_ricette[i].num_ingredienti);

        temp_int = atoi(archivio_ricette[i].num_ingredienti);  //converto il numero di step in intero per l'uso nel ciclo

        for(j=0;j<temp_int;j++){

            fprintf(fp,"%s,",archivio_ricette[i].ingredienti[j]);  //acquisizione degli ingredienti

        }

        fprintf(fp,"%s,",archivio_ricette[i].num_step);

        temp_int = atoi(archivio_ricette[i].num_step);

        for(j=0;j<temp_int;j++){

            fprintf(fp,"%s,",archivio_ricette[i].procedura[j]);

        }

        fprintf(fp,"\n");
    }

    fclose(fp);

}

void file_save_menu_sett(){

    FILE *fp;
    int i;

    fp = fopen ("menu_sett.txt","w");

    for(i=0;i<7;i++){

        to_und_conversion(giorno[i].pietanza);   //converto il nome con gli underscore per prepararlo al salvataggio su file

        fprintf(fp,"%s\n",giorno[i].pietanza);

        to_space_conversion(giorno[i].pietanza);  //riporto il nome da underscore a spazi

    }

    fclose(fp);

}


