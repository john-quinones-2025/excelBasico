#ifndef CELDA_H
#define CELDA_H
#include <iostream>
#include <string>

using namespace std;


struct Celda {
    int fila;
    int columna;
    string valor; // puede almacenar numeros o texto
    
    
    Celda* sigEnFila; // Apunta a la siguiente celda a la derecha
    Celda* sigEnColumna; // Apunta a la siguiente celda hacia abajo

    
    Celda(int f, int c, string v) {
        fila = f;
        columna = c;
        valor = v;
        sigEnFila = nullptr;
        sigEnColumna = nullptr;
    }
};
#endif