cmake_minimum_required(VERSION 3.16)

project(ArbolB_Dual_System VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Habilitar herramientas automáticas de Qt6
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Encontrar el paquete gráfico
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# =================================================================
# COMPILACIÓN 1: EJECUTABLE DE CONSOLA (Menú original)
# =================================================================
# Incluye main_consola.cpp y Aleatorio.cpp (los archivos .cpp nativos)
add_executable(ArbolB_Consola main_consola.cpp Aleatorio.cpp)

# =================================================================
# COMPILACIÓN 2: EJECUTABLE GRÁFICO (Interfaz Qt)
# =================================================================
add_executable(ArbolB_Grafico
    main_gui.cpp
    MainWindow.cpp
    MainWindow.hpp
    VistaZoom.hpp
)
target_link_libraries(ArbolB_Grafico PRIVATE Qt6::Widgets)

