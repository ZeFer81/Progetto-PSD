#include <stdio.h>
#include <string.h>
#include "lista_attivita.h"
#include "attivita.h"
#include "data.h"

// Funzione per leggere una stringa con sicurezza
void leggi_stringa(char* buffer, int size) {
    if (fgets(buffer, size, stdin)) {
        buffer[strcspn(buffer, "\n")] = 0;  // rimuove newline
    }
}

int main() {
    Lista_attivita lista = crea_lista_attivita();
    int scelta;

    do {
        printf("\nMenu:\n");
        printf("1. Aggiungi attività\n");
        printf("2. Elimina attività (per descrizione)\n");
        printf("3. Visualizza report attività\n");
        printf("4. Esci\n");
        printf("Scegli un'opzione: ");
        if (scanf("%d", &scelta) != 1) {
            while (getchar() != '\n'); // svuota buffer
            printf("Input non valido, riprova.\n");
            continue;
        }
        while (getchar() != '\n'); // svuota newline

        if (scelta == 1) {
            char descrizione[LEN_DESC], corso[LEN_CORSO];
            int giorno, mese, anno, priorita;
            float tempo;

            printf("Inserisci descrizione attività: ");
            leggi_stringa(descrizione, LEN_DESC);
            printf("Inserisci corso: ");
            leggi_stringa(corso, LEN_CORSO);

            printf("Inserisci data scadenza (gg mm aaaa): ");
            if (scanf("%d %d %d", &giorno, &mese, &anno) != 3) {
                printf("Data non valida.\n");
                while(getchar() != '\n');
                continue;
            }
            while(getchar() != '\n');

            printf("Inserisci tempo stimato (ore): ");
            if (scanf("%f", &tempo) != 1) {
                printf("Tempo non valido.\n");
                while(getchar() != '\n');
                continue;
            }
            while(getchar() != '\n');

            printf("Inserisci priorità (1=Alta, 2=Media, 3=Bassa): ");
            if (scanf("%d", &priorita) != 1 || priorita < 1 || priorita > 3) {
                printf("Priorità non valida.\n");
                while(getchar() != '\n');
                continue;
            }
            while(getchar() != '\n');

            Data data_scad = crea_data(giorno, mese, anno);
            Attivita_di_studio a = crea_attivita_di_studio(descrizione, corso, data_scad, tempo, priorita);
            aggiungi_attivita(&lista, a);
            printf("Attività aggiunta con successo.\n");

        } else if (scelta == 2) {
            char descrizione[LEN_DESC];
            if (!lista.head) {
                printf("Lista vuota, niente da eliminare.\n");
                continue;
            }
            printf("Inserisci la descrizione dell'attività da eliminare: ");
            leggi_stringa(descrizione, LEN_DESC);
            elimina_attivita(&lista, descrizione);
            printf("Eliminazione effettuata (se attività trovata).\n");

        } else if (scelta == 3) {
            genera_report(&lista);

        } else if (scelta == 4) {
            printf("Uscita dal programma.\n");

        } else {
            printf("Scelta non valida, riprova.\n");
        }

    } while (scelta != 4);

    return 0;
}
