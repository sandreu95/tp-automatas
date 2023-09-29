int ColumnaDecimal (int);
int ColumnaOctal (int);
int ColumnaHexadecimal (int);

int AutomataDecimal (const char *cadena) {
    static int tablaT [4][3] = {{2,3,1},
                                {3,1,1},
                                {3,3,1},
                                {3,3,3}, /* rechazo */
                                };
    int estActual = 0; /* estado inicial */
    unsigned int i = 0; /* recorre la cadena */
    int caracter = cadena[0]; /* primer caracter */
    while (caracter != '\0' && estActual != 3) {
        estActual=tablaT[estActual][ColumnaDecimal(caracter)];
        caracter = cadena[++i];
    }
 if (estActual == 1) return 1; /* estado final */
 return 0;
}

int AutomataOctal (const char *cadena) {
    static int tablaT [3][1] = {{1},
                                {1},
                                {2}, /* rechazo */
                                };
    int estActual = 0; /* estado inicial */
    unsigned int i = 0; /* recorre la cadena */
    int caracter = cadena[0]; /* primer caracter */
    while (caracter != '\0' && estActual != 2) {
        estActual=tablaT[estActual][ColumnaOctal(caracter)];
        caracter = cadena[++i];
    }
 if (estActual == 1) return 1; /* estado final */
 return 0;
}

int AutomataHexadecimal (const char *cadena) {
    static int tablaT [3][1] = {{1},
                                {1},
                                {2}, /* rechazo */
                                };
    int estActual = 0; /* estado inicial */
    unsigned int i = 0; /* recorre la cadena */
    int caracter = cadena[0]; /* primer caracter */
    while (caracter != '\0' && estActual != 2) {
        estActual=tablaT[estActual][ColumnaHexadecimal(caracter)];
        caracter = cadena[++i];
    }
 if (estActual == 1) return 1; /* estado final */
 return 0;
}

int ColumnaDecimal (int c) {
    if (c >= '0' && c <= '9') return 1;
    if (c == '-') return 2;
    return 3;
}

int ColumnaOctal (int c) {
    if (c >= '0' && c <= '7') return 1;
    return 2;
}

int ColumnaHexadecimal (int c) {
    if ((c >= '0' && c <= '9') || c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'D' || c == 'F') return 1;
    return 2;
}