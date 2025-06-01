#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int number(int size_name_file) {
    static int k = 1;          // Numero da restituire (partiamo da 1)
    static int count = 0;      // Quante volte ho restituito k

    if (count < size_name_file) {
        count++;
        return k;
    } else {
        k++;
        count = 1;  // Questa chiamata conta già come la prima volta del nuovo k
        return k;
    }
}

char int_to_char(int n) {
    if (n >= 0 && n <= 9)
        return '0' + n;

    return '?';
}
char *gen_ind_file(int idx) {
    int n = 11;
    char *file_name = malloc(n+1);
    if (!file_name) {
        return NULL;
    }
    memset(file_name, '0', n);
    file_name[n] = '\0';


    int c= 0;
    int  j = 0, i = 0;
    int k = 0;



            while (i<idx)
            {

                file_name[k] = int_to_char(number(n));
                printf("file_name = %s\n",  file_name);


                k++;
                c++;
                i++;
                if (j<=9) {
                    j++;
                }
                if (j>9) {
                    j = 0;
                }
                if (k>10) {
                    k = 0;
                }



            }




    printf("count = %d\n", c);


    return file_name;


}


int main() {

    gen_ind_file(99);


    return 0;
}