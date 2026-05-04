#include "HojaCalculo.h"


//verificacion de valor de celda es numero
bool HojaCalculo::esNumero(const string& s){

    if (s.empty()) return false;
        int digitos = 0;
        int puntos = 0;

        for (char c : s) {
            if (isspace(c)) continue; // ignoramos espacios y saltos de linea
            if (c == '-' || c == '+') continue; // permitimos signos
            if (c == '.' || c == ',') {
                puntos++;
                continue;
            }
            if (isdigit(c)) {
                digitos++;
                continue;
            }
            // si encuentra alguna letra o simbolo retorna false
            return false;
        }
        // es un numero valido si al menos tiene un digito y a lo mas un punto.
        return (digitos > 0 && puntos <= 1);

}

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

    if (f < 0 || f >= cabecerasFilas.size() || c < 0 || c >= cabecerasColumnas.size()) return "";
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



// traduce el nombre de una celda a enteros filas y columnas, si todo sale bien, devuelve true.
bool HojaCalculo::decodificarReferencia(const string& ref, int& fila, int& columna) {
    
    
    //si esta vacio o no empieza ocn letra es retorna false
    if (ref.empty() || !isalpha(ref[0])) return false;


    
    int i = 0;
    columna = 0;
    

    //convierte el indice de letras consecutivas hasta que encuentre algo que no es letra
    while (i < ref.length() && isalpha(ref[i])) {
        columna = columna * 26 + (toupper(ref[i]) - 'A' + 1);
        i++;
    }
    columna -= 1; // para que sea valido con los indice de la matriz dispersa. 

    // si todos son letras entonces es invalido
    if (i == ref.length()) return false;

    // convierte el resto en un string
    string numPart = ref.substr(i);
    try {
        size_t pos;
        fila = stoi(numPart, &pos) - 1; // si se convierte todo se resta -1

        // si no se convierte todo se retorna false
        if (pos != numPart.length()) return false; // hay basura despues del numero, retorna false
    } catch (...) {
        return false;
    }
    return true;
}




//encargado de ver el valor de una parte de formula. celda o numerico.
double HojaCalculo::evaluarOperando(const string& op, bool& ok) {
    ok = true;

    
    //primer caso: es un numero puro, esa el caso retornamos el valor numerico
    try {
        size_t pos;
        double val = stod(op, &pos);
        if (pos == op.length()) return val; // Es un número válido
    } catch (...) {}

    //segundo caso: es referencia a una celda
    int f, c;

    //si tiene una codificacion de celda, consultamos celda
    if (decodificarReferencia(op, f, c)) {
        string valorCelda = consultarCelda(f, c); // Busca en la matriz

        
        // si valor celda tiene un error , se propaga el error, retorna valor 0 como si fuese una celda vacia o cualqiuer string
        if (valorCelda == "ERROR NAME" || valorCelda == "ERROR DIV") {
            ok = false; return 0;
        }

        // si esta vacia devolvemos cero
        if (valorCelda.empty()) {
            return 0; // ok sigue siendo true 
        }
        

        // accede al valor y lo intenta convertir a su valor numerico, si se peude devuelve el valor 
        //en double, de lo contrario es cualquier otro string y sale de la excepcion
        try {
            size_t pos;
            double val = stod(valorCelda, &pos);
            if (pos == valorCelda.length()) return val;
        } catch (...) {}
    }

    // Si no fue numero ni referencia valida
    ok = false;
    return 0;
}

string HojaCalculo::procesarFormula(string input) {
    
    // si es vacio o el input es diferente de = entonces es texto normal
    if (input.empty() || input[0] != '=') {
        return input;
    }


    // de lo contrario es formula y borramos los espacios en blanco
    string formula = "";
    for (char c : input) {
        if (c != ' ') formula += c;
    }
    formula = formula.substr(1); // Quitamos el '='



    // buscamos el operador de la formula
    size_t posOp = string::npos;
    char operador = '\0';
    for (size_t i = 0; i < formula.length(); i++) {
        if (formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/') {
            if (i > 0) { // ignoramos que el operador se encuentre la inicio para que no se confunda con numero negativo "-5".
                posOp = i;
                operador = formula[i];
                break;
            }
        }
    }

    // lamba limpiador de ceros
    auto limpiarCeros = [](double val) {
        string str = to_string(val);
        str.erase(str.find_last_not_of('0') + 1, std::string::npos);
        if (str.back() == '.') str.pop_back();
        return str;
    };

    // si no existe un operador entonces es una celda o numero, retornamos el valor
    // segun determine la bandera ok.
    if (posOp == string::npos) {
        bool ok;
        double val = evaluarOperando(formula, ok);
        if (!ok) return "ERROR NAME";
        return limpiarCeros(val);
    }

    // si llegamos hasta aca, existe operador, separamos en dos partes, evaluamos los operadores
    //con sus banderas, si alguna bandera fallo se retorna ERROR NAME, de lo contrario se retorna
    // el resutlado de la operacion. en el caso de division entre 0 se retorna ERROR DIV.
    string op1Str = formula.substr(0, posOp);
    string op2Str = formula.substr(posOp + 1);

    bool ok1, ok2;
    double val1 = evaluarOperando(op1Str, ok1);
    double val2 = evaluarOperando(op2Str, ok2);

    
    if (!ok1 || !ok2) return "ERROR NAME";

    
    double resultado = 0;
    
    switch (operador) {
    case '+': resultado = val1 + val2; break;
    case '-': resultado = val1 - val2; break;
    case '*': resultado = val1 * val2; break;
    case '/':
        if (val2 == 0) return "ERROR DIV"; 
        resultado = val1 / val2;
        break;
    }

    return limpiarCeros(resultado);
}




