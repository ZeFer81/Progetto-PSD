#ifndef ATTIVITA_DI_STUDIO_H
#define ATTIVITA_DI_STUDIO_H

#include "data.h"
#include <stdbool.h>
typedef struct attivita_di_studio *AttivitaDiStudio;

/*
 * Funzione: crea_attivita_di_studio
 * ---------------------------------
 * Crea una nuova attività di studio allocando e inizializzando
 * tutti i campi.
 *
 * Parametri:
 *   descrizione       - testo descrittivo
 *   corso             - nome del corso
 *   data_di_scadenza  - data di scadenza
 *   tempo_stimato_ore - ore stimate (>=0)
 *   priorita          - livello di priorità (1, 2, 3)
 *   avanzamento       - stato iniziale ("in corso", ecc.)
 *
 * Pre-condizione:
 *   Tutti i puntatori validi; valori nei range corretti.
 *
 * Post-condizione:
 *   Struttura creata e inizializzata.
 *
 * Ritorna:
 *   Puntatore AttivitaDiStudio o NULL se errore.
 */
AttivitaDiStudio crea_attivita_di_studio(
    char* descrizione,
    char* corso,
    Data data_di_scadenza,
    Data data_di_creazione,
    float tempo_stimato_ore,
    int priorita,
    const char* avanzamento);

/*
 * Funzione: distruggi_attivita
 * ----------------------------
 * Libera memoria associata a un’attività.
 *
 * Parametri:
 *   a - attività da distruggere (può essere NULL)
 *
 * Pre-condizione:
 *   Nessuna.
 *
 * Post-condizione:
 *   Memoria rilasciata.
 *
 * Ritorna:
 *   Nessuno (void).
 */
void distruggi_attivita(AttivitaDiStudio a);

/*
 * Funzione: attivita_get_descrizione
 * ----------------------------------
 * Restituisce la descrizione.
 *
 * Parametri:
 *   a - attività valida
 *
 * Pre-condizione:
 *   a ≠ NULL.
 *
 * Post-condizione:
 *   Nessuna.
 *
 * Ritorna:
 *   Puntatore alla descrizione.
 */
char* attivita_get_descrizione(AttivitaDiStudio a);

/*
 * Funzione: attivita_get_corso
 * ----------------------------
 * Restituisce il nome del corso.
 *
 * Parametri:
 *   a - attività valida
 *
 * Pre-condizione:
 *   a ≠ NULL.
 *
 * Post-condizione:
 *   Nessuna.
 *
 * Ritorna:
 *   Puntatore al nome del corso.
 */
char* attivita_get_corso(AttivitaDiStudio a);

/*
 * Funzione: attivita_get_data_scadenza
 * ------------------------------------
 * Restituisce la data di scadenza.
 *
 * Parametri:
 *   a - attività valida
 *
 * Pre-condizione:
 *   a ≠ NULL.
 *
 * Post-condizione:
 *   Nessuna.
 *
 * Ritorna:
 *   Oggetto Data.
 */
Data attivita_get_data_scadenza(AttivitaDiStudio a);
Data attivita_get_data_di_creazione(AttivitaDiStudio a);

/*
 * Funzione: attivita_get_tempo_stimato
 * ------------------------------------
 * Restituisce il tempo stimato in ore.
 *
 * Parametri:
 *   a - attività valida
 *
 * Pre-condizione:
 *   a ≠ NULL.
 *
 * Post-condizione:
 *   Nessuna.
 *
 * Ritorna:
 *   Valore float (ore).
 */
float attivita_get_tempo_stimato(AttivitaDiStudio a);

/*
 * Funzione: attivita_get_priorita
 * -------------------------------
 * Restituisce la priorità.
 *
 * Parametri:
 *   a - attività valida
 *
 * Pre-condizione:
 *   a ≠ NULL.
 *
 * Post-condizione:
 *   Nessuna.
 *
 * Ritorna:
 *   Intero (1, 2, 3).
 */
int attivita_get_priorita(AttivitaDiStudio a);

/*
 * Funzione: attivita_get_avanzamento
 * ----------------------------------
 * Restituisce lo stato di avanzamento.
 *
 * Parametri:
 *   a - attività valida
 *
 * Pre-condizione:
 *   a ≠ NULL.
 *
 * Post-condizione:
 *   Nessuna.
 *
 * Ritorna:
 *   Puntatore a stringa avanzamento.
 */
char* attivita_get_avanzamento(AttivitaDiStudio a);

/*
 * Funzione: giorni_alla_scadenza_attivita
 * ---------------------------------------
 * Calcola i giorni mancanti alla scadenza.
 *
 * Parametri:
 *   a            - attività valida
 *   data_odierna - data di riferimento
 *
 * Pre-condizione:
 *   a ≠ NULL, data_odierna valida.
 *
 * Post-condizione:
 *   Nessuna.
 *
 * Ritorna:
 *   Differenza in giorni (int).
 */
