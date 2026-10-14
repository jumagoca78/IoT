/* ==============================================================
 * SIMULADOR DE PATOS - PATRON ESTRATEGIA (C11)
 * Elaborado por Juan Manuel Gonzalez Calleros
 * Curso: Implementacion de Internet de las Cosas (IoT)
 * Compilar: gcc -std=c11 -Wall -Wextra main.c -o patos
 * Ejecutar: ./patos
 * NOTA: C no tiene clases ni interfaces; usamos structs y punteros
 *       a funcion para aplicar los mismos PRINCIPIOS del patron.
 * ============================================================= */
#include <stdio.h>  /* printf: salida por consola. */

/* Cada funcion concreta es una estrategia posible de vuelo.
 * La firma void funcion(void) actua como contrato comun. */
void volar_alas(void)   { puts("Vuelo con alas"); }
void no_volar(void)     { puts("No puedo volar"); }
void volar_cohete(void) { puts("Vuelo impulsado por un cohete"); }

/* Segunda familia de algoritmos, independiente del vuelo. */
void graznar(void) { puts("Quack, quack"); }
void chillar(void) { puts("Squeak, squeak"); }
void silencio(void){ puts("(Sin sonido)"); }

/* TIPOS DE FUNCION: nombres de contrato para punteros a funcion.
 * A diferencia de Java, C no comprueba una interfaz de objeto,
 * sino la compatibilidad de las firmas de las funciones. */
typedef void (*VueloFn)(void);
typedef void (*GraznidoFn)(void);

/* El contexto Pato TIENE los comportamientos que ejecutara.
 * Separa datos estables (nombre) de algoritmos sustituibles. */
typedef struct {
    const char *nombre; /* Etiqueta del tipo de pato. */
    VueloFn vuelo;      /* Puntero a la estrategia activa de vuelo. */
    GraznidoFn voz;     /* Puntero a la estrategia activa de sonido. */
} Pato;

/* Constructor funcional: inicializa un struct Pato, sin malloc.
 * Como los patos viven en main, no necesitamos memoria dinamica. */
Pato crear_pato(const char *nombre, VueloFn vuelo, GraznidoFn voz) {
    Pato p = {nombre, vuelo, voz};
    return p;
}

/* Los metodos se simulan como funciones que reciben el contexto. */
void mostrar(const Pato *p) { printf("Pato %s\n", p->nombre); }
void nadar(const Pato *p) { (void)p; puts("Floto en el agua"); }
void ejecutar_vuelo(const Pato *p) { p->vuelo(); } /* DELEGACION. */
void ejecutar_graznido(const Pato *p) { p->voz(); }

/* Cambiar una estrategia significa sustituir su puntero a funcion.
 * No modificamos la funcion ejecutar_vuelo(): ese es el beneficio. */
void cambiar_vuelo(Pato *p, VueloFn nuevo) { p->vuelo = nuevo; }
void cambiar_graznido(Pato *p, GraznidoFn nuevo) { p->voz = nuevo; }

int main(void) {
    /* Cuatro configuraciones que corresponden a los patos de clase. */
    Pato patos[] = {
        crear_pato("Mallard", volar_alas, graznar),
        crear_pato("Redhead", volar_alas, graznar),
        crear_pato("Rubber (goma)", no_volar, chillar),
        crear_pato("Decoy (madera)", no_volar, silencio)
    };
    /* sizeof calcula el numero de elementos del arreglo local. */
    size_t cantidad = sizeof(patos) / sizeof(patos[0]);
    for (size_t i = 0; i < cantidad; ++i) {
        puts("\n---");
        mostrar(&patos[i]); nadar(&patos[i]);
        ejecutar_vuelo(&patos[i]); ejecutar_graznido(&patos[i]);
    }
    puts("\n--- Cambio dinamico de Mallard ---");
    cambiar_vuelo(&patos[0], volar_cohete);
    cambiar_graznido(&patos[0], silencio);
    ejecutar_vuelo(&patos[0]); ejecutar_graznido(&patos[0]);
    return 0;
}
