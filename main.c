#include "funzioni.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define IndovinaLettera     1
#define LettereErrate       2
#define Informazioni        3
#define ChiediIndizio       4
#define Abbandona           5
#define MAX_LEN             40
#define MAX_LEN_ALF         27

int main() {
    char parola[MAX_LEN];
    char lettere_usate[MAX_LEN_ALF] = {'\0'};
    char lettera;
    bool gioco_in_corso = true;
    int vite = 6;
    int indice_lettere_usate = 0;
    int indice_parola;
    int punteggio = 0;
    int punteggio_totale = 0;
    int turno = 1;
    int indizi = 3;
    int n_parole_indovinate = 0;
    int scelta;
    char difficolta;
    char conferma;

    srand(time(NULL));

    // Messaggio di benvenuto e istruzioni del gioco
    printf("Benvenuto al gioco dell'impiccato!\n");
    printf("Scopri la parola nascosta indovinando le lettere una alla volta.\n");
    printf("Per ogni lettera sbagliata, perderai una vita. Cerca di indovinare la parola prima di esaurirle!\n");
    
    // Selezione della difficoltà e ricerca della parola da indovinare
    menu_difficolta(&difficolta);
    trovaParola(parola, difficolta, &indice_parola);

    while (gioco_in_corso) {
        // Disegno dell'impiccato e stampa della parola indovinata fino a quel momento
        disegnaImpiccato(vite);
        stampaParola(parola, lettere_usate, difficolta);

        // Menu principale 
        printf("\n\n---------------------------------\n");
        printf("1. Indovina una lettera\n");
        printf("2. Mostra lettere errate\n");
        printf("3. Mostra informazioni\n");
        printf("4. Chiedi indizio\n");
        printf("5. Abbandona\n");
        printf("---------------------------------\n");

        do {
            printf("\nInserisci scelta: ");
            if (scanf("%d", &scelta) != 1) {
                // Gestione dell'input non valido
                while (getchar() != '\n'); // Consuma tutti i caratteri fino a newline
                printf("\nErrore: inserire una scelta valida!");
                scelta = 0; // scelta invalida per rientrare nel do while
            } else if (scelta < 1 || scelta > 5) {
                printf("\nErrore: inserire una scelta valida!");
            }
        } while (scelta < 1 || scelta > 5);

        switch (scelta) {
            case IndovinaLettera:
                // Chiedi al giocatore di inserire una lettera e controlla se è corretta
                do {
                    printf("\nInserisci una lettera: ");
                    scanf(" %c", &lettera);
                    getchar(); // pulisci il buffer                    
                    lettera = controllaLettera(lettera, lettere_usate);
                } while (lettera == 0);

                // Aggiorna le lettere usate e controlla se la lettera è presente nella parola
                aggiornaLettereUsate(lettera, lettere_usate, &indice_lettere_usate);
                bool lettera_giusta = controllaSeGiusta(lettera, parola, difficolta);
                if (lettera_giusta) 
                    printf("\nLa lettera '%c' è corretta!\n", lettera);
                else {
                    printf("\nLa lettera '%c' è sbagliata!\n", lettera); 
                    vite--;
                }
                break;
            case LettereErrate:
                // Mostra le lettere errate
                int LEN_PAROLA = strlen(parola);
                int LEN_LET_USATE = strlen(lettere_usate);
                bool trovata;
                printf("\nLettere errate:\n");
                for (int i = 0; i < LEN_LET_USATE; i++) {
                    trovata = false;
                    for (int j = 0; j < LEN_PAROLA; j++) {
                        if ((difficolta != 'I' && j == 0) || (difficolta != 'I' && j == LEN_PAROLA - 1))
                            continue;
                        if (lettere_usate[i] == parola[j]) { 
                            trovata = true;
                            break;
                        }
                    }
                    if (!trovata) {
                        printf("%c ", lettere_usate[i]); 
                    }
                }
                printf("\n");
                break;
            case Informazioni:
                // Mostra le informazioni sullo stato attuale del gioco
                printf("\nPunteggio totale: %d", punteggio_totale);
                printf("\nVite rimaste: %d", vite);
                printf("\nIndizi rimasti: %d", indizi);
                printf("\nLunghezza parola: %d", strlen(parola));
                printf("\nDifficoltà: ");
                if (difficolta == 'E')
                    printf("Easy\n");
                if (difficolta == 'M')
                    printf("Medium\n");
                if (difficolta == 'H')
                    printf("Hard\n");
                if (difficolta == 'I')
                    printf("Impossible\n");
                break;
            case ChiediIndizio:
                // Gestione della richiesta di indizi
                if (!indizi) {
                    printf("Hai 0 indizi rimasti!\nVuoi comprare 1 indizio per 1000 punti? (S/N): ");
                    chiediConferma(&conferma);
                    if (conferma == 'S' && punteggio_totale < 1000) {
                        printf("Non hai abbastanza punti!");
                        break;
                    }
                    else if (conferma == 'S') {
                        indizi++;
                        punteggio_totale -= 1000;
                        printf("Hai comprato un indizio!");
                    } else break;
                }
                printf("Hai %d indizi rimasti! Vuoi usarne 1? (S/N): ", indizi);
                chiediConferma(&conferma);
                if (conferma == 'S') {
                    printf("\nIndizio:\n");
                    stampaIndizio(indice_parola);
                    indizi--;
                }
                break;
            case Abbandona:
                // Abbandono del gioco
                printf("\nSei sicuro di voler abbandonare? (S/N): ");
                chiediConferma(&conferma);
                if (conferma == 'S') {
                    messaggioSconfitta();
                    printf("\nLa parola da indovinare era: %s", parola);
                    assegnaPunteggio(&punteggio, difficolta, false);
                    punteggio_totale += punteggio;
                    report_turno(turno, parola, difficolta, punteggio);
                    gioco_in_corso = false;
                }
        }
    
    // Verifica se il giocatore ha esaurito le vite o ha indovinato la parola
    if (vite == 0) {
        messaggioSconfitta();
        printf("\nLa parola da indovinare era: %s", parola);
        assegnaPunteggio(&punteggio, difficolta, false);
        punteggio_totale += punteggio;
        report_turno(turno, parola, difficolta, punteggio);
        gioco_in_corso = false;
    }
    if (controllaVittoria(parola, lettere_usate, difficolta)) {
        messaggioVittoria();
        n_parole_indovinate++;
        printf("\nLa parola da indovinare era: %s", parola);
        assegnaPunteggio(&punteggio, difficolta, true);
        punteggio_totale += punteggio;
        report_turno(turno, parola, difficolta, punteggio);
        gioco_in_corso = false;
    }

    if (!gioco_in_corso) {
        // Menu finale per giocare di nuovo o uscire
        printf("\n\n----------------------------\n");
        printf("1. Gioca ancora\n");
        printf("2. Esci\n");
        printf("----------------------------\n");

        do {
            printf("\nInserisci una scelta: ");
            if (scanf("%d", &scelta) != 1) {
                // Gestione dell'input non valido
                while (getchar() != '\n'); // Consuma tutti i caratteri fino a newline
                printf("\nErrore: inserire una scelta valida!");
            } else if (scelta < 1 || scelta > 2)
                printf("\nErrore: inserire una scelta valida!");
        } while (scelta < 1 || scelta > 2);

        if (scelta == 1) {
            // Reset delle variabili di gioco per iniziare una nuova partita
            vite = 6; 
            strcpy(lettere_usate, ""); 
            strcpy(parola, "");
            indice_lettere_usate = 0;

            // Incremento del turno
            turno++;

            // Reimposta gioco_in_corso a true per rientrare nel ciclo di gioco
            gioco_in_corso = true; 

            printf("Vuoi cambiare difficoltà? (S/N): ");
            chiediConferma(&conferma);
            if (conferma == 'S')
                menu_difficolta(&difficolta);
            trovaParola(parola, difficolta, &indice_parola);

            
        }
    }
}
    
    // Stampa del report finale e uscita dal gioco
    report_fine(punteggio_totale, turno, n_parole_indovinate);
    printf("\nSei uscito.\nGrazie per aver giocato!");
    return 0;
}