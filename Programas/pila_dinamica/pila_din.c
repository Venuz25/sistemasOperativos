// LIBRERÍA DE PILAS DINÁMICAS

// Instrucciones de comPilación para generar el
// código objeto: gcc Pila_din.c -c -o Pila_din -std=c11

// Librerías utilizadas
#include <stdio.h>     // Librería estándar de entrada y salida
#include <stdlib.h>    // Librería estándar de utilidades
#include "pila_din.h"  // Encabezado con los prototipos de funcioens

// Inicializa una Pila vacía
void Initialize(Pila *s) {
	s->size = 0;
	(*s).tope = NULL;
}

// EmPila (Inserta) un elemento a la Pila
void Push(Pila *s, elemento e) {
	nodo *aux = malloc(sizeof(nodo));
	if(aux == NULL) { //Desbordamiento de Pila
		printf("\nERROR Push(s,C):\"Desbordamiento de Pila\"");
		exit(1);	
	}
	s->size++;
	aux->e = e;
	aux->abajo = s->tope;
	s->tope = aux;
}

// Retorna si la Pila está vacía
boolean Empty(Pila *s) {
	return (s->tope != NULL) ? false : true;
}

// Retorna el tamaño de la Pila
int Size(Pila *s) {
	return s->size;
}

// Desempila (extrae) un elemento de la Pila
elemento Pop(Pila *s) {
	elemento e; nodo* aux;
	if (s->tope == NULL) { //Subdesbordamiento de la Pila
		printf("\nERROR e=Pop(s):\"Subdesbordamiento de Pila\"");
		exit(1);
	}
	e = s->tope->e;
	aux = s->tope;
	s->tope = aux->abajo;
	free(aux);
	s->size--;
	return e;
}

// Retorna el elemento del tope de la Pila (sin extraerlo)
elemento Top(Pila *s) {
	if(s->tope == NULL) { //Subdesbordamiento de la Pila
		printf("\nERROR e=Top(s):\"Subdesbordamiento de Pila\"");
		exit(1);
	}
	return s->tope->e;
}

// Borra todos los elementos en a la Pila de memoria
void Destroy(Pila *s) {
	nodo *aux;
	if(s->tope != NULL) {
		do {
			aux = s->tope->abajo;
			free(s->tope);
			s->tope = aux;	
		} while(aux != NULL);
	}
	s->size = 0;
}