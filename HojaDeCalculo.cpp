#include "HojaDeCalculo.h"



void HojaCalculo::insertarCelda(int f, int c, string valor) {
    if (f < 0 || f >= cabecerasFilas.size() || c < 0 || c >= cabecerasColumnas.size()) return;


    // utilizamos dos punteros auxiliares para verificar existencia
    Celda* actual = cabecerasFilas[f];
    Celda* antFila = nullptr;

    // busca la posicion actual 
    while (actual != nullptr && actual->columna < c) {
        antFila = actual;
        actual = actual->sigEnFila;
    }

    // saliendo del while, verficamos condicion si exista la celda en c, en ese
    //caso acutalizas valor y sales de la funcion
    if (actual != nullptr && actual->columna == c) {
        actual->valor = valor;
        return;
    }

    // si no existe en fila ,entonces  no existe. cremos nuevo nodo y luego conectamos
    Celda* nuevo = new Celda(f, c, valor);

    // conectamos en fila: el primer caso si es el primer elemento de la fila,
    // y el segundo ya existen elementos en la fila pero falta esa celda con columna c.
    if (antFila == nullptr) {
        nuevo->sigEnFila = cabecerasFilas[f];
        cabecerasFilas[f] = nuevo;
    } else {
        nuevo->sigEnFila = antFila->sigEnFila;
        antFila->sigEnFila = nuevo;
    }

    // analogamente conectamos en la columnas
    Celda* actualCol = cabecerasColumnas[c];
    Celda* antCol = nullptr;

    while (actualCol != nullptr && actualCol->fila < f) {
        antCol = actualCol;
        actualCol = actualCol->sigEnColumna;
    }

    if (antCol == nullptr) {
        nuevo->sigEnColumna = cabecerasColumnas[c];
        cabecerasColumnas[c] = nuevo;
    } else {
        nuevo->sigEnColumna = antCol->sigEnColumna;
        antCol->sigEnColumna = nuevo;
    }
}