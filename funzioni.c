#include "funzioni.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

// Mostra le opzioni di difficoltà, quindi chiede una scelta e ne controlla la validità
void menu_difficolta (char *difficolta) {
    printf("\n---------------------------\n");
    printf("1. Easy\n");
    printf("2. Medium\n");
    printf("3. Hard\n");
    printf("4. Impossible\n");
    printf("5. Random\n");
    printf("---------------------------\n");
    
    int scelta;

    do {
        printf("\nInserisci difficoltà: ");
        if (scanf("%d", &scelta) != 1) {
            // Se scanf non riesce a leggere un intero, pulisci il buffer di input
            while (getchar() != '\n'); // Consuma tutti i caratteri fino a newline
            printf("\nErrore: inserire una scelta valida!");
        } else if(scelta < 1 || scelta > 5)
            printf("\nErrore: inserire una scelta valida!");
    } while (scelta < 1 || scelta > 5);

    switch (scelta) {
        case 1:
            *difficolta = 'E';
            break;
        case 2:
            *difficolta = 'M';
            break;
        case 3:
            *difficolta = 'H';
            break;
        case 4:
            *difficolta = 'I';
            break;
        case 5:
            int x = rand() % 100; // Genera un numero casuale tra 0 e 99
            if (x < 40)
                *difficolta = 'E'; // 40% di probabilità
            else if (x < 70)
                *difficolta = 'M'; // 30% di probabilità
            else if (x < 90)
                *difficolta = 'H'; // 20% di probabilità
            else
                *difficolta = 'I'; // 10% di probabilità
    }
}

// Controlla se una lettera è corretta rispetto alla parola nascosta, considerando la difficoltà
bool controllaSeGiusta (char lettera, char parola_nascosta [], char difficolta) {
    int len = strlen(parola_nascosta);
    for (int i = 0; parola_nascosta[i] != '\0'; i++) {
        if((difficolta != 'I' && i == 0) || (difficolta != 'I' && i == len-1))
            continue;
        if (lettera == parola_nascosta[i])
            return true;
    }
    return false;
}

