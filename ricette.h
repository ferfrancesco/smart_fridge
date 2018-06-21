#ifndef RICETTE_H_
#define RICETTE_H_
#endif /* RICETTE_H_ */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

void ricette();
void stampa_elenco_ricette(int num_linee);
char* stampa_stelle(int num); //stampa le stellette di difficolta',int num indica il numero della ricetta
void stampa_ricetta(int num);
