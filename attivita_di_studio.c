/*
 * File: attivita_di_studio.c
 * --------------------------
 * Questo file implementa la gestione di oggetti AttivitaDiStudio.
 * Fornisce funzioni per creare, distruggere, leggere, modificare
 * e stampare attività, assicurando validazione sui dati e controllo
 * memoria. Include anche il calcolo dei giorni rimanenti alla scadenza.
 */

#include "attivita_di_studio.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.h"
#include <stdbool.h>
#include "item-attivita_di_studio.h"

#define MAX_DESCRIZIONE       128
#define MAX_CORSO             128
#define MAX_AVANZAMENTO       64
#define MIN_TEMPO_ORE         0.1f
#define MAX_TEMPO_ORE         1000.0f

/*
 * Struttura: attivita_di_studio
 * -----------------------------
 * Struttura interna che rappresenta un’attività di studio,
 * con campi per descrizione, corso, data, ore, priorità e avanzamento.
 * Non esportata direttamente all’esterno (gestita via puntatore).
 */
struct attivita_di_studio {
    char * descrizione;
    char * corso;
    Data  data_di_scadenza;
    float tempo_stimato_ore;
    int   priorita;
    char * avanzamento;
};

/*
 * Funzione: crea_attivita_di_studio
 * ---------------------------------
 * Alloca e inizializza una nuova attività di studio.
 * Effettua controlli su validità dei parametri prima di allocare
 * memoria e duplicare le stringhe.
 *
 * Parametri:
 *   descrizione, corso, data_di_scadenza, tempo_stimato_ore,
 *   priorita, avanzamento.
 *
 * Ritorna:
 *   Puntatore all’attività creata o NULL se errore.
 */
AttivitaDiStudio crea_attivita_di_studio(
    char* descrizione,
    char* corso,
    Data data_di_scadenza,
    float tempo_stimato_ore,
    int priorita,
    const char* avanzamento) {

    char buf[MAX_CORSO];
    if(!valida_stringa(descrizione, MAX_DESCRIZIONE, true)) {
        fprintf(stderr, "Errore: descrizione non valida [%s]\n", descrizione);
        return NULL;
    }
    if(!valida_stringa(corso, MAX_CORSO, true)) {
        fprintf(stderr, "Errore: corso non valido [%s]\n", corso);
        return NULL;
    }
    if (!data_valida(data_di_scadenza)) {
        fprintf(stderr, "Errore: data di scadenza non valida\n");
        return NULL;
    }
    if (tempo_stimato_ore < MIN_TEMPO_ORE || tempo_stimato_ore > MAX_TEMPO_ORE) {
        fprintf(stderr, "Errore: tempo stimato (%.2f) fuori range\n",
                tempo_stimato_ore);
        return NULL;
    }
    if (priorita < 0 || priorita > 3) {
        fprintf(stderr,"Errore: priorità (%d) fuori range\n", priorita);
        return NULL;
    }
    if (strcmp(avanzamento, "in corso") &&
        strcmp(avanzamento, "in ritardo") &&
        strcmp(avanzamento, "completata")) {
        fprintf(stderr,"Errore: stato %s non accettato\n", avanzamento);
        return NULL;
    }

    AttivitaDiStudio a = malloc(sizeof *a);
    if (!a) return NULL;

    a->descrizione       = strdup(descrizione);
    a->corso             = strdup(corso);
    a->data_di_scadenza  = data_di_scadenza;
    a->tempo_stimato_ore = tempo_stimato_ore;
    a->priorita          = priorita;
    a->avanzamento       = strdup(avanzamento);
    return a;
}

/*
 * Funzione: distruggi_attivita
 * ----------------------------
 * Libera la memoria allocata per l’attività.
 * Importante per evitare memory leak.
 *
 * Parametri:
 *   a - puntatore attività da distruggere.
 *
 * Ritorna:
 *   Nessuno (void).
 */
void distruggi_attivita(AttivitaDiStudio a) {
    free(a);
}

/*
 * Funzioni: Getter
 * ----------------
 * Restituiscono i singoli campi di un’attività.
 * Sono progettati per evitare accesso diretto ai campi interni.
 *
 * Parametri:
 *   a - attività valida.
 *
 * Ritorna:
 *   Valore del campo richiesto.
 */
char* attivita_get_descrizione(AttivitaDiStudio a) {
    return a ? a->descrizione : NULL;
}
char* attivita_get_corso(AttivitaDiStudio a) {
    return a ? a->corso : NULL;
}
Data attivita_get_data_scadenza(AttivitaDiStudio a) {
    return a ? a->data_di_scadenza : NULL;
}
float attivita_get_tempo_stimato(AttivitaDiStudio a) {
    return a ? a->tempo_stimato_ore : 0.10f;
}
int attivita_get_priorita(AttivitaDiStudio a) {
    return a ? a->priorita : 0;
}
char* attivita_get_avanzamento(AttivitaDiStudio a) {
    return a ? a->avanzamento : NULL;
}

