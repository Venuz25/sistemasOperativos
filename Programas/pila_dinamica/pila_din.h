// Archivo de encabezado (header) con las definiciones
// de constantes, estructuras de datos y prototipos
// de funciones utilizadas en la librería de Pilas 
// dinámics (stack)

// Definiciones de constantes
#define true 1
#define false 0

// Definiciones de tipos de dato

//Definir un boolean (Se modela con un "char")
typedef char boolean;

// Definición de la estructura del nodo del árbol de expresiones
typedef struct nodoArbol {
    char op;
    int x;
    struct nodoArbol* izq;
    struct nodoArbol* der;
} nodoArbol;

// Definición de la estructura del elemento en la pila
typedef struct elemento {
    char c;
    struct nodoArbol *arbol;
} elemento;

//Definir un nodo que será utilizado para almacenar una posición de la Pila (Nodo), 
// lo que incluirá a un elemento y a un apuntador al nodo de debajo
typedef struct nodo {
	elemento e;
	struct nodo *abajo;	
} nodo;

//Definir una Pila (Se modela con una estructura que unicamente incluye un puntero
// a "elemento" y una varieble para almacenar su tamaño)
typedef struct Pila {
	nodo *tope;
	int size;
} Pila;

// Declaración o prototipos de funciones
void Initialize(Pila *S);
void Push(Pila *S, elemento e);
elemento Pop(Pila *S);
boolean Empty(Pila *S);
elemento Top(Pila *S);
int Size(Pila *S);
void Destroy(Pila *S);