

studio_manager.exe : data tempo attivita_di_studio item-attivita_di_studio lista list utils main
	gcc data.o tempo.o attivita_di_studio.o main.o utils.o\
	    item-attivita_di_studio.o list.o lista_attivita.o \
	    -o studio_manager.exe









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
	del *.o *.exe
