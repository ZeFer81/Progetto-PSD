#include "funzione_test.h"
int main(){
    //Tc1 input validi
    genera_report_test("TC1_report.txt","TC1_report_output.txt","TC1_report_oracle.txt","TC1_report");

    //Tc2 input non validi
    genera_report_test("TC2_report.txt",
        "TC2_report_output.txt",
        "TC2_report_oracle.txt",
        "TC2_report");
    // Tc3 campo Descrizione corso vuota
    genera_report_test("TC3_report.txt",
        "TC3_report_output.txt",
        "TC3_report_oracle.txt",
        "TC3_report");
    return 0;
}