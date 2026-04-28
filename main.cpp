#include "HojaCalculo.h"

int main(){

    HojaCalculo hoja(100,100);

    hoja.insertarCelda(2,2, "hola");
    hoja.insertarCelda(3,2,"peru");
    hoja.insertarCelda(1,1 , "porque");
    hoja.insertarCelda(9,8,"sera");
    hoja.insertarCelda(10,2, "hola");
    hoja.insertarCelda(0,0, "algo");
    hoja.insertarCelda(-1,0,"diferente");
    hoja.insertarCelda(0,2,"cierto");
    hoja.insertarCelda(5,5,"1");
    hoja.insertarCelda(6,5,"2");
    hoja.insertarCelda(7,5,"3");
    hoja.insertarCelda(8,5,"4");
    hoja.insertarCelda(9,5,"5");
    hoja.insertarCelda(10,5,"6");

   cout<< hoja.sumaRango(-3,-3,15,15)<<endl;
   cout<<hoja.promedioRango(-3,-3,15,15)<<endl;
   cout<<hoja.maximoRango(-3,-3,15,15)<<endl;

    

    
    
    hoja.printing();

    

    return 0;
}