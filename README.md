# Proyecto Nro. 1: Hoja de Cálculo Simple con Matrices Dispersas

## Integrantes
* John Brandon Quiñones Espinal 
* Ariana Belen Blanco Anicama
* Romina Valeria Muñoz Portugal

---

## 1. Instrucciones de Compilación y Ejecución
Este proyecto fue desarrollado en **C++17** utilizando el framework **Qt** para la interfaz gráfica.

### Requisitos
* Qt Creator instalado.
* Compilador compatible con C++17 (GCC, Clang o MSVC).

### Instalación de Qt
**En Windows:**
1. Dirígete a la página oficial y descarga el **Qt Online Installer** (versión Open Source).
2. Ejecuta el instalador e inicia sesión con tu cuenta de Qt (puedes crear una de forma gratuita).
3. En la selección de componentes, asegúrate de marcar **Qt Creator** y un compilador compatible (por defecto, MinGW viene incluido en las opciones recomendadas de Windows).
4. Sigue los pasos del asistente de instalación hasta finalizar.

**En Linux (Ubuntu/Debian):**
La forma más rápida y directa es a través de la terminal. Ejecuta los siguientes comandos:
1. Actualiza los repositorios: 
   `sudo apt update`
2. Instala las herramientas de compilación base, Qt Creator y las librerías de Qt:
   `sudo apt install build-essential qtcreator qtbase5-dev`
*(Nota: Si utilizas otra distribución como Fedora o Arch Linux, reemplaza `apt` por tu gestor de paquetes correspondiente, como `dnf` o `pacman`).*

### Pasos para compilar y ejecutar
1. Descomprimir el archivo `.zip` del proyecto.
2. Abrir **Qt Creator**.
3. Ir a `Archivo` -> `Abrir archivo o proyecto...` y seleccionar el archivo `proyectoNro1.pro`.
4. Configurar el proyecto seleccionando un Kit válido (Desktop Qt...).
5. Presionar el botón de **Build** (icono de martillo o Ctrl+B) para compilar el código fuente (`.cpp` y `.h`).
6. Presionar el botón de **Run** (icono de play verde o Ctrl+R) para iniciar la aplicación.

### Pasos para compilar y ejecutar
1. Descomprimir el archivo `.zip` del proyecto.
2. Abrir **Qt Creator**.
3. Ir a `Archivo` -> `Abrir archivo o proyecto...` y seleccionar el archivo `proyectoNro1.pro`.
4. Configurar el proyecto seleccionando un Kit válido (Desktop Qt...).
5. Presionar el botón de **Build** (icono de martillo o Ctrl+B) para compilar el código fuente (`.cpp` y `.h`).
6. Presionar el botón de **Run** (icono de play verde o Ctrl+R) para iniciar la aplicación.

---

## 2. Justificación de la Estructura de Datos
*(Nota: A continuación se presenta un resumen de nuestras decisiones de diseño. Para un análisis más exhaustivo, por favor revisar el documento PDF adjunto en la entrega).*

Para este proyecto, optamos por implementar una **lista enlazada cruzada** para la matriz dispersa. Una hoja de cálculo tradicional contiene miles de celdas, de las cuales solo una pequeña fracción almacena información real en un momento dado. Si hubiéramos usado una matriz bidimensional tradicional densa, el programa desperdiciaría una cantidad masiva de memoria y las operaciones básicas serían ineficientes.

Nuestra estructura resuelve estos problemas porque:
* **Optimización estricta de Memoria:** Solo se crean nodos dinámicos para las celdas que realmente tienen contenido. Las celdas vacías no ocupan memoria.
* **Eficiencia Algorítmica:** Insertar o eliminar un nodo tiene un costo temporal de O(k), donde k es el número de elementos existentes en esa fila o columna. Esto es significativamente menor que recorrer una matriz densa, lo cual tendría un costo prohibitivo de O(n * m).

Para lograr esto, cada nodo almacena su fila, columna, valor, y dos punteros (`sigEnFila` y `sigEnColumna`). La estructura se gestiona a través de nodos cabecera para cada fila y columna activa.

---

## 3. Análisis de Complejidad de las Operaciones Clave
* **Consultar / Modificar Celda:** O(k). Se recorren únicamente los nodos ocupados en la fila o columna hasta hallar la coordenada deseada (o determinar que está vacía).
* **Insertar Celda:** O(k). Implica buscar la posición correcta en la fila y columna para enlazar los punteros adecuadamente, saltándose todos los espacios vacíos.
* **Eliminar Celda:** O(k). Se localiza el nodo y se puentean los punteros de los nodos previos en la fila y columna correspondiente.
* **Eliminar Fila / Columna / Rango:** O(p), donde p es la cantidad de nodos ocupados en esa fila, columna o rango. Al ignorar las celdas vacías, la liberación de memoria es directa y altamente eficiente.