// Stampa la parola nascosta, mostrando solo le lettere corrette e nascondendo le altre (tenendo conto anche della difficolta)
void stampaParola(char parola_nascosta[], char lettere_inserite[], char difficolta) {
    printf("\n");
    for (int i1 = 0; parola_nascosta[i1] != '\0'; i1++) {
        int trovato = 0; // Inizializza trovato a 0 per ogni lettera della parola
        if ((difficolta == 'E' || difficolta == 'M' || difficolta == 'H') && (i1 == 0 || parola_nascosta[i1 + 1] == '\0')) {
            printf("%c ", parola_nascosta[i1]);
            continue; // Salta il controllo delle lettere inserite
        }
        for (int i2 = 0; lettere_inserite[i2] != '\0'; i2++) {
            if (parola_nascosta[i1] == lettere_inserite[i2]) {
                trovato = 1; // Se trovi la lettera, imposta trovato a 1
                break; // Esci dal loop interno
            }
        }
        // Se la lettera è stata trovata, stampala, altrimenti stampa '_'
        if (trovato) {
            printf("%c ", parola_nascosta[i1]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

// Trova una parola casuale in dizionario.txt, basata sulla difficoltà specificata
void trovaParola (char parola [], char difficolta, int *riga_casuale) {
    FILE *pF = fopen("dizionario.txt", "r");
    
    int num_righe = 50; // numero di righe (o parole) per difficoltà
    int prima_riga;

    switch(difficolta) {
        case 'E': 
            prima_riga = 1;
            break;
        case 'M': 
            prima_riga = 52;
            break;
        case 'H': 
            prima_riga = 103;
            break;
        case 'I': 
            prima_riga = 154;
    }

    *riga_casuale = (rand () % num_righe) + prima_riga;
    int riga_corrente = 0;

    while (fgets(parola, 40, pF) != NULL) {
        riga_corrente++;
        if (riga_corrente == *riga_casuale) {
            // Rimuovi il carattere di newline dalla fine della riga
            if (parola[strlen(parola) - 1] == '\n') {
                parola[strlen(parola) - 1] = '\0';
            }
            break;
        }
    }

    fclose(pF);
}

// Controlla se tutte le lettere della parola sono state indovinate (tenendo conto della difficolta)
bool controllaVittoria(char parola[], char lettere_inserite[], char difficolta) {
    int len_parola = strlen(parola);
    int len_lettere_inserite = strlen(lettere_inserite);

    for (int i = 0; i < len_parola; i++) {
        // se la difficolta non è 'I' (Impossible) salta il controllo della prima e dell'ultima lettera della parola da indovinare
        if ((difficolta != 'I' && i == 0) || (difficolta != 'I' && i == len_parola - 1))
            continue;
        
        bool trovata = false;
        for (int j = 0; j < len_lettere_inserite; j++) {
            if (parola[i] == lettere_inserite[j]) {
                trovata = true;
                break;
            }
        }
        
        if (!trovata) {
            return false; // Se anche una sola lettera della parola non è stata trovata, restituisci false
        }
    }
    
    return true; // Se tutte le lettere della parola sono state trovate, restituisci true
}

// Richiede conferma all'utente, assicurandosi che la risposta sia valida
void chiediConferma(char *conferma) {
    do {
        // chiedi conferma
        scanf(" %c", conferma);
        getchar(); // pulisci il buffer

        // converti in maiuscolo se necessario 
        if (*conferma == 's' || *conferma == 'n')
            *conferma -= ('a' - 'A');

        // se la conferma non è valida, dai errore
        if (*conferma != 'S' && *conferma != 'N')
            printf("Errore: inserire una scelta valida\n");
                    } while (*conferma != 'S' && *conferma != 'N');
}

// Disegna la rappresentazione grafica dell'impiccato in base alle vite rimanenti
void disegnaImpiccato (int vite)  {
    switch (vite) {
        case 6:
            printf("\n  ------\n  |    |\n  |\n  |\n  |\n  |\n-----\n");
            break;
        case 5:
            printf("\n  ------\n  |    |\n  |    O\n  |\n  |\n  |\n-----\n");
            break;
        case 4:
            printf("\n  ------\n  |    |\n  |    O\n  |    |\n  |    |\n  |\n-----\n");
            break;
        case 3:
            printf("\n  ------\n  |    |\n  |    O\n  |   /|\n  |    |\n  |\n-----\n");
            break;
        case 2:
            printf("\n  ------\n  |    |\n  |    O\n  |   /|\\\n  |    |\n  |\n-----\n");
            break;
        case 1:
            printf("\n  ------\n  |    |\n  |    O\n  |   /|\\\n  |    |\n  |   / \n-----\n");
            break;
        case 0:
            printf("\n  ------\n  |    |\n  |    O\n  |   /|\\\n  |    |\n  |   / \\\n-----\n");
            break;
    }
}

// Aggiorna l'array delle lettere usate con la nuova lettera inserita
void aggiornaLettereUsate (char lettera, char lettere_usate [], int *i) {  
    lettere_usate[*i] = lettera;
    (*i)++;
    lettere_usate[*i] = '\0';
}

// Controlla se una lettera inserita è valida e non è stata già usata
char controllaLettera (char lettera, char lettere_inserite []) {
    // se la lettera è in maiuscolo, convertila in minuscolo
    if (lettera >= 'A' && lettera <= 'Z')
        lettera += ('a' - 'A');

    // controlla se la lettera è valida
    if (lettera < 'a' || lettera > 'z') {
        printf("Errore: inserire una lettera valida!\n");
        return 0;
    }

    // controlla se la lettera è gia stata inserita
    for(int i = 0; lettere_inserite[i] != '\0'; i++) {
        if (lettera == lettere_inserite[i]) {
            printf("Errore: la lettera %c è già stata inserita!\n", lettera);
            return 0;
        }
    }

    return lettera;
}

// Stampa un messaggio di vittoria
void messaggioVittoria () {
    printf("\n");
    printf("    __  __      _          _       __        __\n"      );
    printf("   / / / /___ _(_)  _   __(_)___  / /_____  / /\n"      );
    printf("  / /_/ / __ `/ /  | | / / / __ \\/ __/ __ \\/ / \n"    );
    printf(" / __  / /_/ / /   | |/ / / / / / /_/ /_/ /_/  \n"      );
    printf("/_/ /_/\\__,_/_/    |___/_/_/ /_/\\__/\\____(_)   \n"   );
    printf("                                                \n"     ); 
}

// Stampa un messaggio di sconfitta
void messaggioSconfitta () {
    printf("\n");
    printf("    __  __      _                               __\n"   );
    printf("   / / / /___ _(_)  ____  ___  ______________  / /\n"   );
    printf("  / /_/ / __ `/ /  / __ \\/ _ \\/ ___/ ___/ __ \\/ / \n");
    printf(" / __  / /_/ / /  / /_/ /  __/ /  (__  ) /_/ /_/  \n"   );
    printf("/_/ /_/\\__,_/_/  / .___/\\___/_/  /____/\\____(_)   \n");
    printf("                /_/                               \n"   );
}

// Assegna un punteggio in base alla difficoltà e all'esito della partita
void assegnaPunteggio (int *punteggio, char difficolta, bool win) {
    if(win){
        switch(difficolta) {
            case 'E':
                *punteggio = 10;
                break;
            case 'M':
                *punteggio = 50;
                break;
            case 'H':
                *punteggio = 200;
                break;
            case 'I':
                *punteggio = 500;
        }
        printf("\nHai vinto %d punti!\n", *punteggio);
    } else {
        switch(difficolta) {
            case 'E':
                *punteggio = -20;
                break;
            case 'M':
                *punteggio = -40;
                break;
            case 'H':
                *punteggio = -100;
                break;
            case 'I':
                *punteggio = -150;
        }
        printf("\nHai perso %d punti!\n", *punteggio);
    }
}

// Registra i dettagli del turno corrente nel report
void report_turno (int turno, char *parola, char difficolta, int punteggio) {
    FILE *pF = fopen("report.txt", "a");
    fprintf(pF, "turno: %d°; parola: %s; difficolta: '%c'; punteggio: %+d\n", turno, parola, difficolta, punteggio);
    fclose(pF);
}

// Stampa le statistiche finali nel report
void report_fine (int punteggio_totale, int turni, int parole_indovinate) {
    FILE *pF = fopen("report.txt", "a");
    fprintf(pF, "\nStatistiche finali: \n");
    fprintf(pF, "punteggio finale: %d; turni totali: %d; parole indovinate: %d/%d (%.2f%%)", punteggio_totale, turni, parole_indovinate, turni, (float) parole_indovinate / turni * 100);
    fprintf(pF, "\n\n--------------------------------------------------------------------------\n\n");
    fclose(pF);
}

// Stampa un indizio basato sulla riga specificata nel file degli indizi
void stampaIndizio(int riga_indizio) {
    FILE *pF = fopen("indizi.txt", "r");

    char indizio[150];
    int riga_corrente = 0;

    while (fgets(indizio, 150, pF) != NULL) {
        riga_corrente++;
        if (riga_corrente == riga_indizio) {
            printf("%s", indizio);
            break;
        }
    }

    fclose(pF);

}