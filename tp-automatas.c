#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include ".\automatas.h"

#define DECIMAL 1
#define OCTAL 2
#define HEXADECIMAL 3
#define MAX_TAMANO_PALABRA 100

 /*Imprime en pantalla si el automata utilizado reconoció o no la palabra*/
void printSiReconoce (const char * palabra, int resultado) {
    if (resultado) {
        printf("El automata reconocio la palabra %s\n", palabra);
    } else {
        printf("El automata NO reconocio la palabra %s\n", palabra);
    }
}

/*Elimina el prefijo de la palabra para reconocerlo con el automata correspondiente*/
char *quitarPrefijo (char *palabra, int longPrefijo) {
    int i;
    for (i=0; palabra[i+longPrefijo] != '\0'; i++) {
        palabra[i] = palabra[i+longPrefijo];
    }
    palabra[i] = '\0';
    return palabra;
}

/*Verificamos si la palabra que ingresa por variable es un valor decimal, octal o hexadecimal segun su prefijo
Si el valor empieza con 0 se lo considera octal
Si el valor comienza con 0x se lo considera hexadecimal
Si no tiene nunguno de los prefijos anteriores se lo considera decimal
*/
int definirTipoDePalabra (char *palabra) {
    if (palabra[0] != '0' && isdigit(palabra[0])) {
        return DECIMAL;
    } else {
        if (palabra[1] == 'x') {
            palabra = quitarPrefijo(palabra,2);
            return HEXADECIMAL;
        }
        palabra = quitarPrefijo(palabra,1);
        return OCTAL;
    }
}

/*Dependiendo del tipo de palabra, lo intenta reconocer con el automata correspondiente*/
int automata (char *palabra) {
    int tipoDePalabra = definirTipoDePalabra(palabra);
    if (tipoDePalabra == DECIMAL) {
        return AutomataDecimal(palabra);
    } else if (tipoDePalabra == OCTAL) {
        return AutomataOctal(palabra);
    }
    return AutomataHexadecimal(palabra);
}

int main () {
    FILE * palabras;
    palabras = fopen("palabras.txt","r+t");
    int c;
    int i = 0;
    char *palabraNueva = malloc(MAX_TAMANO_PALABRA);
    /*Recorremos el archivo y creamos una cadena auxiliar que sera la palabra a identificar por el automata
    Cuando llega al caracter $, como lo lee y lo adhiere a la cadena auxiliar, lo reemplazamos en la cadena por el caracter \0
    Una vez tenemos la palabra la reconocemos por el automata
    */    
    while ((c=fgetc(palabras)) != EOF) {
        palabraNueva[i] = c;
        i++;
        if (c == '$') {
            palabraNueva[i-1] = '\0';
            int reconoce = automata(palabraNueva);
            printSiReconoce (palabraNueva,reconoce);
            i = 0;
        }
    } 
    palabraNueva[i] = '\0';
    int reconoce = automata(palabraNueva);
    printSiReconoce (palabraNueva,reconoce);

    free(palabraNueva);
    fclose(palabras);

    return 0;
}