// Librerías utilizadas
#include <stdio.h>  // Librería estándar de entrada y salida

// Función recursiva que resuelve el problema de las torres de Hanoi
void hanoi(int n, char origen, char destino, char auxiliar) {
    if (n == 1) {
        printf("Mover disco 1 de %c a %c\n", origen, destino);
        return;
    }
    // Mueve n-1 discos de la torre de origen a la torre auxiliar
    hanoi(n - 1, origen, auxiliar, destino);
    // Mueve el disco restante de la torre de origen a la torre destino
    printf("Mover disco %d de %c a %c\n", n, origen, destino);
    // Mueve n-1 discos de la torre auxiliar a la torre destino
    hanoi(n - 1, auxiliar, destino, origen);
}

// Función principal del programa
int main() {
    // Declaración de variables
    int n;
    printf("Ingrese el número de discos: ");
    scanf("%d", &n);
    hanoi(n, 'A', 'C', 'B');
    return 0;
}
