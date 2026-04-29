#include "HojaCalculo.h"



//destructor para evitar fugas de memoria 
HojaCalculo::~HojaCalculo() {
    //recorremos la cantidad de cabezas en fila
    for (int i = 0; i < cabecerasFilas.size(); ++i) {

        //agararmos la cabeza de la fila
        Celda* actual = cabecerasFilas[i];

        //recorremos hasta chocarnos con el nullptr
        while (actual != nullptr) {

            //temporal para borrar despues
            Celda* aBorrar = actual;

            //apuntamos el actual al siguiente
            actual = actual->sigEnFila;

            //borramos la celda y asi sucesivamente hasta borrar todas la celdas
            delete aBorrar;
        }
    }

    //luego, vaciamos las cabezas
    cabecerasFilas.clear();
    cabecerasColumnas.clear();
}


void HojaCalculo::insertarCelda(int f, int c, string valor) {
    if (f < 0 || f >= cabecerasFilas.size() || c < 0 || c >= cabecerasColumnas.size()) {
        
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

//eliminando filas
void HojaCalculo::eliminarFila(int f) {

    // caso de la fila este vacia, salimos
    if (cabecerasFilas[f] == nullptr) return; 

    //agarramos la cabecera de la fila
    Celda* actual = cabecerasFilas[f];

    // hacer el bucle hasta que actual apunte a un null.
    // utiliza temp para ubicar el indice del siguiente
    //eliminas rapido con eliminarCelda, ya que es el primer elemento de la lista
    //asi con todos, todos tienen la primera posicion cuando se eliminan.

    while (actual != nullptr) {

        int colActual = actual->columna;

        Celda* temp = actual->sigEnFila;

        eliminarCelda(f, colActual); 
        actual = temp;
    }
}


// analogamente se eliminan columnas.

void HojaCalculo::eliminarColumna(int c) {

    if (cabecerasColumnas[c] == nullptr) return; 

    Celda* actual = cabecerasColumnas[c];

    while (actual != nullptr) {
        int filaActual = actual->fila;

        Celda* temp = actual->sigEnColumna;
        
        eliminarCelda(filaActual, c); 
        actual = temp;
    }
}


void HojaCalculo::eliminarRango(int fInicio, int cInicio, int fFin, int cFin) {


    // si se pasa hacia atras de la fila 0, lo ponemos en 0
    if (fInicio < 0) fInicio = 0;
    //si se pasa de la capaciad maxima de la fila lo ponemos en la maxima que se puede
    if (fFin >= cabecerasFilas.size()) fFin = cabecerasFilas.size() - 1;

    //recorremos todas las filas en el rango
    for (int i = fInicio; i <= fFin; ++i) {
        // agarramos la cabecera de la fila 
        Celda* actual = cabecerasFilas[i];
        
        // recorremos la fila utilizando un auxiliar para eliminando en el camino
        while (actual != nullptr && actual->columna <= cFin) {
            // guardamos antes de eliminar el actual
            Celda* siguienteEnFila = actual->sigEnFila;
            
            // si esta en el rango dentro del rango de columnas, eliminamos
            if (actual->columna >= cInicio) {
                //eliminamos 
                eliminarCelda(i, actual->columna);
            }
            //seguimos con el siguiente en la fila
            actual = siguienteEnFila;
        }
    }
}


double HojaCalculo::sumaRango(int fInicio, int cInicio, int fFin, int cFin){

    //acumulador de suma
    double suma = 0.0;

    // si se pasa hacia atras de la fila 0, lo ponemos en 0
    if (fInicio < 0) fInicio = 0;
    //si se pasa de la capaciad maxima de la fila lo ponemos en la maxima que se puede
    if (fFin >= cabecerasFilas.size()) fFin = cabecerasFilas.size() - 1;

    //bucle de fila incio hasta el final 
    for(int i = fInicio; i<= fFin; ++i){

        //agarramos la cabeza de la fila
        Celda* actual = cabecerasFilas[i];

        while(actual != nullptr && actual->columna<= cFin){

            if(actual->columna >= cInicio && esNumero(actual->valor)){
                suma+= stod(actual->valor);

            }

            actual = actual->sigEnFila;
        }
    }

    return suma;



}


double HojaCalculo::promedioRango(int fInicio, int cInicio, int fFin, int cFin){

    //acumulador de suma
    double suma = 0.0;

    //ponemos un contador para los validos, la demas logica es igual
    int contador= 0;
    //bucle de fila incio hasta el final 

    // si se pasa hacia atras de la fila 0, lo ponemos en 0
    if (fInicio < 0) fInicio = 0;
    //si se pasa de la capaciad maxima de la fila lo ponemos en la maxima que se puede
    if (fFin >= cabecerasFilas.size()) fFin = cabecerasFilas.size() - 1;


    for(int i = fInicio; i<= fFin; ++i){

        //agarramos la cabeza de la fila
        Celda* actual = cabecerasFilas[i];

        while(actual != nullptr && actual->columna<= cFin){

            //anadirmos la condicional de esNumero para agarrar solo numeros en la suma
            if(actual->columna >= cInicio && esNumero(actual->valor)){

                // convretirmos string a double
                suma+= stod(actual->valor);
                contador++;

            }

            actual = actual->sigEnFila;
        }
    }

    //retornamos

    return (contador ==0) ? 0: (suma/ contador); //para evitar dividir entre 0



}

double HojaCalculo::maximoRango(int fInicio, int cInicio, int fFin, int cFin) {
    double maximo = -numeric_limits<double>::infinity();
    bool encontrado = false;

    // si se pasa hacia atras de la fila 0, lo ponemos en 0
    if (fInicio < 0) fInicio = 0;
    //si se pasa de la capaciad maxima de la fila lo ponemos en la maxima que se puede
    if (fFin >= cabecerasFilas.size()) fFin = cabecerasFilas.size() - 1;


    // bucle para las filas
    for (int i = fInicio; i <= fFin; ++i) {

        //agarramos la cabecera
        Celda* actual = cabecerasFilas[i];
        //bucle para vez que tenga cabeza y sea menor que la columna
        while (actual != nullptr && actual->columna <= cFin) {
            //verificar que sea numero y que sea mayor que la fila inicio

            if (actual->columna >= cInicio && esNumero(actual->valor)) {
                double val = stod(actual->valor);

                //comparamos con el maximo
                if (val > maximo) maximo = val;
                //si existe cambiamos la bandera a encontrado
                encontrado = true;
            }

            //continuas con el del costado hasta que llegue a null y cambies a la otra fila
            actual = actual->sigEnFila;
        }
    }

    // si encuentras un valor entonces devuelves maximo, de lo contrario no hay maximo y devuelves 0
    return encontrado ? maximo : 0; 
}


// analogamente calculamos el minimo, reutilizamos el codigo anteorios y hacemos algunos cambios
double HojaCalculo::minimoRango(int fInicio, int cInicio, int fFin, int cFin) {
 
    
    double minimo = numeric_limits<double>::infinity();
    bool encontrado = false;

    // si se pasa hacia atras de la fila 0, lo ponemos en 0
    if (fInicio < 0) fInicio = 0;
    //si se pasa de la capaciad maxima de la fila lo ponemos en la maxima que se puede
    if (fFin >= cabecerasFilas.size()) fFin = cabecerasFilas.size() - 1;


    // bucle para las filas
    for (int i = fInicio; i <= fFin; ++i) {

        //agarramos la cabecera
        Celda* actual = cabecerasFilas[i];
        //bucle para vez que tenga cabeza y sea menor que la columna
        while (actual != nullptr && actual->columna <= cFin) {
            //verificar que sea numero y que mayor que la fila inicio

            if (actual->columna >= cInicio && esNumero(actual->valor)) {
                double val = stod(actual->valor);

                //comparamos con el minimo
                if (val < minimo) minimo = val;
                //si existe cambiamos la bandera a encontrado
                encontrado = true;
            }

            //continuas con el del costado hasta que llegue a null y cambies a la otra fila
            actual = actual->sigEnFila;
        }
    }

    // si encuentras un valor entonces devuelves minimo, de lo contrario no hay minimo y devuelves 0
    return encontrado ? minimo : 0; 
}







