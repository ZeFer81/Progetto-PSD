#include <stdio.h>
#include "funzione_test.h"

int main()
{



    run_test("TC1_inserimento",
             "TC1_inserimento.txt",
             "TC1_inserimento_output.txt",
             "TC1_inserimento_oracle.txt"
             );

    //TEST 2 INput non valido Data tranne uno
    run_test("TC2_inserimento",
             "TC2_inserimento.txt",
             "TC2_inserimento_output.txt",
             "TC2_inserimento_oracle.txt"
             );


    run_test("TC3_inserimento",
             "TC3_inserimento.txt",
             "TC3_inserimento_output.txt",
             "TC3_inserimento_oracle.txt"
             );


    run_test("TC4_inserimento",
             "TC4_inserimento.txt",
             "TC4_inserimento_output.txt",
             "TC4_inserimento_oracle.txt"
             );


    run_test("TC5_inserimento",
             "TC5_inserimento.txt",
             "TC5_inserimento_output.txt",
             "TC5_inserimento_oracle.txt"
             );

    run_test("TC6_inserimento",
             "TC6_inserimento.txt",
             "TC6_inserimento_output.txt",
             "TC6_inserimento_oracle.txt"
             );




    run_test("TC7_inserimento",
             "TC7_inserimento.txt",
             "TC7_inserimento_output.txt",
             "TC7_inserimento_oracle.txt"
             );



    run_test("TC8_inserimento",
             "TC8_inserimento.txt",
             "TC8_inserimento_output.txt",
             "TC8_inserimento_oracle.txt"
             );



    return 0;
}