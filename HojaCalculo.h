#ifndef HOJACALCULO_H
#define HOJACALCULO_H
#include "Celda.h"
#include <vector>
#include <iostream>

using namespace std;


class HojaCalculo {
private:
    // Arreglos de punteros para las cabeceras (headers)
    vector<Celda*> cabecerasFilas;
    vector<Celda*> cabecerasColumnas;

public:
    // Constructor
    HojaCalculo(int maxFilas = 1000, int maxCols = 1000) {
        cabecerasFilas.assign(maxFilas, nullptr);
        cabecerasColumnas.assign(maxCols, nullptr);
    }

    // funciones a implementar 
    void insertarCelda(int f, int c, string valor);
    string consultarCelda(int f, int c);
    void eliminarCelda(int f, int c);
    void modificarCelda(int f, int c, string valor);
    void eliminarFila(int f);
    void eliminarColumna(int c);
    void eliminarRango(int fInicio, int cInicio, int fFin, int cFin);
    void printing();
    
    
};
#endif