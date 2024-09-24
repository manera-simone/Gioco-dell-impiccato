# I made a hangman game using C.
---
## Panoramica:
    Ho scritto un programma in linguaggio C che ricrea il classico gioco dell'impiccato. 
    Il gioco prevede di indovinare una parola nascosta selezionata casualmente da un dizionario. 

    Sono presenti 4 livelli di difficoltà, ovvero:
        - **Easy**: parole semplici e più corte; la prima e l'ultima lettera sono fornite
        - **Medium**: parole comuni e di lunghezza media; la prima e l'ultima lettera sono fornite
        - **Hard**: parole difficili di lunghezza variabile; la prima e l'ultima lettera sono fornite
        - **Impossible**: parole molto difficili e rare; la prima e l'ultima lettera NON sono fornite
    Infine, è presente un livello di difficoltà aggiuntivo chiamato "Random": quando l'utente seleziona questo livello, 
    una delle quattro difficoltà principali viene scelta casualmente con le seguenti probabilità: 
        Easy con il 40% di probabilità, Medium con il 30%, Hard con il 20% e Impossible con il 10%. 
    Credo che ciò aggiunga un elemento di imprevedibilità al gioco, permettendo agli utenti di sperimentare una varietà di sfide.

    Durante il gioco, il giocatore ha la possibilità di chiedere un indizio nel caso in cui si trovi bloccato nel tentativo 
    di indovinare la parola segreta. All'inizio di ogni partita, il giocatore dispone di 3 indizi che può utilizzare. 
    Tuttavia, se tutti gli indizi vengono esauriti e il giocatore si trova ancora in difficoltà, ha la possibilità di acquistare 
    un ulteriore indizio utilizzando i punti accumulati durante il corso del gioco.
    Credo che questa meccanica aggiuntiva offra al giocatore un'opportunità per superare gli ostacoli nel gioco, mantenendo comunque 
    un certo grado di sfida e decisione strategica nel gestire i propri punti per ottenere vantaggi durante la partita.

    Il programma tiene traccia del punteggio totale, delle vite rimanenti e fornisce un report dettagliato alla fine di ogni partita.
---
## Struttura:
    - main.c: *contiene la funzione main e gestisce il flusso del gioco.*
    - funzioni.c: *contiene le funzioni utilizzate nel gioco.*
        - menu_difficolta        --> *Gestisce la selezione della difficoltà del gioco.*
        - controllaSeGiusta      --> *Controlla se una lettera inserita è corretta rispetto alla parola nascosta.*
        - stampaParola           --> *Stampa la parola nascosta, mostrando solo le lettere corrette e nascondendo le altre.*
        - trovaParola            --> *Trova una parola casuale nel dizionario, basata sulla difficoltà specificata.*
        - controllaVittoria      --> *Controlla se tutte le lettere della parola sono state indovinate.*
        - chiediConferma         --> *Richiede conferma all'utente, assicurandosi che la risposta sia valida.*
        - disegnaImpiccato       --> *Disegna la rappresentazione grafica dell'impiccato in base alle vite rimanenti.*
        - controllaLettera       --> *Controlla se una lettera inserita è valida e non è stata già usata.*
        - aggiornaLettereUsate   --> *Aggiorna l'array delle lettere usate con la nuova lettera inserita.*
        - assegnaPunteggio       --> *Assegna un punteggio in base alla difficoltà e all'esito della partita.*
        - stampaIndizio          --> *Stampa un indizio basato sulla riga specificata nel file degli indizi.*
        - report_turno           --> *Registra i dettagli del turno corrente nel report.*
        - report_fine            --> *Stampa le statistiche finali nel report.*
        - messaggioVittoria      --> *Stampa un messaggio di vittoria.*
        - messaggioSconfitta     --> *Stampa un messaggio di sconfitta.*
    - funzioni.h: *contiene i prototipi delle funzioni utilizzate.*
    - dizionario.txt: *contiene l'elenco di parole utilizzate nel gioco.*
    - indizi.txt: *contiene i suggerimenti che possono essere visualizzati durante il gioco.*
    - report.txt: *registra i dettagli e le statistiche delle partite giocate.*
---
## Crediti:
   - Manera Simone