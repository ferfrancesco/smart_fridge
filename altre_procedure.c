#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "alimenti.h"
#include "ricette.h"
#include "varie.h"
#include "CUnit/Basic.h"

//inclusione valori bool
typedef int bool;
#define true 1
#define false 0

#define LUNGH_MAX_NOME 50 //Lunghezza massima per il nome di un alimento

/**
 * Questa funzione verifica che una data stringa contenga solo numeri.
 *
 * @pre deve essere inserita una stringa che indica la stringa la cui composizione deve essere verificata
 * @post viene restituito un valore booleano, o vero o falso (che corrispondono rispettivamente ad un 1 o ad uno 0)
 */
int isOnlyNumbers(char* stringa){ // todo c'è un warning legato alla correttezza dei tipi

    int i;
    //int numero;

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

//TODO Controlla sta roba
//--------------------------------------------------------
/*È anche possibile inizializzare i valori alla dichiarazione, mettendo i valori (giusti nel tipo) compresi tra parentesi graffe:

struct libro biblio = {"Guida al C", "Fabrizio Ciacchi", 2003, 45.2};*/
//-----------------------------------------------------------------------

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

    printf("\n*************************\n5)TESTING CUnit\n*************************\n\n");

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

        case 5:
        	system("cls");
        	testing();
        	system("pause");
        	stampa_menu();
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


 /**
  * Questa procedura non fa altro che effettuare controlli sul calcolo delle consumazioni di ciascun alimento e sulla trascrizione dell'aggiornamento sul file "consumazioni.txt"
  * Vengono distinti diversi casi a seconda se l'alimento è già in lista consumazioni, se il file è vuoto, oppure se è già presente nel file.
  * Se il file è vuoto, si scrive l'alimento e le relative consumazioni
  * Se il file non è vuoto ma non esistono corrispondenze, si aggiunge il nome dell'alimento e le relative consumazioni
  * Se il file non è vuoto e viene trovata una corrispondenza, si aggiorna solo il dato relativo alle consumazioni.
  *
  * @param num_consumazioni, ovvero il numero di confezioni che si stanno eliminando di un dato alimento.
  * @param num_linee,ovvero di quante linee e' composto il file "consumazioni.txt".
  * @param stringa, ovvero il nome dell'alimento di cui si intende cercare la corrispondenza nel file "consumazioni.txt"
  */

void consumazioni(int num_consumazioni,int num_linee,char stringa[]){

	int i;
	int consumazioni_tot_int;//indica il numero totale di consumazioni di un dato alimento nella lista "consumazioni.txt"
	int trovato=0;  		 //flag che indica che l'alimento è già in lista o se è da aggiungere

	if (num_linee==0){		//se il file non esiste

		strcpy(archivio_consumazioni[num_linee].nome,stringa);

		consumazioni_tot_int=0;

		consumazioni_tot_int=consumazioni_tot_int+num_consumazioni;

		sprintf(archivio_consumazioni[num_linee].consumazioni ,"%d",consumazioni_tot_int);

		num_linee++;
	}

	for(i=0;i<num_linee;i++){ // se il file esiste e ...

		if(strcmp(archivio_consumazioni[i].nome,stringa)==0){ //...viene trovata una corrispondenza tra nomi

			consumazioni_tot_int=atoi(archivio_consumazioni[i].consumazioni);

			consumazioni_tot_int=consumazioni_tot_int+num_consumazioni;

			sprintf(archivio_consumazioni[i].consumazioni ,"%d",consumazioni_tot_int);

			trovato=1;

		}

	}

	if (trovato==0) {			// se non viene trovata nessuna corrispondenza tra nomi

		strcpy(archivio_consumazioni[num_linee].nome,stringa);

		consumazioni_tot_int=0;

		consumazioni_tot_int=consumazioni_tot_int+num_consumazioni;

		sprintf(archivio_consumazioni[num_linee].consumazioni ,"%d",consumazioni_tot_int);

		num_linee++;

	}

	file_save_consumazioni(num_linee);
}

/**
 * Questa procedura permette di ordinare, tramite un algoritmo "selection sort", l'array passato alla procedura,
 * in maniera decrescente.
 *
 * @pre dev'essere selezionata un'opzione che includa l'ordinamento di qualcosa
 * @post Si ha l'ordinamento di un vettore di interi, insieme ai nomi ad essi eventualmente associati
 *
 * @param array_int, ovvero l'array di interi del quale si deve effettuare l'ordinamento principale
 * @param array_nomi,ovvero l'array dei nomi corrispondenti ai numeri che devono essere ordinati
 * @param num_linee, ovvero il numero di linee di lui e' composto il file che deve essere ordinato
 */

void selection_sort(int array_int[],char array_nomi[CONSUM_MAX][LUNGH_MAX_NOME], int num_linee) {
//TODO L'ordinamento è sminchiato,controlla e fixa

	int i;
	int j;
	int max;

	int temp;
	char nome_temp[50];

	for (i=num_linee-1;i>0;i--){

		max=0;

		for (j=1;j<=i;j++) { // ricerca del max

				if (array_int[j] < max) {

					max=j;

				}

				//scambio il valore numericoo
				temp=array_int[max];
				array_int[max]=array_int[i];
				array_int[i]=temp;

				//scambio i nomi
				strcpy(nome_temp,array_nomi[max]);
				strcpy(array_nomi[max],array_nomi[i]);
				strcpy(array_nomi[i],nome_temp);
			}
	}

}

//------------------------------------------------------------------------------------------------------
//PROCEDURE TESTING CUNIT

/**
 * Funzione che introduce il testing con CUnit.
 * E' possibile accedervi selezionando la scelta 5 nel menu' principale.
 * Testa le asserzioni (Test Method) inserite in una o piu' "Test Suite" e ne valuta la verita' o la falsita'.
 * Vi sono diversi tipi di asserzione, a seconda di quale funzione si vuole testare.
 * Le funzioni testate sono "low_conversion", "stampa_stelle" e "isOnlyNumbers".
 * Le asserzioni sono raggruppate in un'unica Test Suite, la quale a sua volta si trova nel Test Registry allocato e deallocato all'inizio del programma.
 *
 *
 * @return CU_get_error();
 */


int testing(){

	char test1[50];

	//allocazione risorse
	int init_testA(void){

		return 0;
	}

	//deallocazione risorse
	int clean_testA(void){

		return 0;
	}

	//---------------------------------------------------------
	//PROCEDURE TEST
	void test_IsOnlyNumbers(void){

		CU_ASSERT_EQUAL(isOnlyNumbers("12"),false);
		CU_ASSERT_EQUAL(isOnlyNumbers("ciao"),true);
		CU_ASSERT_EQUAL(isOnlyNumbers("-1"),true);
		CU_ASSERT_EQUAL(isOnlyNumbers("a1"),true);
		CU_ASSERT_EQUAL(isOnlyNumbers("1a"),true);

	}



	void test_low_conversion(void){

		CU_ASSERT_STRING_EQUAL(low_conversion(strcpy(test1,"CIAO")),"ciao");
		CU_ASSERT_STRING_EQUAL(low_conversion(strcpy(test1,"CIAO")),"cia");
		CU_ASSERT_STRING_EQUAL(low_conversion(strcpy(test1,"CIao")),"ciao");
		CU_ASSERT_STRING_EQUAL(low_conversion(strcpy(test1,"ciao")),"ciao");
		CU_ASSERT_STRING_EQUAL(low_conversion(strcpy(test1,"1234")),"1234");
		CU_ASSERT_STRING_EQUAL(low_conversion(strcpy(test1,"12AB")),"12AB");
		CU_ASSERT_STRING_EQUAL(low_conversion(strcpy(test1,"12AB")),"12ab");
		CU_ASSERT_STRING_EQUAL(low_conversion(strcpy(test1,"&*.,")),"&*.,");
	}


	void test_stampa_stelle(void){

		CU_ASSERT_PTR_EQUAL(stampa_stelle(4),"****");

	}
	//--------------------------------------------------

	//inizializzazione registro cunit
	CU_initialize_registry();

	CU_pSuite pSuite_A = CU_add_suite("Test_A",init_testA, clean_testA);

	CU_add_test(pSuite_A, "test IsOnlyNumbers",test_IsOnlyNumbers);
	CU_add_test(pSuite_A, "test low_conversion",test_low_conversion);
	CU_add_test(pSuite_A, "test stampa_stelle",test_stampa_stelle);

	CU_basic_set_mode(CU_BRM_VERBOSE);

	CU_basic_run_tests();

	CU_cleanup_registry();

	return CU_get_error();

}
