#ifndef COLORES_H
#define COLORES_H

#include <stdio.h>
#include <stdarg.h>

// Definiciones de colores de texto
#define RESET       "\x1b[0m"
#define BLACK       "\x1b[30m"
#define RED         "\x1b[31m"
#define GREEN       "\x1b[32m"
#define YELLOW      "\x1b[33m"
#define BLUE        "\x1b[34m"
#define MAGENTA     "\x1b[35m"
#define CYAN        "\x1b[36m"
#define WHITE       "\x1b[37m"
#define BRIGHT_BLACK    "\x1b[90m"
#define BRIGHT_RED      "\x1b[91m"
#define BRIGHT_GREEN    "\x1b[92m"
#define BRIGHT_YELLOW   "\x1b[93m"
#define BRIGHT_BLUE     "\x1b[94m"
#define BRIGHT_MAGENTA  "\x1b[95m"
#define BRIGHT_CYAN     "\x1b[96m"
#define BRIGHT_WHITE    "\x1b[97m"

// Definiciones de colores de fondo
#define BG_BLACK       "\x1b[40m"
#define BG_RED         "\x1b[41m"
#define BG_GREEN       "\x1b[42m"
#define BG_YELLOW      "\x1b[43m"
#define BG_BLUE        "\x1b[44m"
#define BG_MAGENTA     "\x1b[45m"
#define BG_CYAN        "\x1b[46m"
#define BG_WHITE       "\x1b[47m"
#define BG_BRIGHT_BLACK    "\x1b[100m"
#define BG_BRIGHT_RED      "\x1b[101m"
#define BG_BRIGHT_GREEN    "\x1b[102m"
#define BG_BRIGHT_YELLOW   "\x1b[103m"
#define BG_BRIGHT_BLUE     "\x1b[104m"
#define BG_BRIGHT_MAGENTA  "\x1b[105m"
#define BG_BRIGHT_CYAN     "\x1b[106m"
#define BG_BRIGHT_WHITE    "\x1b[107m"

// Función para imprimir texto en color
void print_color(const char *color, const char *format, ...) {
    va_list args;
    va_start(args, format);
    printf("%s", color);
    vprintf(format, args);
    printf("%s", RESET);
    va_end(args);
}

// Función para imprimir texto con color de fondo
void print_color_bg(const char *color, const char *bg_color, const char *format, ...) {
    va_list args;
    va_start(args, format);
    printf("%s%s", color, bg_color);
    vprintf(format, args);
    printf("%s", RESET);
    va_end(args);
}

#endif // COLORES_H