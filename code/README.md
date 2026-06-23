# Documentación

## Implementación

### Programa principal

### Scripts

# INF221 - Tarea 2: AniMarathon

## Descripción

Este proyecto resuelve el problema **AniMarathon**, que consiste en seleccionar capítulos de distintos animes con el objetivo de **maximizar la satisfacción total**, respetando restricciones de:

* Tiempo disponible (M)
* Energía disponible (E)

Cada anime permite seleccionar únicamente un **prefijo de capítulos** (no se pueden omitir capítulos intermedios). Además, si se visualiza el anime completo, se obtiene un **bono adicional de satisfacción**.

## Implementación

### Programa principal (`general.cpp`)

El archivo principal se encarga de:

* Leer la entrada desde `stdin`
* Generar las opciones de prefijos para cada anime
* Ejecutar los algoritmos:

  * Fuerza Bruta
  * Greedy 1
  * Greedy 2
  * Programación Dinámica
* Medir:

  * Tiempo de ejecución (ms)
  * Uso de memoria (KB)
* Guardar resultados en:

  * `data/measurements/` (por instancia)
  * `data/measurements/results.txt` (acumulado)
  * `data/outputs/MaxSatisfaccion.txt`

### Scripts (`scripts/`)

#### `plot_generator.py`

Script encargado de:

* Leer `results.txt`
* Calcular promedios por tamaño de entrada (n)
* Generar gráficos:

  * Comparación de tiempos (todos los algoritmos)
  * Comparación sin fuerza bruta
  * Calidad de solución (Greedy vs DP)
  * Uso de memoria

Los gráficos se guardan en:

data/plots/

## Algoritmos implementados

### 1. Fuerza Bruta

* Explora todas las combinaciones posibles
* Garantiza solución óptima
* Complejidad exponencial
* Solo se ejecuta para instancias pequeñas

### 2. Greedy 1

* Selecciona prefijos según el mejor ratio:

  satisfacción / (tiempo + energía)

* Considera todas las opciones globalmente

* Rápido pero no siempre óptimo

### 3. Greedy 2

* Primero elige la mejor opción por anime

* Luego prioriza animes más eficientes

* Más rápido que Greedy 1

* Menor calidad en algunos casos

### 4. Programación Dinámica

* Enfoque tipo mochila con doble restricción
* Garantiza solución óptima
* Complejidad pseudo-polinomial

## Compilación y Ejecución

Para compilar y ejecutar el proyecto:

make

## Estructura del proyecto

code/implementation/
├── algorithms/
│   ├── brute-force.cpp
│   ├── greedy1.cpp
│   ├── greedy2.cpp
│   └── dynamic-programming.cpp
├── general.cpp
├── makefile
├── data/
│   ├── inputs/          # Casos de prueba
│   ├── outputs/         # Máxima satisfacción por instancia
│   ├── measurements/    # Resultados individuales + results.txt
│   └── plots/           # Gráficos generados
└── scripts/
    └── plot_generator.py

## Resultados experimentales

* Se ejecutan múltiples instancias por cada tamaño n
* Se promedian los tiempos de ejecución
* Se analiza:

  * Escalabilidad
  * Calidad de solución
  * Uso de memoria

## Notas

* Fuerza Bruta se omite para n grandes (n > 25)
* Programación Dinámica entrega siempre el óptimo
* Greedy es mucho más rápido, pero puede fallar en calidad
* Los gráficos permiten visualizar claramente estas diferencias

## Autor
Martin Vicente Mella Chávez
202373529-9