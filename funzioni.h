#ifndef FUNZIONI_H
#define FUNZIONI_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void menu_difficolta (char *difficolta);
bool controllaSeGiusta (char lettera, char parola_nascosta [], char difficolta);
void stampaParola (char parola_nascosta [], char lettere_inserite [], char difficolta);
void trovaParola (char parola [], char difficolta, int *riga_casuale);
bool controllaVittoria(char parola[], char lettere_inserite[], char difficolta);
void chiediConferma(char *conferma);
void disegnaImpiccato (int vite);
char controllaLettera (char lettera, char lettere_inserite []);
void aggiornaLettereUsate (char lettera, char lettere_usate [], int *i);
void messaggioVittoria ();
void messaggioSconfitta ();
void assegnaPunteggio(int *punteggio, char difficolta, bool win);
void report_turno (int turno, char *parola, char difficolta, int punteggio);
void report_fine (int punteggio_totale, int turni, int parole_indovinate);
void stampaIndizio(int riga_indizio);

#endif