#ifndef LISTA_ATTIVITA_H
#define LISTA_ATTIVITA_H

#include "attivita_di_studio.h"
#include "list.h"

/* Tipo opaco per la collezione di attività */
typedef struct lista_attivita *lista_attivita;

/*
 * Funzione: crea_lista_attivita
 * -----------------------------
 * Allocazione e inizializzazione di una nuova lista vuota.
 *
 * Pre-condizione:
 *   Nessuna.
 * Post-condizione:
 *   Viene restituito un oggetto lista_attivita con lista interna vuota.
 * Ritorna:
 *   lista_attivita valida o NULL se malloc fallisce.
 */
lista_attivita crea_lista_attivita(void);

/*
 * Funzione: libera_lista
 * ----------------------
 * Distrugge la lista liberando tutte le attività e la struttura lista_attivita.
 *
 * Parametri:
 *   lista – lista da liberare (può essere NULL).
 * Pre-condizione:
 *   lista è risultato di crea_lista_attivita o NULL.
 * Post-condizione:
 *   Tutte le attività e la struttura lista_attivita sono liberate.
 */
void libera_lista(lista_attivita lista);

/* ==== OPERAZIONI BASE ==== */

/*
 * Funzione: aggiungi_attivita
 * ---------------------------
 * Inserisce un’attività in coda alla lista.
 *
 * Parametri:
 *   lista – lista di destinazione.
 *   att   – attività da aggiungere.
 * Pre-condizione:
 *   lista != NULL, att != NULL.
 * Post-condizione:
 *   L’attività è stata aggiunta in fondo alla lista interna.
 * Ritorna:
 *   La lista aggiornata.
 */
lista_attivita aggiungi_attivita(lista_attivita lista, AttivitaDiStudio att);

/*
 * Funzione: elimina_attivita
 * --------------------------
 * Rimuove la prima occorrenza di un’attività dalla lista.
 *
 * Parametri:
 *   lista – lista di origine.
 *   att   – attività da rimuovere.
 * Pre-condizione:
 *   lista != NULL, att != NULL.
 * Post-condizione:
 *   Se presente, l’attività è stata rimossa dalla lista interna.
 * Ritorna:
 *   La lista aggiornata.
 */
lista_attivita elimina_attivita(lista_attivita lista, AttivitaDiStudio att);

/* ==== GETTER SULLA COLLEZIONE ==== */

/*
 * Funzione: lista_attivita_size
 * -----------------------------
 * Restituisce il numero di attività nella lista.
 *
 * Parametri:
 *   lista – lista di cui contare gli elementi.
 * Pre-condizione:
 *   lista può essere NULL.
 * Post-condizione:
 *   Nessuna.
 * Ritorna:
 *   Numero di elementi, 0 se lista è NULL o vuota.
 */
int lista_attivita_size(lista_attivita lista);

/*
 * Funzione: lista_attivita_get
 * ----------------------------
 * Restituisce l’attività alla posizione idx.
 *
 * Parametri:
 *   lista – lista di origine.
 *   idx   – indice (0 … size-1).
 * Pre-condizione:
 *   lista != NULL.
 * Post-condizione:
 *   Nessuna modifica alla lista.
 * Ritorna:
 *   AttivitaDiStudio se idx valido, o NULL altrimenti.
 */
AttivitaDiStudio lista_attivita_get(lista_attivita lista, int idx);

/* ==== SETTER SUL SINGOLO ELEMENTO ==== */

/*
 * Funzione: lista_attivita_set_avanzamento
 * ----------------------------------------
 * Modifica lo stato di avanzamento dell’attività in posizione idx.
 *
 * Parametri:
 *   lista       – lista di origine.
 *   idx         – indice dell’attività.
 *   nuovo_stato – stringa non NULL con il nuovo stato.
 * Pre-condizione:
 *   lista != NULL, 0 ≤ idx < size, nuovo_stato != NULL.
 * Post-condizione:
 *   L’attività indicata ha avanzamento aggiornato.
 */
void lista_attivita_set_avanzamento(lista_attivita lista, int idx, char* nuovo_stato);

/* ==== FUNZIONI “SMART” ==== */

/*
 * Funzione: segna_ritardo_interattivo
 * -----------------------------------
 * Chiede all’utente di selezionare un indice e marca l’attività come in ritardo.
 *
 * Parametri:
 *   lista – lista di attività.
 * Pre-condizione:
 *   lista != NULL.
 * Post-condizione:
 *   Se indice valido, avanzamento impostato a "in ritardo".
 */
void segna_ritardo_interattivo(lista_attivita lista);

/*
 * Funzione: segna_completata_interattivo
 * --------------------------------------
 * Chiede all’utente di selezionare un indice e marca l’attività come completata.
 *
 * Parametri:
 *   lista – lista di attività.
 * Pre-condizione:
 *   lista != NULL.
 * Post-condizione:
 *   Se indice valido, avanzamento impostato a "completato".
 */
void segna_completata_interattivo(lista_attivita lista);

/*
 * Funzione: segna_in_corso_interattivo
 * ------------------------------------
 * Chiede all’utente di selezionare un indice e marca l’attività come in corso.
 *
 * Parametri:
 *   lista – lista di attività.
 * Pre-condizione:
 *   lista != NULL.
 * Post-condizione:
 *   Se indice valido, avanzamento impostato a "in corso".
 */
void segna_in_corso_interattivo(lista_attivita lista);

/*
 * Funzione: aggiorna_stati_ritardo
 * --------------------------------
 * Imposta automaticamente "in ritardo" per tutte le attività scadute.
 *
 * Parametri:
 *   lista – lista di attività.
 * Pre-condizione:
 *   lista != NULL.
 * Post-condizione:
 *   Ogni attività con data di scadenza passata ha avanzamento aggiornato.
 */
void aggiorna_stati_ritardo(lista_attivita lista);

/* ==== REPORT & STAMPA ==== */

/*
 * Funzione: genera_report
 * -----------------------
 * Suddivide le attività in sezioni per stato e stampa un report.
 *
 * Parametri:
 *   lista – lista di attività.
 * Pre-condizione:
 *   lista != NULL.
 * Post-condizione:
 *   Stampa sezioni completate, in corso e in ritardo.
 */
void genera_report(lista_attivita lista);

/*
 * Funzione: stampa_elenco_attivita
 * --------------------------------
 * Stampa tutte le attività con indice, in ordine.
 *
 * Parametri:
 *   lista – lista di attività.
 * Pre-condizione:
 *   lista != NULL.
 * Post-condizione:
 *   Stampa elenco dettagliato su stdout.
 */
void stampa_elenco_attivita(lista_attivita lista);

/*
 * Funzione: stampa_sezione
 * ------------------------
 * Stampa una sezione di attività con un titolo e la lista interna.
 *
 * Parametri:
 *   titolo  – intestazione della sezione.
 *   sezione – lista di attività da stampare.
 * Pre-condizione:
 *   titolo != NULL, sezione valida.
 * Post-condizione:
 *   Stampa titolo e attività o messaggio “Nessuna attivita”.
 */
void stampa_sezione(const char *titolo, List sezione);

#endif /* LISTA_ATTIVITA_H */
