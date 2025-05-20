#include <string.h>
#include <stdio.h>
#include "attivita.h"
#include "data.h"

// Crea una nuova attività
Attivita_di_studio crea_attivita_di_studio(const char* descrizione, const char* corso, Data data_scadenza, float tempo_stimato_ore, int priorita) {
    Attivita_di_studio a;
    strncpy(a.descrizione, descrizione, LEN_DESC);
    strncpy(a.corso, corso, LEN_CORSO);
    a.data_scadenza = data_scadenza;
    a.tempo_stimato_ore = tempo_stimato_ore;
    a.priorita = priorita;
    strncpy(a.avanzamento, "in corso", LEN_AVANZ);
    return a;
}

const char* descrizione(Attivita_di_studio* as) {
    return as->descrizione;
}

const char* corso(Attivita_di_studio* as) {
    return as->corso;
}

Data data_scadenza_att(Attivita_di_studio* as) {
    return as->data_scadenza;
}

float tempo_stimato_ore(Attivita_di_studio* as) {
    return as->tempo_stimato_ore;
}

int priorita_att(Attivita_di_studio* as) {
    return as->priorita;
}

const char* avanzamento(Attivita_di_studio* as) {
    return as->avanzamento;
}

int giorni_alla_scadenza(Attivita_di_studio* as, Data oggi) {
    return giorni_tra(as->data_scadenza, oggi);
}

void segna_completata(Attivita_di_studio* as) {
    strncpy(as->avanzamento, "completato", LEN_AVANZ);
}

void segna_ritardo(Attivita_di_studio* as, Data oggi) {
    if (giorni_tra(oggi, as->data_scadenza) > 0) {
        strncpy(as->avanzamento, "in ritardo", LEN_AVANZ);
    }
}

void stampa_attivita(Attivita_di_studio* as) {
    printf("Descrizione: %s\n", as->descrizione);
    printf("Corso: %s\n", as->corso);
    printf("Data di scadenza: ");
    stampa_data(as->data_scadenza);
    printf("\nTempo stimato (ore): %.2f\n", as->tempo_stimato_ore);
    printf("Priorità: ");
    switch (as->priorita) {
        case 1: printf("Alta\n"); break;
        case 2: printf("Media\n"); break;
        case 3: printf("Bassa\n"); break;
        default: printf("Sconosciuta\n");
    }
    printf("Avanzamento: %s\n", as->avanzamento);
}
