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

    // Funciones que tu equipo deberá implementar
    void insertarCelda(int f, int c, string valor);
    string consultarCelda(int f, int c);
    void eliminarCelda(int f, int c);
    
    // (Otras operaciones irán aquí luego...)
};
#endif