#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "alimenti.h"
#include "ricette.h"
#include "varie.h"

//inclusione valori bool
typedef int bool;
#define true 1
#define false 0

#define LUNGH_MAX_NOME 50 //Luneghezza massima per il nome di un alimento

/**
 * Questa funzione verifica che una data stringa contenga solo numeri.
 *
 * @pre deve essere inserita una stringa che indica la stringa la cui composizione deve essere verificata
 * @post viene restituito un valore booleano, o vero o falso (che corrispondono rispettivamente ad un 1 o ad uno 0)
 */
int isOnlyNumbers(char* stringa){ // todo c'è un warning legato alla correttezza dei tipi

    int i;
    int numero;

    for(i=0;i<strlen(stringa);i++){

        if(isdigit(stringa[i])==false){

            return true;

        }

        else if(isdigit(stringa[i])==true){

            return false;

        }

    }

}

/**
 * Questa procedura stampa un messaggio di errore, utile in diverse funzioni
 *
 */

void messaggio_errore(){

    system("cls");
    printf("Selezione Errata.Inserire una cifra numerica (1,2,3,4,...)\n");
    system("pause");
    fflush(stdin);

}

/**
 * Questa procedura copia i nomi dei giorni della settimana nella struct "giorno"
 */

void dayname_fill(){

    strcpy(giorno[0].dayname,"Lunedi'");
    strcpy(giorno[1].dayname,"Martedi'");
    strcpy(giorno[2].dayname,"Mercoledi'");
    strcpy(giorno[3].dayname,"Giovedi'");
    strcpy(giorno[4].dayname,"Venerdi'");
    strcpy(giorno[5].dayname,"Sabato");
    strcpy(giorno[6].dayname,"Domenica");

}

/**
 * Questa procedura stampa il menu principale dello Smart Fridge.
 *
 */

void stampa_menu(){

    int menu_select=0;

    time_t orario;
    char* stringa_ora;

    orario = time(NULL);

    /* Convert to local time format. */
    stringa_ora = ctime(&orario);

    fflush(stdin);		//termina lo stream di scanf
    system("cls");

    printf("Benvenuto nel tuo Smart Fridge\n");

    printf("%s",stringa_ora);

    printf("\n\nSeleziona una categoria\n\n1)Alimenti\n2)Ricette\n3)Varie\n4)Spegni il sistema\n\n");

    //memos();

    scanf("%d",&menu_select);

    switch(menu_select){

        case 1:
            alimenti();
            break;

        case 2:
            ricette();
            break;

        case 3:
            varie();
            break;

        case 4:
            exit(1);
            break;

        default:
            messaggio_errore();
            stampa_menu();
            break;
    }

}

/**
 * Procedura che stampa eventuali promemoria inseriti nello Smart Fridge
 *
 */
void memos(){

    printf("\n\n---------------------------------------------\n\nSEZIONE MEMOS");
}

/**
 * Questa funzione trasforma una stringa ,eventualmente scritta anche in lettere maiuscole,
 * in lettere minuscole.
 *
 * @pre la stringa deve essere composta di lettere.
 * @param stringa, ovvero la stringa da convertire
 * @return stringa, la stringa convertita
 */
char* low_conversion(char stringa[]){

	int i;

	for(i=0;i<strlen(stringa);i++){

		stringa[i]=tolower(stringa[i]);

	}

	return stringa;
}

void consumazioni(int num_consumazioni,int num_linee,char stringa[]){

	int i;
	int consumazioni_tot_int;
	int trovato=0;  //flag che indica che l'alimento è già in lista o se è da aggiungere

	if (num_linee==0){

		strcpy(archivio_consumazioni[num_linee].nome,stringa);

		consumazioni_tot_int=0;

		consumazioni_tot_int=consumazioni_tot_int+num_consumazioni;

		sprintf(archivio_consumazioni[num_linee].consumazioni ,"%d",consumazioni_tot_int);

		num_linee++;
	}

	for(i=0;i<num_linee;i++){

		if(strcmp(archivio_consumazioni[i].nome,stringa)==0){

			consumazioni_tot_int=atoi(archivio_consumazioni[i].consumazioni);

			consumazioni_tot_int=consumazioni_tot_int+num_consumazioni;

			sprintf(archivio_consumazioni[i].consumazioni ,"%d",consumazioni_tot_int);

			trovato=1;

		}

	}

	if (trovato==0) {

		strcpy(archivio_consumazioni[num_linee].nome,stringa);

		consumazioni_tot_int=0;

		consumazioni_tot_int=consumazioni_tot_int+num_consumazioni;

		sprintf(archivio_consumazioni[num_linee].consumazioni ,"%d",consumazioni_tot_int);

		num_linee++;

	}

	file_save_consumazioni(num_linee);
}

