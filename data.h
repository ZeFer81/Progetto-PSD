#ifndef DATA_H
#define DATA_H

typedef struct {
    int giorno;
    int mese;
    int anno;
} Data;

// Operator: crea_data
Data crea_data(int giorno, int mese, int anno);

// Operator: confronto_date (restituisce -1 se d1<d2, 0 se uguali, 1 se d1>d2)
int confronto_date(Data d1, Data d2);

// Operator: giorni_tra (restituisce giorni tra due date; negativo se d1<d2)
int giorni_tra(Data d1, Data d2);

// Operator: stampa_data (gg/mm/aaaa)
void stampa_data(Data d);

#endif