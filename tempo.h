#ifndef TEMPO_H
#define TEMPO_H

#include "data.h"
/*
 * Funzione: giorni_alla_scadenza
 * ------------------------------
 * Calcola quanti giorni mancano dalla data odierna alla data d.
 *
 * Parametri:
 *   d – Data di scadenza
 *
 * Ritorna:
 *   Differenza in giorni (positiva se d > oggi, negativa se d < oggi)
 */
int giorni_alla_scadenza(Data d);

#endif
