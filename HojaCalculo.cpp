#include "HojaCalculo.h"



void HojaCalculo::insertarCelda(int f, int c, string valor) {
    if (f < 0 || f >= cabecerasFilas.size() || c < 0 || c >= cabecerasColumnas.size()) {
        cout<< "valor no admitido"<<endl;
        return;
    }


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




string HojaCalculo::consultarCelda(int f, int c) {


    // vas a la cabecera de f
    Celda* actual = cabecerasFilas[f];

    //si existe entra al bucle hasta menor igual al c
    while (actual != nullptr && actual->columna <= c) {

        //verifica si llega al c y sale.
        if (actual->columna == c) return actual->valor;

        //avanza a la siguiente celda
        actual = actual->sigEnFila;
    }
    // cuando se pasa sale y retorna vacio
    return ""; 
}

void HojaCalculo::modificarCelda(int f, int c, string valor) {


    // ejecutamos insertarCelda, 
    //esta hace el recorrido hasta la posicion y actualiza
    // con el valor de entrada

    insertarCelda(f, c, valor); 
}

void HojaCalculo::eliminarCelda(int f, int c) {

    // creamos al igual que para insertar dos auxiliares para recorrer la fila
    Celda* actual = cabecerasFilas[f];
    Celda* antFila = nullptr;


    //bucle para llegar despues o igual a  la posicion c . 
    while (actual != nullptr && actual->columna < c) {
        antFila = actual;
        actual = actual->sigEnFila;
    }

    // si se pasa de la columa c entonces no existe y salimos
    if (actual == nullptr || actual->columna != c) return; 

    // si no se pasa entonces tenemos dos opciones, que este al inicio o en el medio

    // reasignamos la cabezera al siguiente de la fila
    if (antFila == nullptr) cabecerasFilas[f] = actual->sigEnFila;

    // utilizamos el antFila para apuntar al siguiente actual
    else antFila->sigEnFila = actual->sigEnFila;

    // como ya verificamos que existe la celda a eliminar, 
    // analogmente a la busqueda en la fila. lo hacemos en las columnas, cuando lo encontramos
    //hacemos la reasignacion correspondiente , luego eliminamos la celda.



    // auxilires para el recorrido
    Celda* actualCol = cabecerasColumnas[c];
    Celda* antCol = nullptr;

    // bucle para el recorrido, para llegar al f porque ya existe
    while (actualCol != nullptr && actualCol->fila < f) {
        antCol = actualCol;
        actualCol = actualCol->sigEnColumna;
    }

    // si esta al inicio de la columna se hace la reasignacion de cabeceraColumna
    if (antCol == nullptr) cabecerasColumnas[c] = actual->sigEnColumna;

    //si esta en el medio reasignas los punteros con la ayuda del antCol
    else antCol->sigEnColumna = actual->sigEnColumna;

    //una vez conectado, lo eliminas
    delete actual; 
}

void HojaCalculo::printing(){


    for (auto s : cabecerasFilas) {
        if (s != nullptr) { // Solo imprimimos si la fila tiene datos
            while (s != nullptr) {
                cout << "[F:" << s->fila << " C:" << s->columna << " V:" << s->valor << "] ";
                s = s->sigEnFila;
            }
            cout << endl;
        }
    }

}