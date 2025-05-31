#include "data.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
struct data{ //struc data per la crezione di data_di_scadenza per i file attivita_di_studio
    int giorno;
    int mese;
    int anno;
    int secondi;
    int minuti;
    int ore;
};

static long data_to_jdn(const struct data *d) {
    int y = d->anno, m = d->mese, day = d->giorno;
    if (m <= 2) {                   // sposta gen/feb ai mesi 13/14 dell’anno precedente
        y--;
        m += 12;
    }
    long A = y / 100;               // secolo
    long B = 2 - A + A / 4;         // correzione calendario gregoriano
    // formula JDN
    return (long)(365.25 * (y + 4716))
         + (long)(30.6001 * (m + 1))
         + day + B - 1524;
}


Data crea_data(int giorno, int mese, int anno) {
    // Alloca memoria per una nuova struct data
    Data d = malloc(sizeof *d);
    if (!d) {
        printf("Errore malloc\n");
        return NULL;
    }

    // Inizializza i campi giorno, mese e anno
    d->giorno = giorno;
    d->mese   = mese;
    d->anno   = anno;

    // Verifica che la data sia valida
    if (!data_valida(d)) {
        printf("Errore data non valida\n");
        free(d);
    }

    return d;
}
Data data_creazione(int giorno, int mese, int anno, int secondi, int minuti, int ore) {
    // Alloca memoria per una nuova struct data
    Data d = malloc(sizeof *d);
    if (!d) {
        printf("Errore malloc\n");
        return NULL;
    }

    // Inizializza i campi giorno, mese e anno
    d->giorno = giorno;
    d->mese   = mese;
    d->anno   = anno;
    d->secondi = secondi;
    d->minuti = minuti;
    d->ore   = ore;

    // Verifica che la data sia valida
    if (!data_valida(d)) {
        printf("Errore data non valida\n");
        free(d);
    }

    return d;
}

void distruggi_data(Data d) {
    if (!d) return; //controlla se il puntatore è diverso da NULL libera la memoria per struct Data
    free(d);
}


int confronta_date(Data d1, Data d2) {
    // Se uno dei puntatori non è valido, segnala errore
    if (!d1 || !d2)
        return DATE_ERROR;

    // Confronta prima l’anno
    if (d1->anno != d2->anno)
        return (d1->anno < d2->anno) ? DATE_LESS : DATE_GREATER;

    // Anni uguali: confronta il mese
    if (d1->mese != d2->mese)
        return (d1->mese < d2->mese) ? DATE_LESS : DATE_GREATER;

    // Anni e mesi uguali: confronta il giorno
    if (d1->giorno != d2->giorno)
        return (d1->giorno < d2->giorno) ? DATE_LESS : DATE_GREATER;

    // Se tutte le componenti coincidono, le date sono uguali
    return DATE_EQUAL;
}


Data data_odierna(void) {
    // Ottiene il timestamp attuale
    time_t now = time(NULL);
    /* Converte il timestamp nel fuso locale (giorno, mese, anno)
       timestamp: secondi trascorsi dall’epoch Unix (1 gen 1970 00:00:00 UTC)*/
    struct tm *tm_oggi = localtime(&now);
    // Crea una Data con giorno, mese (0–11 → 1–12) e anno (da 1900)
    return crea_data(
        tm_oggi->tm_mday,
        tm_oggi->tm_mon + 1,
        tm_oggi->tm_year + 1900);
}
Data data_odierna_creazione(void) {
    // Ottiene il timestamp attuale
    time_t now = time(NULL);
    /* Converte il timestamp nel fuso locale (giorno, mese, anno)
       timestamp: secondi trascorsi dall’epoch Unix (1 gen 1970 00:00:00 UTC)*/
    struct tm *tm_oggi = localtime(&now);
    // Crea una Data con giorno, mese (0–11 → 1–12) e anno (da 1900)
    return data_creazione(
        tm_oggi->tm_mday,
        tm_oggi->tm_mon + 1,
        tm_oggi->tm_year + 1900,
        tm_oggi->tm_sec,
        tm_oggi->tm_min,
        tm_oggi->tm_hour);
}


void stampa_data(Data d) {
    // Stampa la data in formato gg/mm/aaaa
    printf("%02d/%02d/%04d", d->giorno, d->mese, d->anno);
}

int differenza_giorni(Data d1, Data d2) {
    // Ritorna differenza in giorni usando JDN
    return (int)(data_to_jdn(d2) - data_to_jdn(d1));
}


// Restituisce il giorno dalla struttura Data
int data_get_giorno(Data d) {
    return d->giorno;
}

// Restituisce il mese dalla struttura Data
int data_get_mese(Data d) {
    return d->mese;
}

// Restituisce l’anno dalla struttura Data
int data_get_anno(Data d) {
    return d->anno;
}
int data_get_secondi(Data d) {
    return d->secondi;
}

int data_get_minuti(Data d) {
    return d->minuti;
}

int data_get_ore(Data d) {
    return d->ore;
}

int data_valida(Data d) {


    // Controllo anno
    if (d->anno < 1900 || d->anno > 3000) {
        return 0;
    }

    // Controllo mese
    if (d->mese < 1 || d->mese > 12) {
        return 0;
    }

    // Giorni massimi per ogni mese
    int mdays[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    // Bisestile?
    if ((d->anno % 4 == 0 && d->anno % 100 != 0) || (d->anno % 400 == 0)) {
        mdays[2] = 29;
    }

    // Controllo giorno
    if (d->giorno < 1 || d->giorno > mdays[d->mese]) {
        return 0;
    }

    if (d->secondi <0 || d->secondi > 60) {
        return 0;
    }
    if (d->minuti <0 || d->minuti > 59) {
        return 0;
    }
    if (d->ore <0 || d->ore > 23) {
        return 0;
    }

    return 1;
}

