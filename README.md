# Árbol B

![C++](https://img.shields.io/badge/C++-Standard-blue.svg)
![Linux](https://img.shields.io/badge/Linux-Supported-yellow.svg)
![Windows](https://img.shields.io/badge/Windows-Supported-blue.svg)

Implementación de la estructura de datos **Árbol B** en C++ como proyecto universitario. Este tipo de estructura de datos se destaca por la eficiencia a la hora de buscar datos dentro de esta, garantizando tiempos de búsqueda algorítmica de $O(\log_M N)$ donde $M$ es el grado del Árbol B.

El proyecto va más allá de una implementación de consola: a partir del mismo núcleo de la estructura de datos se generan **dos programas independientes**, uno con menú de texto en la terminal y otro con una **interfaz gráfica interactiva** construida con Qt, donde el árbol se dibuja en tiempo real como una simulación.

## Requisitos del sistema

El programa se desarrolló y se hicieron las pruebas correspondientes en el sistema operativo Windows 11 y Linux con la distribución CachyOS. Esto no quiere decir que cualquier otro sistema vaya a fallar, pero no se hicieron pruebas para otros sistemas operativos ni distribuciones.

| Componente | Versión mínima | Para qué se necesita |
|---|---|---|
| Compilador C++ | Compatible con C++17 (GCC, Clang o MSVC) | Compilar todo el proyecto |
| CMake | 3.16 o superior | Automatizar el ensamblado y generar el proyecto |
| Qt | Qt 6 (módulo Widgets) | Únicamente para el ejecutable gráfico |

El ejecutable de **consola** no requiere Qt: solo el compilador y CMake. El ejecutable **gráfico** sí requiere tener Qt 6 instalado.

### Instalación de dependencias en Linux

En distribuciones basadas en Arch (como CachyOS):

```bash
sudo pacman -S cmake qt6-base gcc
```

En distribuciones basadas en Debian/Ubuntu:

```bash
sudo apt install cmake qt6-base-dev g++
```

### Instalación de dependencias en Windows

1. **Compilador y CMake**: instala [Visual Studio](https://visualstudio.microsoft.com/) con la carga de trabajo "Desarrollo para el escritorio con C++" (incluye el compilador MSVC y CMake). Alternativamente, puedes usar [MinGW-w64](https://www.mingw-w64.org/) como compilador y descargar [CMake](https://cmake.org/download/) por separado.
2. **Qt 6**: descarga el instalador oficial desde [qt.io](https://www.qt.io/download-qt-installer) y, durante la instalación, selecciona el módulo **Qt 6 con el compilador que vayas a usar** (por ejemplo, MSVC o MinGW).

## Instrucciones de ejecución

Primero, clona el repositorio (funciona igual en Windows, Linux y macOS):

```bash
git clone https://github.com/JASM18/Arbol-B.git
cd Arbol-B
```

A partir de aquí tienes dos formas de compilar, según tu preferencia.

### Opción A — CMake desde la terminal (multiplataforma)

Estos comandos funcionan en **Windows, Linux y macOS** por igual. La configuración se hace en dos pasos:

```bash
cmake -B build
cmake --build build
```

El primer comando prepara el proyecto en una carpeta `build`; el segundo lo compila. Se usa `cmake --build` en lugar de `make` porque es el comando que funciona en cualquier sistema operativo, sin importar si por debajo se usa Make, Ninja o MSVC.

> **Nota para Windows**: si CMake no encuentra Qt automáticamente, indícale dónde está tu instalación con `-DCMAKE_PREFIX_PATH`, por ejemplo:
> ```bash
> cmake -B build -DCMAKE_PREFIX_PATH="C:/Qt/6.x.x/msvc2022_64"
> ```
> (ajusta la ruta a tu versión y compilador de Qt).

Al terminar, los **dos ejecutables** quedan dentro de la carpeta `build`:

**En Linux/macOS:**
```bash
./build/ArbolB_Consola    # versión con menú de texto en la terminal
./build/ArbolB_Grafico    # versión con interfaz gráfica
```

**En Windows** (los ejecutables llevan extensión `.exe`, y según la configuración pueden quedar en una subcarpeta `Debug` o `Release`):
```bat
.\build\ArbolB_Consola.exe
.\build\ArbolB_Grafico.exe
```

### Opción B — Code::Blocks

Como el `CMakeLists.txt` puede generar un proyecto compatible con Code::Blocks, quienes usen ese IDE pueden trabajar sin tocar la terminal:

```bash
cmake -B build -G "CodeBlocks - Unix Makefiles"
```

Esto produce un archivo `.cbp` dentro de `build` que se abre directamente en Code::Blocks, donde puedes compilar y ejecutar cualquiera de los dos objetivos desde la interfaz del IDE.

> En Windows, si usas Code::Blocks con MinGW, cambia el generador a `-G "CodeBlocks - MinGW Makefiles"`.

## Características principales

El proyecto está pensado como un **sistema dual** que comparte un único núcleo de estructura de datos, separando completamente la lógica del árbol de su presentación (arquitectura Modelo–Vista).

- **Doble objetivo de compilación**: un mismo núcleo (`ArbolB`) alimenta tanto la aplicación de consola como la gráfica, generadas en paralelo por un solo `CMakeLists.txt`.
- **Aplicación gráfica interactiva** construida con Qt, donde el árbol se dibuja en un lienzo 2D y se actualiza tras cada operación.
- **Visualización con layout automático**: el dibujo calcula el espacio que necesita cada subárbol para que las cajas y los punteros no se superpongan, sin importar cuánto crezca el árbol.
- **Zoom y desplazamiento**: la vista permite acercar y alejar con la rueda del mouse, útil para árboles grandes.
- **Búsqueda con resaltado visual**: al buscar una clave, el nodo que la contiene se pinta de un color distinto.
- **Inserción de datos aleatorios** en lote, con cantidad configurable por el usuario.
- **Cambio de grado en tiempo de ejecución**, sin necesidad de cerrar y reabrir el programa.
- **Panel de información** que muestra el grado, la altura y el total de claves del árbol en todo momento.
- **Aplicación de consola** con menú de texto completo, que conserva todas las operaciones de la estructura de datos.

## ¿Qué es un Árbol B?

Un **Árbol B** es un árbol de búsqueda generalizado y autobalanceado, diseñado originalmente para sistemas que almacenan grandes volúmenes de datos en disco. Fue creado por **Rudolf Bayer** y **Edward McCreight** en 1972.

A diferencia de un árbol binario, donde cada nodo guarda una sola clave y tiene a lo más dos hijos, en un Árbol B cada nodo puede contener **múltiples claves** y tener **múltiples hijos**. Esto reduce drásticamente la altura del árbol y, por lo tanto, el número de comparaciones necesarias para encontrar un dato.

### Definición según su grado M

Un Árbol B se define dado un grado $M \geq 3$. A partir de ese grado:

- Cada nodo (excepto la raíz) puede contener entre $\lceil M/2 \rceil$ y $M$ hijos.
- Cada nodo (excepto la raíz) puede contener entre $\lceil M/2 \rceil - 1$ y $M - 1$ claves.
- La raíz puede tener entre 2 y $M$ hijos (entre 1 y $M-1$ claves).
- Si un nodo tiene exactamente $k$ claves, entonces tiene $k + 1$ hijos.

### Propiedades fundamentales

1. Las claves dentro de cada nodo están **ordenadas** de menor a mayor.
2. **Propiedad de búsqueda**: para un nodo con claves $k_1 < k_2 < \dots < k_n$, todas las claves del hijo situado entre $k_i$ y $k_{i+1}$ están en ese rango.
3. **Todas las hojas están al mismo nivel**, lo que garantiza un balance perfecto en altura.
4. Cada nodo se mantiene al menos a la mitad de su capacidad, salvo la raíz.

### Cómo se mantiene balanceado

- **Al insertar**: la clave baja hasta la hoja correspondiente. Si un nodo se desborda (supera $M-1$ claves), se **divide** y la clave del medio sube al padre. El árbol solo **crece en altura** cuando esta división alcanza la raíz.
- **Al eliminar**: si la clave está en un nodo interno, se reemplaza por su sucesor inorden. Si un nodo queda con muy pocas claves (underflow), se repara pidiendo prestada una clave a un hermano o **fusionando** nodos. El árbol solo **decrece en altura** cuando una fusión vacía la raíz.

Esta simetría (crecer y decrecer únicamente desde la raíz) es lo que garantiza que todas las hojas permanezcan siempre al mismo nivel.

## Preview de salidas

### Aplicación de consola

La versión de terminal presenta un menú interactivo y muestra el árbol en formato de texto tras cada operación.

<!-- Sugerencia: agrega aquí una captura del menú de consola -->
<!-- ![Salida de consola](docs/consola.png) -->

```
[30, 60, 90, 120]
    [10, 20]
    [40, 50]
    [70, 80]
    [100, 110]
    [130, 140, 150]
```

### Aplicación gráfica

La versión gráfica dibuja el árbol como una estructura jerárquica navegable, con zoom, búsqueda resaltada y panel de información.

<!-- Sugerencia: agrega aquí una captura de la ventana de la GUI -->
<!-- ![Interfaz gráfica](docs/gui.png) -->

## Conclusiones

Este proyecto comenzó como una implementación académica de la estructura de datos Árbol B y evolucionó hasta convertirse en una aplicación con separación entre la lógica de datos y su presentación, capaz de compilarse en dos formas distintas a partir de un mismo núcleo.

El resultado no solo cumple con las propiedades teóricas de un Árbol B (balance perfecto, búsqueda eficiente y manejo correcto de inserciones y eliminaciones), sino que además ofrece una herramienta visual que permite observar en tiempo real cómo la estructura se reorganiza con cada operación, lo cual resulta especialmente útil para comprender el comportamiento del algoritmo.
