

studio_manager.exe : data tempo attivita_di_studio item-attivita_di_studio lista list utils main
	gcc data.o tempo.o attivita_di_studio.o main.o utils.o\
	    item-attivita_di_studio.o list.o lista_attivita.o \
	    -o studio_manager.exe


test_inserimento.exe : list utils data tempo attivita_di_studio item-attivita_di_studio lista test_inserimento funzione_test
	gcc list.o utils.o data.o tempo.o attivita_di_studio.o \
	    item-attivita_di_studio.o lista_attivita.o \
	    test_inserimento.o funzione_test.o\
	    -o test_inserimento.exe

test_inserimento :
	gcc -c test_inserimento.c



funzione_test :
	gcc -c funzione_test.c

data :
	gcc -c data.c

tempo :
	gcc -c tempo.c

attivita_di_studio :
	gcc -c attivita_di_studio.c

item-attivita_di_studio :
	gcc -c item-attivita_di_studio.c -o item-attivita_di_studio.o

lista :
	gcc -c lista_attivita.c

list :
	gcc -c list.c

utils :
	gcc -c utils.c

main :
	gcc -c main.c

clean :
	del debug.txt result.txt TC1_avanzamento_output.txt TC1_inserimento_output.txt TC1_report_output.txt \
        		TC2_inserimento_output.txt \
        		TC3_inserimento_output.txt \
        		TC4_inserimento_output.txt \
        		TC5_inserimento_output.txt \
        		TC6_inserimento_output.txt *.o *.exe

