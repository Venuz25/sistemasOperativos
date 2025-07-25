// Liberías utilizadas en el programa
#include <stdio.h>   // Librería estándar de entrada y salida
#include <stdlib.h>  // Librería de utilidades estándar
#include "pila_dinamica/pila_din.h"  // Librería de pilas

// gcc evaluarExpInfija.c pila_dinamica/pila_din.c -o evaluarExpInfija

#define MAX 200

// Devuelve el valor de precedencia del operador actual.
int valorPrecedencia(char c) {
    int valor=0;
    if(c == '*' || c == '/') valor=2;
    else if(c == '+' || c == '-') valor=1;
    return valor;
}

// Retorna true o false si un caracter es un operador
boolean esOperador(char c) {
    return (c=='*' || c=='/' || c=='+' || c=='-');
}


// Retorna true o false si un caracter es un operando
boolean esOperando(char c) {
    return (c>='0' && c<='9');
}

// Se crea un nodo en el árbol de expresiones
nodoArbol *creaNodo(int x, char op) {
    nodoArbol *aux = (nodoArbol*)malloc(sizeof(nodoArbol));
    aux->x = x;
    aux->op = op;
    aux->izq = NULL;
    aux->der = NULL;
    return aux;
}

// Construye el árbol de expresiones
nodoArbol *crearArbol(char *expresion) {
    // Declaración de variables
    Pila operandos, operadores;
    nodoArbol *nuevoArbol = NULL;
    elemento e;
    int idx=0, len, sum=0;

    // Inicialización de las pilas auxiliares
    Initialize(&operadores);
    Initialize(&operandos);

    while(expresion[idx] != '\0') {
        sum = 0;
        if(expresion[idx] == '(' || expresion[idx] == '[' || expresion[idx] == '{') {
            e.c = '(';
            Push(&operadores, e);
            idx++;
        }
        else if(esOperando(expresion[idx])) {
            while(esOperando(expresion[idx])) {
                sum *= 10;
                sum += expresion[idx++] - '0';
            }
            e.arbol = creaNodo(sum, 0);
            e.c = 0;
            Push(&operandos, e);
        }
        else if(esOperador(expresion[idx])) {
            while(!Empty(&operadores) && valorPrecedencia(Top(&operadores).c) >= valorPrecedencia(expresion[idx])) {
                e = Pop(&operadores);
                
                nuevoArbol = creaNodo(0, e.c);
                nodoArbol *aux1 = Pop(&operandos).arbol;
                nuevoArbol->der = aux1;
                nuevoArbol->izq = Pop(&operandos).arbol;
                
                e.c = 0;
                e.arbol = nuevoArbol;
                Push(&operandos, e);
            }
            e.arbol = NULL;
            e.c = expresion[idx++];
            Push(&operadores, e);
        }
        else if(expresion[idx] == ')' || expresion[idx] == ']' || expresion[idx] == '}') {
            while(!Empty(&operadores) && Top(&operadores).c != '(') {
                e = Pop(&operadores);

                nuevoArbol = creaNodo(0, e.c);
                nuevoArbol->der = Pop(&operandos).arbol;
                nuevoArbol->izq = Pop(&operandos).arbol;

                e.arbol = nuevoArbol;
                e.c = 0;
                Push(&operandos, e);
            }
            Pop(&operadores);
            idx++;
        }
        else 
            idx++;
    }

    // Vacía la cola con los operadores
    while(!Empty(&operadores)) {
        e = Pop(&operadores);

        nuevoArbol = creaNodo(0, e.c);
        nuevoArbol->der = Pop(&operandos).arbol;
        nuevoArbol->izq = Pop(&operandos).arbol;

        e.c = 0;
        e.arbol = nuevoArbol;
        Push(&operandos, e);
    }
    return Top(&operandos).arbol;
}


// Función para evaluar una expresión en el árbol de expresiones
int evaluarExpresion(nodoArbol *root) {
    if(root == NULL) {
        return 0;
    }

    if(root->izq == NULL && root->der == NULL) {
        return root->x;
    }

    int sumIzq, sumDer;
    sumIzq = evaluarExpresion(root->izq);
    sumDer = evaluarExpresion(root->der);

    if(root->op == '*') 
        return sumIzq * sumDer;
    else if(root->op == '/')
        return sumIzq / sumDer;
    else if(root->op == '+')
        return sumIzq + sumDer;
    else if(root->op == '-')
        return sumIzq - sumDer;
    return 0;
}

// Función principal del programa
int main() {
    char expresion[MAX];

    printf("Ingresa una expresion aritmetica: ");
    scanf("%s", &expresion);

    nodoArbol *root = crearArbol(expresion);
    printf("Resultado: %d\n", evaluarExpresion(root));

    free(root);
}