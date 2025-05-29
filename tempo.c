/* tempo.c */

#include "tempo.h"
#include "data.h"
#include <time.h>

/*
 * Calcola la differenza in giorni tra oggi e la data d.
 */
int giorni_alla_scadenza(Data d) {
    // Estrai giorno, mese e anno da d
    int g1 = data_get_giorno(d);
    int m1 = data_get_mese(d);
    int y1 = data_get_anno(d);

    // Prendi la data odierna
    Data oggi = data_odierna();
    int g2 = data_get_giorno(oggi);
    int m2 = data_get_mese(oggi);
    int y2 = data_get_anno(oggi);

    // Popola struct tm per d e per oggi (tm_mon 0–11, tm_year da 1900)
    struct tm tm1 = {
        .tm_mday = g1,
        .tm_mon  = m1 - 1,
        .tm_year = y1 - 1900
    };
    struct tm tm2 = {
        .tm_mday = g2,
        .tm_mon  = m2 - 1,
        .tm_year = y2 - 1900
    };

    // Converte in timestamp e calcola la differenza in secondi
    time_t t1 = mktime(&tm1);
    time_t t2 = mktime(&tm2);
    double diff = difftime(t1, t2);

    // Libera la memoria della Data odierna
    distruggi_data(oggi);

    // Restituisce la differenza in giorni
    return (int)(diff / (60 * 60 * 24));
}

