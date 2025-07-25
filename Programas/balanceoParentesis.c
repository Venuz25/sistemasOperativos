#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAMAÑO 100

typedef struct {
    char elementos[TAMAÑO];
    int cima;
} Pila;

// Inicializa la pila
void inicializar(Pila *pila) {
    pila -> cima = -1;
}

// Pila está vacía
bool estaVacia(Pila *pila) {
    return pila -> cima == -1;
}

//Pila está llena
bool estaLlena(Pila *pila) {
    return pila -> cima == TAMAÑO - 1;
}

// Insertar
void insertar(Pila *pila, char valor) {
    if (estaLlena(pila)) {
        printf("Desbordamiento de pila\n");
        exit(EXIT_FAILURE);
    }

    pila -> elementos[++pila -> cima] = valor;
}

// Eliminar un elemento
char eliminar(Pila *pila) {
    if (estaVacia(pila)) {
        printf("No hay elementos que borrar\n");
        exit(EXIT_FAILURE);
    }

    return pila -> elementos[pila -> cima--];
}

// Paréntesis están balanceados
// Se guardan todas las aperturas de parentesis en la pila y al encontrar su cerradura corresponidente lo borra de la pila
// al final del for si la pila queda vacia la ecuacion esta balanceada y si queda algun elemento no esta balanceada
bool ParentesisBalanceados(char expr[]) {
    Pila pila;
    inicializar(&pila);

    for (int i = 0; expr[i] != '\0'; i++) {

        if (expr[i] == '(' || expr[i] == '{' || expr[i] == '[') {
            insertar(&pila, expr[i]);
        } 

        else if (expr[i] == ')' || expr[i] == '}' || expr[i] == ']') {
            
            //Si hay una cerradura pero la pila esta vacia no esta balanceada la ecuacion
            if (estaVacia(&pila)) {
                return false;
            }

            char eliminado = eliminar(&pila);

            // Si el tipo de cerradura que se encuentra no coincide con el ultimo tipo de abertura encontrada no esta balanceada la ecuacion
            if ((expr[i] == ')' && eliminado != '(') || (expr[i] == '}' && eliminado != '{') || (expr[i] == ']' && eliminado != '[')) {
                return false;
            }
        }
    }
    return estaVacia(&pila);
}

int main() {
    char expr[TAMAÑO];

    printf("Ingrese una expresion algebraica: ");
    fgets(expr, TAMAÑO, stdin);

    if (ParentesisBalanceados(expr)) {
        printf("Los parentesis estan balanceados :D/\n");
    } else {
        printf("Los parentesis no estan balanceados :(\n");
    }

    return 0;
}

