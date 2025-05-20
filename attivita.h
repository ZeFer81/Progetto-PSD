#ifndef ATTIVITA_H
#define ATTIVITA_H

#include "data.h"

#define LEN_DESC 100
#define LEN_CORSO 50
#define LEN_AVANZ 15

typedef struct {
    char descrizione[LEN_DESC];
    char corso[LEN_CORSO];
    Data data_scadenza;
    float tempo_stimato_ore;
    int priorita;         // 1=alta 2=media 3=bassa
    char avanzamento[LEN_AVANZ]; // "completato", "in corso", "in ritardo"
} Attivita_di_studio;

// Operator: crea_attivita_di_studio
Attivita_di_studio crea_attivita_di_studio(const char* descrizione, const char* corso, Data data_scadenza, float tempo_stimato_ore, int priorita);

// Operator: descrizione, corso, data, tempo_stimato_ore, priorita, avanzamento
const char* descrizione(Attivita_di_studio* as);
const char* corso(Attivita_di_studio* as);
Data data_scadenza_att(Attivita_di_studio* as);
float tempo_stimato_ore(Attivita_di_studio* as);
int priorita_att(Attivita_di_studio* as);
const char* avanzamento(Attivita_di_studio* as);

// Operator: giorni_alla_scadenza (richiede "oggi" come Data)
int giorni_alla_scadenza(Attivita_di_studio* as, Data oggi);

// Operator: segna_completata, segna_ritardo
void segna_completata(Attivita_di_studio* as);
void segna_ritardo(Attivita_di_studio* as, Data oggi);

// Operator: stampa_attivita
void stampa_attivita(Attivita_di_studio* as);

#endif