#include "HojaCalculo.h"

int main(){

    HojaCalculo hoja(100,100);

    hoja.insertarCelda(2,2, "hola");
    hoja.insertarCelda(3,2,"peru");
    hoja.insertarCelda(1,1 , "porque");
    hoja.insertarCelda(15,15,"sera");

    hoja.insertarCelda(0,0, "algo");
    hoja.insertarCelda(-1,0,"diferente");
    hoja.insertarCelda(0,2,"cierto");


    hoja.eliminarFila(0);
    hoja.eliminarColumna(2);
    hoja.printing();

    

    return 0;
}