#include <stdio.h>

// Definizione della struct Data
typedef struct {
    int giorno;
    int mese;
    int anno;
} Data;

Data crea_data(int giorno, int mese, int anno) {
    Data d;
    d.giorno = giorno;
    d.mese = mese;
    d.anno = anno;
    return d;
}

// Funzione per sapere se un anno è bisestile
int bisestile(int anno) {
    return (anno % 4 == 0 && (anno % 100 != 0 || anno % 400 == 0));
}

// Funzione che restituisce i giorni del mese dato mese e anno
int giorni_mese(int mese, int anno) {
    switch (mese) {
        case 2:
            return bisestile(anno) ? 29 : 28;
        case 4: case 6: case 9: case 11:
            return 30;
        default:
            return 31;
    }
}

// Funzione privata per convertire una data in giorni dall'anno 0
static int giorni_totali(Data d) {
    int giorni = d.giorno;
    for (int m = 1; m < d.mese; ++m)
        giorni += giorni_mese(m, d.anno);
    giorni += 365 * d.anno + d.anno/4 - d.anno/100 + d.anno/400;
    return giorni;
}

// Calcola i giorni tra due date
int giorni_tra(Data d1, Data d2) {
    return giorni_totali(d1) - giorni_totali(d2);
}

void stampa_data(Data d) {
    printf("%02d/%02d/%04d", d.giorno, d.mese, d.anno);
}