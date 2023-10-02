#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_TAMANO_PALABRA 100

typedef struct tnodo {
    int info;
    struct tnodo* sig;
} nodo;

typedef nodo* ptrNodo;

void push(ptrNodo* pila, int info) {
    ptrNodo nuevo = (ptrNodo)malloc(sizeof(nodo));
    nuevo->info = info;
    nuevo->sig = *pila;
    *pila = nuevo;
}

int pop(ptrNodo* pila) {
    int ret = (*pila)->info;
    ptrNodo aux = (*pila);
    *pila = aux->sig;
    free(aux);
    return ret;
}

/*Se define la precedencia de las operaciones*/
int precedencia(char operador) {
    switch (operador) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

/*Se define la funcion para aplicar las operaciones*/
int operaciones(int operando1, int operando2, char operador) {
    int resultado;
    switch (operador) {
        case '+':
            resultado = operando1 + operando2;
            break;
        case '-':
            resultado = operando1 - operando2;
            break;
        case '*':
            resultado = operando1 * operando2;
            break;
        case '/':
            if (operando2 != 0) {
                resultado = operando1 / operando2;
            } else {
                printf("Error: División por cero.\n");
                exit(1);
            }
            break;
        default:
            printf("Operador no reconocido.\n");
            exit(1);
    }
    return resultado;
}

/*funcion del punto 2*/
int char_to_int(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    return -1; // Valor inválido
}

int main() {
    FILE* operacion;
    operacion = fopen("operacion.txt", "r+t");

    int c;

    ptrNodo pilaOperandos = NULL;
    ptrNodo pilaOperadores = NULL;

    
    /*Se lee el archivo con la operacion y se valida:
    -si es un digito, se hace un push a la pila de operandos
    -si es un operador, valida si dicho operador tiene menor precedencia que la info del tope de la pila, 
    en caso de sea mayor, opera y pushea el resultado en la pila. en caso de ser menor, pushea la operacion en una pila auxiliar de operandos para resolver posteriormente.
    La idea de utilizar dos pilas partio de intentar dos listas, pero observamos que era mas optimo usar pilas en cuanto a codigo. 
    Nos servimos de la ayuda de IAs para corregir errores de compilacion*/
    while ((c = getc(operacion)) != EOF) {
        if (isdigit(c)) {
            int valor = char_to_int(c);
            push(&pilaOperandos, valor);
        } else {
            while (pilaOperadores != NULL && precedencia(c) <= precedencia(pilaOperadores->info)) {
                int operando2 = pop(&pilaOperandos);
                int operando1 = pop(&pilaOperandos);
                char operador = pop(&pilaOperadores);
                int resultado = operaciones(operando1, operando2, operador);
                push(&pilaOperandos, resultado);
            }
            push(&pilaOperadores, c);
        }
    }

    /*Una vez resuelta la precedencia, se realizan las operaciones que quedaron encoladas*/
    while (pilaOperadores != NULL) {
        int operando2 = pop(&pilaOperandos);
        int operando1 = pop(&pilaOperandos);
        char operador = pop(&pilaOperadores);
        int resultado = operaciones(operando1, operando2, operador);
        push(&pilaOperandos, resultado);
    }

    int resultadoFinal = pop(&pilaOperandos);
    printf("El resultado de la operacion es %d\n", resultadoFinal);

    fclose(operacion);

    // Liberar la memoria de la pila si es necesario
    while (pilaOperandos != NULL) {
        pop(&pilaOperandos);
    }

    while (pilaOperadores != NULL) {
        pop(&pilaOperadores);
    }

    return 0;
}