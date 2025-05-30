
#include "funzione_test.h"




int main(){
    // Input validi in corso
    test_avanzamento("TC1_avanzamento.txt","TC1_avanzamento_output.txt","TC1_avanzamento_oracle.txt","TC1_avanzamento",attivita_set_avanzamento,"in corso");
    test_avanzamento("TC2_avanzamento.txt","TC2_avanzamento_output.txt","TC2_avanzamento_oracle.txt","TC2_avanzamento",attivita_set_avanzamento,"completata");
    test_avanzamento("TC3_avanzamento.txt","TC3_avanzamento_output.txt","TC3_avanzamento_oracle.txt","TC3_avanzamento",attivita_set_avanzamento,"in ritardo");

    return 0;
}
