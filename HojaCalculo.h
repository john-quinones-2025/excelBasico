#ifndef HOJACALCULO_H
#define HOJACALCULO_H
#include "Celda.h"
#include <vector>
#include <iostream>
#include <limits>

using namespace std;


class HojaCalculo {
private:
    // Arreglos de punteros para las cabeceras (headers)
    vector<Celda*> cabecerasFilas;
    vector<Celda*> cabecerasColumnas;


    bool esNumero(const string& s) {
        try {
            stod(s);
            return true;
        } catch (...) {
            return false;
        }
    }

public:
    // Constructor
    HojaCalculo(int maxFilas = 1000, int maxCols = 1000) {
        cabecerasFilas.assign(maxFilas, nullptr);
        cabecerasColumnas.assign(maxCols, nullptr);
    }

    ~HojaCalculo();

    // funciones a implementar 
    void insertarCelda(int f, int c, string valor);
    string consultarCelda(int f, int c);
    void eliminarCelda(int f, int c);
    void modificarCelda(int f, int c, string valor);
    void eliminarFila(int f);
    void eliminarColumna(int c);
    void eliminarRango(int fInicio, int cInicio, int fFin, int cFin);
    double sumaRango(int fInicio, int cInicio, int fFin, int cFin);
    double promedioRango(int fInicio, int cInicio, int fFin, int cFin);
    double maximoRango(int fInicio, int cInicio, int fFin, int cFin);
    double minimoRango(int fInicio, int cInicio, int fFin, int cFin);
    void printing();
    
    
};
#endif