int giorni_alla_scadenza_attivita(AttivitaDiStudio a, Data data_odierna);

/*
 * Funzione: attivita_set_descrizione
 * ----------------------------------
 * Imposta una nuova descrizione.
 *
 * Parametri:
 *   a     - attività valida
 *   descr - nuova descrizione
 *
 * Pre-condizione:
 *   a ≠ NULL, descr ≠ NULL.
 *
 * Post-condizione:
 *   Descrizione aggiornata.
 *
 * Ritorna:
 *   true se riuscito, false altrimenti.
 */
bool attivita_set_descrizione(AttivitaDiStudio a, char *descr);

/*
 * Funzione: attivita_set_corso
 * ----------------------------
 * Imposta un nuovo corso.
 *
 * Parametri:
 *   a     - attività valida
 *   corso - nuovo corso
 *
 * Pre-condizione:
 *   a ≠ NULL, corso ≠ NULL.
 *
 * Post-condizione:
 *   Corso aggiornato.
 *
 * Ritorna:
 *   true se riuscito, false altrimenti.
 */
bool attivita_set_corso(AttivitaDiStudio a, char *corso);

/*
 * Funzione: attivita_set_data_scadenza
 * ------------------------------------
 * Imposta una nuova data di scadenza.
 *
 * Parametri:
 *   a    - attività valida
 *   data - nuova data
 *
 * Pre-condizione:
 *   a ≠ NULL, data valida.
 *
 * Post-condizione:
 *   Data aggiornata.
 *
 * Ritorna:
 *   true se riuscito, false altrimenti.
 */
bool attivita_set_data_scadenza(AttivitaDiStudio a, Data data);

/*
 * Funzione: attivita_set_tempo_stimato
 * ------------------------------------
 * Imposta un nuovo tempo stimato.
 *
 * Parametri:
 *   a     - attività valida
 *   tempo - nuovo tempo
 *
 * Pre-condizione:
 *   a ≠ NULL, tempo > 0.
 *
 * Post-condizione:
 *   Tempo aggiornato.
 *
 * Ritorna:
 *   true se riuscito, false altrimenti.
 */
bool attivita_set_tempo_stimato(AttivitaDiStudio a, float tempo);

/*
 * Funzione: attivita_set_priorita
 * -------------------------------
 * Imposta una nuova priorità.
 *
 * Parametri:
 *   a        - attività valida
 *   priorita - nuovo valore (1, 2, 3)
 *
 * Pre-condizione:
 *   a ≠ NULL, priorita valida.
 *
 * Post-condizione:
 *   Priorità aggiornata.
 *
 * Ritorna:
 *   true se riuscito, false altrimenti.
 */
bool attivita_set_priorita(AttivitaDiStudio a, int priorita);

/*
 * Funzione: attivita_set_avanzamento
 * ----------------------------------
 * Imposta un nuovo stato avanzamento.
 *
 * Parametri:
 *   a     - attività valida
 *   avanz - nuovo stato
 *
 * Pre-condizione:
 *   a ≠ NULL, avanz valido.
 *
 * Post-condizione:
 *   Avanzamento aggiornato.
 *
 * Ritorna:
 *   true se riuscito, false altrimenti.
 */
bool attivita_set_avanzamento(AttivitaDiStudio a, char *avanz);

/*
 * Funzione: segna_completata
 * --------------------------
 * Segna l’attività come completata.
 *
 * Parametri:
 *   a - attività valida
 *
 * Pre-condizione:
 *   a ≠ NULL.
 *
 * Post-condizione:
 *   Stato aggiornato a "completata".
 *
 * Ritorna:
 *   Nessuno (void).
 */
void segna_completata(AttivitaDiStudio a);

/*
 * Funzione: segna_ritardo
 * -----------------------
 * Segna l’attività come in ritardo.
 *
 * Parametri:
 *   a - attività valida
 *
 * Pre-condizione:
 *   a ≠ NULL.
 *
 * Post-condizione:
 *   Stato aggiornato a "in ritardo".
 *
 * Ritorna:
 *   Nessuno (void).
 */
void segna_ritardo(AttivitaDiStudio a);

/*
 * Funzione: stampa_attivita
 * -------------------------
 * Stampa tutti i dettagli dell’attività su stdout.
 *
 * Parametri:
 *   a - attività valida
 *
 * Pre-condizione:
 *   a ≠ NULL.
 *
 * Post-condizione:
 *   Dati stampati a video.
 *
 * Ritorna:
 *   Nessuno (void).
 */
void stampa_attivita(AttivitaDiStudio a);

#endif /* ATTIVITA_DI_STUDIO_H */
