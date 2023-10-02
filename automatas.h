#include <ctype.h>

int ColumnaDecimal (int);
int ColumnaOctal (int);
int ColumnaHexadecimal (int);

int AutomataDecimal (const char *cadena) {
    int errores = 0;
    static int tablaT [4][4] = {{1,3,2,3},
                                {1,1,3,3},
                                {1,3,3,3},
                                {3,3,3,3}, /* rechazo */
                                };
    int estActual = 0;
    unsigned int i = 0;
    int caracter = cadena[0]; /* primer caracter */
    while (caracter != '\0') {
        int columna  = ColumnaDecimal(caracter);
        if (columna == 3) {
            errores++;
        }
        estActual=tablaT[estActual][columna];
        caracter = cadena[++i];
    }
    if (estActual == 1) return 1; /* estado final */
    printf("La palabra no fue reconocida, la cantidad de errores es: %d\n", errores);
    return 0;
}

int AutomataOctal (const char *cadena) {
    int errores = 0;
    static int tablaT [3][2] = {{1,2},
                                {1,2},
                                {2,2}, /* rechazo */
                                };
    int estActual = 0; /* estado inicial */
    unsigned int i = 0; /* recorre la cadena */
    int caracter = cadena[0]; /* primer caracter */
    while (caracter != '\0' && estActual != 2) {
        int columna  = ColumnaOctal(caracter);
        if (columna == 1) {
            errores++;
        }
        estActual=tablaT[estActual][columna];
        caracter = cadena[++i];
        if (ColumnaDecimal(caracter) == 1) {errores++;}
    }
 if (estActual == 1) return 1; /* estado final */
 printf("La palabra no fue reconocida, la cantidad de errores es: %d\n", errores);
 return 0;
}

int AutomataHexadecimal (const char *cadena) {
    int errores = 0;
    static int tablaT [3][2] = {{1,2},
                                {1,2},
                                {2,2}, /* rechazo */
                                };
    int estActual = 0; /* estado inicial */
    unsigned int i = 0; /* recorre la cadena */
    int caracter = cadena[0]; /* primer caracter */
    while (caracter != '\0' && estActual != 2) {
        int columna  = ColumnaHexadecimal(caracter);
        if (columna == 1) {
            errores++;
        }
        estActual=tablaT[estActual][columna];
        caracter = cadena[++i];
    }
 if (estActual == 1) return 1; /* estado final */
 printf("La palabra no fue reconocida, la cantidad de errores es: %d\n", errores);
 return 0;
}

int ColumnaDecimal (int c) {
    if (c >= '1' && c <= '9') return 0;
    if (c == '0') return 1;
    if (c == '-') return 2;
    return 3;
}

int ColumnaOctal (int c) {
    if (c >= '0' && c <= '7') return 0;
    return 1;
}

int ColumnaHexadecimal (int c) {
    if ((c >= '0' && c <= '9') || toupper(c) == 'A' || toupper(c) == 'B' || toupper(c) == 'C' || toupper(c) == 'D' || toupper(c) == 'E' || toupper(c) == 'F') return 0;
    return 1;
}