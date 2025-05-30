#include <stdio.h>
#include <stdlib.h>
#include "lista_attivita.h"
#include "item-attivita_di_studio.h"
#include <string.h>

/* ---------------------------------------------------------- */
/* Pulisce lo schermo su Windows / Unix */
static void clear_screen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


/* Lettura di un intero con controllo limiti e formato */
static int leggi_int(const char *prompt, int min, int max, int *out) {
    char buf[64];
    printf("%s", prompt);

    if (!fgets(buf, sizeof buf, stdin))
        return 0;                                    /* EOF / errore */

    char *endptr;
    errno = 0;
    long v = strtol(buf, &endptr, 10);
    if (errno || endptr == buf ||
        (*endptr != '\n' && *endptr != '\0') ||
        v < min || v > max)
        return 0;

    *out = (int)v;
    return 1;
}

/* ---------------------------------------------------------- */
int main(void) {

    /* 1 – Creo la lista una sola volta */
    lista_attivita lista = crea_lista_attivita();
    if (!lista) {
        fprintf(stderr, "Errore: impossibile inizializzare la lista.\n");
        return EXIT_FAILURE;
    }

    int scelta = 0;
    while (scelta != 9) {

        /* 2 – Menu */
        clear_screen();
        puts("========================================");
        puts("      Gestore Attivita di Studio        ");
        puts("========================================");
        puts("1. Aggiungi nuova attivita");
        puts("2. Segna attività come completata");

        puts("3. Mostra report attivita");

        puts("4. Aggiorna stati \"in ritardo\"");
        puts("5. Segna attivita come \"in ritardo\"");
        puts("6. Riporta attivita \"in corso\"");
        puts("7. Elimina un'attivita");
        puts("8. Esci");
        puts("----------------------------------------");

        if (!leggi_int("Seleziona un'opzione [1-8]: ", 1, 8, &scelta))
            scelta = 0;                      /* input non valido ⇒ default */

        switch (scelta) {
        /* -------------------------------------------------- */
        case 1: {   /* Aggiungi nuova attività */
            Item it = inputItem();           /* può restituire NULL */
            if (!it) {
                puts("Inserimento annullato o dati non validi.");
            } else {
                aggiungi_attivita(lista, (AttivitaDiStudio)it);
                printf("Attività aggiunta! Totale: %d\n", lista_attivita_size(lista));
            }
            break;
        }
        /* -------------------------------------------------- */
        case 2:   /* Segna completata */
            stampa_elenco_attivita(lista);
            segna_completata_interattivo(lista);
            break;

        case 3:   /* Report */
            clear_screen();
            genera_report(lista);
            break;

        case 4:   /* Aggiorna automaticamente gli stati in ritardo */
            aggiorna_stati_ritardo(lista);
            puts("Stati \"in ritardo\" aggiornati.");
            break;

        case 5:   /* Segna manualmente in ritardo */
            stampa_elenco_attivita(lista);
            segna_ritardo_interattivo(lista);
            break;

        case 6:   /* Riporta in corso */
            stampa_elenco_attivita(lista);
            segna_in_corso_interattivo(lista);
            break;

        /* ----------   ELIMINA ATTIVITÀ   ---------- */
        case 7: {
            if (lista_attivita_size(lista) == 0) {
                puts("La lista è vuota.");
                break;
            }
            stampa_elenco_attivita(lista);

            int idx;
            if (!leggi_int("Indice da eliminare: ", 0,
                           (int)lista_attivita_size(lista) - 1, &idx)) {
                puts("Indice non valido.");
                break;
            }
            AttivitaDiStudio a = lista_attivita_get(lista, idx);
            elimina_attivita(lista, a);
            puts("Attività eliminata.");
            break;
        }

        case 8:   /* Esci */
            puts("Grazie per aver utilizzato il Gestore Attività!");
            puts("Premi Invio per uscire...");
            while (getchar() != '\n' && !feof(stdin)) {}
            return EXIT_SUCCESS;

        default:
            puts("Opzione non valida.");
            break;        }

        /* 3 – Pausa tra le operazioni */
        if (scelta != 8) {
            puts("Premi Invio per continuare...");
            while (getchar() != '\n' && !feof(stdin)) {} //"pulire" il buffer di input

        }
    }

    /* 4 – Pulizia finale */
    libera_lista(lista);
    return EXIT_SUCCESS;
}