/*
 * Funzione: giorni_alla_scadenza_attivita
 * ---------------------------------------
 * Calcola il numero di giorni rimanenti tra la data di scadenza
 * dell’attività e una data di riferimento (oggi).
 *
 * Parametri:
 *   a            - attività valida.
 *   data_odierna - data corrente di confronto.
 *
 * Ritorna:
 *   Differenza in giorni.
 */
int giorni_alla_scadenza_attivita(AttivitaDiStudio a, Data data_odierna) {
    if (!a) return 0;
    Data scad = attivita_get_data_scadenza(a);
    return differenza_giorni(scad, data_odierna);
}

/*
 * Funzioni: Setter
 * ----------------
 * Aggiornano i singoli campi dell’attività.
 * Gestiscono la memoria liberando i dati precedenti dove necessario.
 *
 * Parametri:
 *   a        - attività valida.
 *   nuovo_*  - nuovo valore da impostare.
 *
 * Ritorna:
 *   true se l’operazione ha avuto successo, false altrimenti.
 */
bool attivita_set_descrizione(AttivitaDiStudio a, char *descr) {
    if (!a || !descr) return false;
    free(a->descrizione);
    a->descrizione = strdup(descr);
    return a->descrizione != NULL;
}

bool attivita_set_corso(AttivitaDiStudio a, char *corso) {
    if (!a || !corso) return false;
    free(a->corso);
    a->corso = strdup(corso);
    return a->corso != NULL;
}

bool attivita_set_data_scadenza(AttivitaDiStudio a, Data data) {
    if (!a || !data) return false;
    distruggi_data(a->data_di_scadenza);
    a->data_di_scadenza = data;
    return true;
}

bool attivita_set_tempo_stimato(AttivitaDiStudio a, float tempo) {
    if (!a || tempo <= 0.0f) return false;
    a->tempo_stimato_ore = tempo;
    return true;
}

bool attivita_set_priorita(AttivitaDiStudio a, int priorita) {
    if (!a || priorita < 1 || priorita > 3) return false;
    a->priorita = priorita;
    return true;
}

/*
 * Funzione: attivita_set_avanzamento
 * ----------------------------------
 * Aggiorna lo stato avanzamento solo se il nuovo valore è tra quelli
 * accettati.
 *
 * Parametri:
 *   a     - attività valida.
 *   avanz - nuovo stato.
 *
 * Ritorna:
 *   true se aggiornamento riuscito, false altrimenti.
 */
bool attivita_set_avanzamento(AttivitaDiStudio a, char *avanz) {
    if (!a || !avanz) return false;
    if (strcmp(avanz, "in corso") &&
        strcmp(avanz, "in ritardo") &&
        strcmp(avanz, "completata")) {
        return false;
    }
    free(a->avanzamento);
    a->avanzamento = strdup(avanz);
    return a->avanzamento != NULL;
}

/*
 * Funzione: segna_completata
 * --------------------------
 * Imposta lo stato avanzamento a "completata".
 *
 * Parametri:
 *   a - attività valida.
 *
 * Ritorna:
 *   Nessuno (void).
 */
void segna_completata(AttivitaDiStudio a) {
    attivita_set_avanzamento(a, "completata");
}

/*
 * Funzione: segna_ritardo
 * -----------------------
 * Imposta lo stato avanzamento a "in ritardo".
 *
 * Parametri:
 *   a - attività valida.
 *
 * Ritorna:
 *   Nessuno (void).
 */
void segna_ritardo(AttivitaDiStudio a) {
    attivita_set_avanzamento(a, "in ritardo");
}

/*
 * Funzione: stampa_attivita
 * -------------------------
 * Stampa su stdout tutti i dettagli dell’attività in formato leggibile.
 * Utile per debug o visualizzazione a schermo.
 *
 * Parametri:
 *   a - attività valida.
 *
 * Ritorna:
 *   Nessuno (void).
 */
void stampa_attivita(AttivitaDiStudio a) {
    if (!a) return;
    printf("Descrizione : %s\n", a->descrizione);
    printf("Corso       : %s\n", a->corso);
    printf("Scadenza    : ");
    stampa_data(attivita_get_data_scadenza(a));
    printf("\nOre stimate : %.2f\n", a->tempo_stimato_ore);
    printf("Priorità    : %d\n", a->priorita);
    printf("Avanzamento : %s\n", a->avanzamento);
}
