# Árbol B

![C++](https://img.shields.io/badge/C++-17-blue.svg)
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

El ejecutable de **consola** no requiere Qt: solo el compilador y CMake. El ejecutable **gráfico** sí requiere tener Qt 6 instalado (solo si se va a compilar desde el código fuente).

## Instrucciones de ejecución

Hay dos formas de usar este programa según lo que necesites:

- **Solo quiero usar el programa** → ve a [Para usuarios (ejecutable listo)](#para-usuarios-ejecutable-listo).
- **Quiero compilarlo desde el código fuente** → ve a [Para desarrolladores (compilar desde el código)](#para-desarrolladores-compilar-desde-el-código).

---

### Para usuarios (ejecutable listo)

Si solo quieres ejecutar el programa sin compilar nada, esta es la forma más sencilla.

#### Windows

1. Descarga el archivo `.zip` de la versión más reciente desde la sección [**Releases**](https://github.com/JASM18/Arbol-B/releases) del repositorio.
2. Descomprime el `.zip` en la carpeta que prefieras.
3. Antes de la primera ejecución, instala el **Visual C++ Redistributable** de Microsoft (solo se necesita una vez por computadora). Es un instalador oficial y gratuito de Microsoft:
   [https://aka.ms/vs/17/release/vc_redist.x64.exe](https://aka.ms/vs/17/release/vc_redist.x64.exe)
4. Abre `ArbolB_Grafico.exe` con doble clic.

> **Importante**: no muevas el `ArbolB_Grafico.exe` fuera de su carpeta. El ejecutable necesita las librerías (`.dll`) y carpetas que vienen junto a él dentro del `.zip`. Si lo sacas solo, no abrirá.

#### Linux

En Linux es necesario tener Qt 6 instalado en el sistema (ver la sección de desarrolladores para el comando de instalación) y compilar desde el código fuente, ya que los binarios pueden variar entre distribuciones.

---

### Para desarrolladores (compilar desde el código)

#### 1. Instalar las dependencias

**En Linux (Arch / CachyOS):**
```bash
sudo pacman -S cmake qt6-base gcc git
```

**En Linux (Debian / Ubuntu):**
```bash
sudo apt install cmake qt6-base-dev g++ git
```

**En Windows:**
1. Instala [Visual Studio](https://visualstudio.microsoft.com/) con la carga de trabajo **"Desarrollo para el escritorio con C++"** (incluye el compilador MSVC y CMake).
2. Instala [Git para Windows](https://git-scm.com/download/win).
3. Instala **Qt 6** con el [instalador oficial](https://www.qt.io/download-qt-installer) (requiere crear una cuenta gratuita). Durante la instalación, en los componentes, asegúrate de seleccionar **MSVC 2022 64-bit** dentro de tu versión de Qt 6. Este componente es necesario para que coincida con el compilador de Visual Studio.

#### 2. Clonar el repositorio

```bash
git clone https://github.com/JASM18/Arbol-B.git
cd Arbol-B
```

#### 3. Compilar

Los comandos de CMake son los mismos en todos los sistemas. La única diferencia es la terminal que se usa:

- **En Linux**: cualquier terminal.
- **En Windows**: usa la **"Developer Command Prompt for VS"** (búscala en el menú de inicio). Es importante usar esta y no el `cmd` normal, porque es la única que tiene CMake y el compilador configurados.

**Configurar el proyecto:**

```bash
cmake -B build
```

> **Nota para Windows**: si CMake no encuentra Qt, indícale dónde está tu instalación con `-DCMAKE_PREFIX_PATH`, ajustando la ruta a tu versión y compilador de Qt:
> ```bash
> cmake -B build -DCMAKE_PREFIX_PATH="C:/Qt/6.11.1/msvc2022_64"
> ```

**Compilar:**

```bash
cmake --build build
```

> Se usa `cmake --build` en lugar de `make` porque funciona igual en cualquier sistema operativo.

Al terminar, los **dos ejecutables** quedan disponibles:

**En Linux:**
```bash
./build/ArbolB_Consola    # versión con menú de texto en la terminal
./build/ArbolB_Grafico    # versión con interfaz gráfica
```

**En Windows** (quedan dentro de una subcarpeta `Debug`):
```bat
.\build\Debug\ArbolB_Consola.exe
.\build\Debug\ArbolB_Grafico.exe
```

#### 4. (Opcional) Generar un paquete distribuible en Windows

Si quieres crear una versión que funcione en cualquier computadora con Windows **sin necesidad de tener Qt ni Visual Studio instalados**, sigue estos pasos:

1. Compila en modo **Release** (más rápido y, a diferencia de Debug, sus librerías sí se pueden distribuir):
   ```bash
   cmake --build build --config Release
   ```
2. Usa la herramienta `windeployqt` de Qt para copiar todas las librerías necesarias junto al ejecutable:
   ```bash
   C:\Qt\6.11.1\msvc2022_64\bin\windeployqt.exe --release build\Release\ArbolB_Grafico.exe
   ```
   (ajusta la ruta de Qt a tu versión).
3. Comprime **toda la carpeta** `build\Release\` en un `.zip`. Ese archivo es el que se puede compartir: cualquier persona podrá descomprimirlo y ejecutar el programa con doble clic (solo necesitará el Visual C++ Redistributable mencionado en la sección de usuarios).

#### Compilar para Code::Blocks

Si prefieres trabajar dentro del IDE Code::Blocks, CMake puede generar un proyecto compatible:

```bash
cmake -B build -G "CodeBlocks - Unix Makefiles"
```

Esto produce un archivo `.cbp` dentro de `build` que se abre directamente en Code::Blocks. En Windows con MinGW, usa el generador `"CodeBlocks - MinGW Makefiles"` en su lugar.

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
