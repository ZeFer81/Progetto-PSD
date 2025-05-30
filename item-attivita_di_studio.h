#ifndef ITEM_ATTIVITA_DI_STUDIO_H
#define ITEM_ATTIVITA_DI_STUDIO_H

#include "attivita_di_studio.h"
#include <stdio.h>
typedef void* Item;
typedef void (*SetterFn)(AttivitaDiStudio a, char *str_user);

/*
 * Funzione: inputItem
 * -------------------
 * Legge da stdin i dati per creare un’AttivitaDiStudio.
 *
 * Parametri:
 *   Nessuno.
 *
 * Pre-condizione:
 *   stdin disponibile e leggibile.
 *
 * Post-condizione:
 *   Viene creato dinamicamente un oggetto AttivitaDiStudio con i dati
 *   forniti dall’utente e inizializzato con valori validi.
 *
 * Ritorna:
 *   Un puntatore Item (alias AttivitaDiStudio) oppure NULL in caso di
 *   errore durante la creazione o lettura.
 */
Item inputItem();

/*
 * Funzione: outputItem
 * --------------------
 * Visualizza su stdout le informazioni di un’attività.
 *
 * Parametri:
 *   item – puntatore a un oggetto Item creato da inputItem o recuperato
 *          da una lista.
 *
 * Pre-condizione:
 *   item ≠ NULL e deve riferirsi a un oggetto AttivitaDiStudio valido.
 *
 * Post-condizione:
 *   I dettagli dell’attività vengono stampati su stdout in formato
 *   leggibile.
 *
 * Ritorna:
 *   Nessun valore (void).
 */
void outputItem(Item item);

/*
 * Funzione: cmpItem
 * -----------------
 * Confronta due attività in base alla loro data di scadenza.
 *
 * Parametri:
 *   item1 – primo Item da confrontare.
 *   item2 – secondo Item da confrontare.
 *
 * Pre-condizione:
 *   Entrambi i parametri ≠ NULL e devono essere riferimenti validi a
 *   oggetti AttivitaDiStudio.
 *
 * Post-condizione:
 *   Nessuna modifica sugli oggetti passati.
 *
 * Ritorna:
 *   Un intero:
 *     <0 se item1 ha data antecedente a item2.
 *      0 se hanno la stessa data.
 *     >0 se item1 ha data successiva a item2.
 */
int cmpItem(Item item1, Item item2);

/*
 * Funzione: valida_stringa
 * ------------------------
 * Verifica se una stringa soddisfa le condizioni di validità.
 *
 * Parametri:
 *   str – puntatore alla stringa da validare.
 *   max_len – lunghezza massima accettata.
 *   consenti_str_vuota – true se è permesso che la stringa sia vuota.
 *
 * Pre-condizione:
 *   str può essere NULL.
 *
 * Post-condizione:
 *   Nessuna modifica a str.
 *
 * Ritorna:
 *   true se la stringa è valida, false altrimenti.
 */
bool valida_stringa(char *str, int max_len, bool consenti_str_vuota);

/*
 * Funzione: input_stringa
 * -----------------------
 * Legge e valida una stringa da stdin.
 *
 * Parametri:
 *   stringa – buffer di destinazione.
 *   max_lun_stringa – lunghezza massima ammessa.
 *
 * Pre-condizione:
 *   Il buffer stringa deve essere allocato con spazio sufficiente.
 *
 * Post-condizione:
 *   La stringa letta viene salvata nel buffer se valida.
 *
 * Ritorna:
 *   Puntatore alla stringa se lettura e validazione avvenute con
 *   successo, NULL altrimenti.
 */
char *input_stringa(char* stringa, int max_lun_stringa);

/*
 * Funzione: stdin_pulizia
 * -----------------------
 * Pulisce stdin eliminando eventuali caratteri residui dopo una lettura.
 *
 * Parametri:
 *   stringa – buffer di destinazione.
 *   max_len – lunghezza massima ammessa.
 *   stream – stream di input (es. stdin).
 *
 * Pre-condizione:
 *   Il buffer deve essere allocato.
 *
 * Post-condizione:
 *   I caratteri residui nella riga vengono eliminati, buffer aggiornato.
 *
 * Ritorna:
 *   Puntatore alla stringa se lettura valida, NULL se errore.
 */
char *stdin_pulizia(char* stringa, int max_len, FILE * stream);

/*
 * Funzione: svuotamento_buffer
 * ----------------------------
 * Svuota completamente il buffer di input fino a newline o EOF.
 *
 * Parametri:
 *   Nessuno.
 *
 * Pre-condizione:
 *   Nessuna.
 *
 * Post-condizione:
 *   Tutti i caratteri pendenti in stdin fino a newline vengono eliminati.
 *
 * Ritorna:
 *   Nessun valore (void).
 */
void svuotamento_buffer();

#endif // ITEM_ATTIVITA_DI_STUDIO_H
