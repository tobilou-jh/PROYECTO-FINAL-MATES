#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include ".\Librerias\colores.h"  // Incluir la librería de colores

#define MAX_TERMS 100

typedef struct {
    int terms[MAX_TERMS][10]; // Suponiendo un máximo de 10 variables
    int numTerms;
} SOPExpression;

// Función para generar la tabla de verdad
void generarTablaDeVerdad(int numVariables, int tabla[][numVariables + 1], int numFilas) {
    for (int i = 0; i < numFilas; i++) {
        for (int j = 0; j < numVariables; j++) {
            tabla[i][j] = (i >> (numVariables - j - 1)) & 1;
        }
    }
}

// Función para construir la expresión SOP y almacenar términos
void construirExpresionSOP(int numVariables, int tabla[][numVariables + 1], int numFilas, SOPExpression *expresion) {
    int primeraSuma = 1;
    expresion->numTerms = 0;

    for (int i = 0; i < numFilas; i++) {
        if (tabla[i][numVariables] == 1) {
            if (!primeraSuma) {
                printf(" + ");
            }
            primeraSuma = 0;
            printf("(");
            int primerProducto = 1;
            for (int j = 0; j < numVariables; j++) {
                if (!primerProducto) {
                    printf(" * ");
                }
                primerProducto = 0;
                printf("%c", 'A' + j);
                if (tabla[i][j] == 0) {
                    printf("'");
                    expresion->terms[expresion->numTerms][j] = 0;
                } else {
                    expresion->terms[expresion->numTerms][j] = 1;
                }
            }
            printf(")");
            expresion->terms[expresion->numTerms][numVariables] = 1;
            expresion->numTerms++;
        }
    }
    printf("\n");
}

// Función para mostrar el menú
void mostrarMenu() {
    print_color(CYAN, "\n***********************************\n");
    print_color(YELLOW, "   PROYECTO DE MATES DISCRETAS I\n");
    print_color(CYAN, "***********************************\n\n");
    print_color(MAGENTA, "INTEGRANTES:\n");
    print_color(BLUE, "Jaime Hidalgo\n");
    print_color(BLUE, "Elias Armas\n\n");
    print_color(CYAN, "NCR:\n");
    print_color(BRIGHT_YELLOW, "5535\n\n");
    print_color(RED, "Programa:\n");
    print_color(GREEN, "La funcion del programa es generar primero una tabla de verdad booleana ya sea de 2 o 3 variables dependiendo de lo que ingrese el usuario, despues generar una expresion SOP tomando los valores de 0 y 1 que ingreso el usuario en las filas que pide rellanar el progrma, la expresion se forma gracias los valores 1 que ingreso el usuario, despues con esta expresion SOP se genra la tabla de resultados parciales de esta. \n\n");
    print_color(BRIGHT_MAGENTA, "2025\n\n");
}

// Función para imprimir la tabla de verdad con los valores después de los dos puntos en verde
void imprimirTablaDeVerdad(int numVariables, int tabla[][numVariables + 1], int numFilas) {
    printf("\nTabla de Verdad:\n");

    // Imprimir encabezado de la tabla de verdad
    for (int i = 0; i < numVariables; i++) {
        printf("%c ", 'A' + i);
    }
    printf("S\n");

    for (int i = 0; i < numFilas; i++) {
        for (int j = 0; j < numVariables; j++) {
            printf("%d ", tabla[i][j]);
        }
        printf(": ");
        print_color(GREEN, "%d\n", tabla[i][numVariables]);
    }
}

// Función para graficar la tabla de resultados parciales
void graficarTablaResultados(int numVariables, int tabla[][numVariables + 1], int numFilas, SOPExpression *expresion) {
    printf("Tabla de Resultados Parciales:\n");

    // Encabezado dinámico
    for (int t = 0; t < expresion->numTerms; t++) {
        printf("(");
        for (int j = 0; j < numVariables; j++) {
            printf("%c", 'A' + j);
            if (expresion->terms[t][j] == 0) {
                printf("'");
            }
            if (j < numVariables - 1) {
                printf(" * ");
            }
        }
        if (t < expresion->numTerms - 1) {
            printf(") + ");
        } else {
            printf(")");
        }
    }
    printf("\n");
    for (int t = 0; t < expresion->numTerms; t++) {
        for (int j = 0; j < numVariables * 4; j++) {
            printf("-");
        }
        printf(" ");
    }
    printf("\n");

    // Evaluar y mostrar resultados parciales
    for (int i = 0; i < numFilas; i++) {
        int resultadoFinal = 0;
        for (int t = 0; t < expresion->numTerms; t++) {
            int resultadoTermino = 1;
            for (int j = 0; j < numVariables; j++) {
                int valor = tabla[i][j];
                if (expresion->terms[t][j] == 0) {
                    valor = !valor;
                }
                resultadoTermino &= valor;
                printf("%d ", valor);
                if (j < numVariables - 1) {
                    printf("* ");
                }
            }
            resultadoFinal |= resultadoTermino;
            printf("= ");
            print_color(GREEN, "%d ", resultadoTermino); // Imprimir resultado de AND en verde
            if (t < expresion->numTerms - 1) {
                printf("+ ");
            } else {
                printf(" ");
            }
        }
        printf("= ");
        print_color(RED, "%d\n", resultadoFinal); // Imprimir resultado de OR en rojo
    }
}

int main() {
    int numVariables;

    // Mostrar el menú
    mostrarMenu();

    while (1) {
        print_color_bg(BLACK, BG_MAGENTA, "Ingrese el numero de variables booleanas (2 o 3): ");
        scanf("%d", &numVariables);
        if (numVariables == 2 || numVariables == 3) {
            break;
        } else {
            print_color(RED, "Numero de variables no valido. Debe ser 2 o 3.\n");
        }
    }

    int numFilas = 1 << numVariables; // 2^numVariables
    int tabla[numFilas][numVariables + 1];
    SOPExpression expresion;

    generarTablaDeVerdad(numVariables, tabla, numFilas);

    print_color_bg(BRIGHT_BLUE,BG_BLACK,"Ingrese los valores de salida para cada fila de la tabla de verdad (0 o 1):\n");
    
    // Imprimir encabezado de la tabla
    for (int i = 0; i < numVariables; i++) {
        printf("%c ", 'A' + i);
    }
    printf("S\n");

    for (int i = 0; i < numFilas; i++) {
        for (int j = 0; j < numVariables; j++) {
            printf("%d ", tabla[i][j]);
        }
        printf(": ");
        int value;
        while (1) {
            scanf("%d", &value);
            if (value == 0 || value == 1) {
                tabla[i][numVariables] = value;
                break;
            } else {
                print_color(RED, "Valor no valido. Ingrese 0 o 1: ");
            }
        }
    }

    imprimirTablaDeVerdad(numVariables, tabla, numFilas);

    print_color(BLUE, "\nExpresion SOP: ");
    print_color(YELLOW, "");
    construirExpresionSOP(numVariables, tabla, numFilas, &expresion);

    graficarTablaResultados(numVariables, tabla, numFilas, &expresion);

    return 0;
}





