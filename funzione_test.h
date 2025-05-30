#ifndef FUNZIONE_TEST_H
#define FUNZIONE_TEST_H
#include "lista_attivita.h"
lista_attivita lettura_lista (char *nome_file_ingresso);
void scrittura_lista (char *nome_file, lista_attivita lista);
void confronta_file (char *oracle, char *output, char * TC);
void run_test( char *tc_name,
                      char *input_file,
                      char *output_file,
                      char *oracle_file);
void genera_report_test(char* input_file, char* output_file,char* oracle, char* TC);
void test_avanzamento( char* input_file, char* output_file,char* oracle, char* TC, bool (*setter)(AttivitaDiStudio, char*), char* stato);
#endif //FUNZIONE_TEST_H
