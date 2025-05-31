#ifndef DATA_H
#define DATA_H

typedef struct data * Data;

// Confronta due date: <0 se d1<d2, 0 se uguali, >0 se d1>d2
typedef enum
{
    DATE_ERROR = -2,
    DATE_LESS = -1,
    DATE_EQUAL = 0,
    DATE_GREATER = 1
} DateCompare;

/*
 * Funzione: crea_data
 * -------------------
 * Alloca e inizializza una struttura Data con giorno, mese e anno specificati.
 *
 * Parametri:
 *   giorno – valore intero del giorno (1–31)
 *   mese   – valore intero del mese (1–12)
 *   anno   – valore intero dell’anno
 *
 * Pre-condizione:
 *   Nessuna (ma se la data non è valida, viene emesso un messaggio di errore).
 *
 * Post-condizione:
 *   Restituisce un puntatore Data con campi inizializzati, o NULL se malloc fallisce.
 *
 * Ritorna:
 *   Un oggetto Data* con i campi impostati, oppure NULL.
 */
Data crea_data(int giorno, int mese, int anno);

/*
 * Funzione: distruggi_data
 * ------------------------
 * Libera la memoria allocata per un oggetto Data.
 *
 * Parametri:
 *   d – puntatore Data restituito da crea_data (o NULL)
 *
 * Pre-condizione:
 *   d è stato ottenuto da crea_data o è NULL.
 *
 * Post-condizione:
 *   La memoria di d è liberata se d non era NULL.
 *
 * Ritorna:
 *   Nulla.
 */
void distruggi_data(Data d);

/*
 * Funzione: confronta_date
 * ------------------------
 * Confronta lessicograficamente due date (anno → mese → giorno).
 *
 * Parametri:
 *   d1 – prima data
 *   d2 – seconda data
 *
 * Pre-condizione:
 *   d1 e d2 sono puntatori validi a Data.
 *
 * Post-condizione:
 *   Nessuna modifica a d1 o d2.
 *
 * Ritorna:
 *   DATE_LESS (-1) se d1 < d2,
 *   DATE_EQUAL (0) se d1 == d2,
 *   DATE_GREATER (+1) se d1 > d2.
 */
int confronta_date(Data d1, Data d2);

/*
 * Funzione: data_odierna
 * ----------------------
 * Crea un oggetto Data rappresentante la data corrente di sistema.
 *
 * Parametri:
 *   (nessuno)
 *
 * Pre-condizione:
 *   L’orologio di sistema è corretto.
 *
 * Post-condizione:
 *   Restituisce una nuova Data con la data odierna, o NULL se malloc fallisce.
 *
 * Ritorna:
 *   Un oggetto Data* con la data di oggi, oppure NULL.
 */
Data data_odierna(void);

/*
 * Funzione: data_valida
 * ---------------------
 * Verifica che una Data rappresenti una data calendaristicamente corretta.
 *
 * Parametri:
 *   d – puntatore a Data da validare
 *
 * Pre-condizione:
 *   d != NULL e d->giorno, d->mese, d->anno sono inizializzati.
 *
 * Post-condizione:
 *   Nessuna modifica a d.
 *
 * Ritorna:
 *   1 se la data è valida, 0 altrimenti.
 */
int data_valida(Data d);

/*
 * Funzione: stampa_data
 * ---------------------
 * Stampa su stdout una Data nel formato gg/mm/aaaa (senza newline).
 *
 * Parametri:
 *   d – puntatore a Data (validata o meno)
 *
 * Pre-condizione:
 *   d != NULL.
 *
 * Post-condizione:
 *   Nessuna modifica a d; output su stdout.
 *
 * Ritorna:
 *   Nulla.
 */
void stampa_data(Data d);

/*
 * Funzione: differenza_giorni
 * ---------------------------
 * Calcola il numero di giorni tra due date.
 *
 * Parametri:
 *   d1 – data di partenza
 *   d2 – data di arrivo
 *
 * Pre-condizione:
 *   d1, d2 != NULL e rappresentano date valide.
 *
 * Post-condizione:
 *   Nessuna modifica a d1 o d2.
 *
 * Ritorna:
 *   Numero di giorni (positivo, negativo o zero).
 */
int differenza_giorni(Data d1, Data d2);

/*
 * Funzione: data_get_giorno
 * -------------------------
 * Restituisce il campo giorno di una Data.
 *
 * Parametri:
 *   d – puntatore a Data non NULL
 *
 * Pre-condizione:
 *   d != NULL.
 *
 * Post-condizione:
 *   Nessuna modifica a d.
 *
 * Ritorna:
 *   Valore intero del giorno.
 */
int data_get_giorno(Data d);

/*
 * Funzione: data_get_mese
 * -----------------------
 * Restituisce il campo mese di una Data.
 *
 * Parametri:
 *   d – puntatore a Data non NULL
 *
 * Pre-condizione:
 *   d != NULL.
 *
 * Post-condizione:
 *   Nessuna modifica a d.
 *
 * Ritorna:
 *   Valore intero del mese.
 */
int data_get_mese(Data d);

/*
 * Funzione: data_get_anno
 * -----------------------
 * Restituisce il campo anno di una Data.
 *
 * Parametri:
 *   d – puntatore a Data non NULL
 *
 * Pre-condizione:
 *   d != NULL.
 *
 * Post-condizione:
 *   Nessuna modifica a d.
 *
 * Ritorna:
 *   Valore intero dell’anno.
 */
int data_get_anno(Data d);

int data_get_secondi(Data d);

int data_get_minuti(Data d);

int data_get_ore(Data d);

Data data_creazione(int giorno, int mese, int anno, int secondi, int minuti, int ore);
Data data_odierna_creazione(void);


#endif // DATA_H