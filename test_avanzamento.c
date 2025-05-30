
#include "funzione_test.h"




int main(){
    // Input validi in corso
    test_avanzamento("TC1_avanzamento.txt","TC1_avanzamento_output.txt","TC1_avanzamento_oracle.txt","TC1_avanzamento",lista_attivita_set_avanzamento,"in corso");
    test_avanzamento("TC2_avanzamento.txt","TC2_avanzamento_output.txt","TC2_avanzamento_oracle.txt","TC2_avanzamento",lista_attivita_set_avanzamento,"completata");
    test_avanzamento("TC3_avanzamento.txt","TC3_avanzamento_output.txt","TC3_avanzamento_oracle.txt","TC3_avanzamento",lista_attivita_set_avanzamento,"in ritardo");

    // Input avanzamento non valido
    test_avanzamento("TC4_avanzamento.txt","TC4_avanzamento_output.txt","TC4_avanzamento_oracle.txt","TC4_avanzamento",lista_attivita_set_avanzamento,"in ritardo");

    return 0;
}
