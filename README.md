# Evaluacion_de_polinomios.
Tarea para la materia de matemáticas discretas en la que se comparan distintas evaluaciones de polinomios.
# Comparación de Métodos para Evaluación de Polinomios

## Descripción
Este proyecto implementa y compara dos métodos diferentes para evaluar polinomios: el método tradicional y el método de Horner. El objetivo es analizar las diferencias de rendimiento entre ambos algoritmos para polinomios de diferentes grados.

## Autor(a)
Miguel Angel Nuñez Holguin-

## Requisitos del sistema
Hardware
Procesador: Intel de doble núcleo
Memoria RAM: 16 GB
Disco duro: 256 GB
Software
Compilador de C++:
Code::Blocks
Sistema Operativo:
Windows 10/11

## Instrucciones de compilación y ejecución
Para compilar el código fuente, ejecuta el siguiente comando en la terminal:
```bash
g++ -std=c++11 -O2 -o evaluador_polinomios main.cpp
```

Para ejecutar el programa:
```bash
./evaluador_polinomios
```

El programa generará automáticamente un archivo CSV con los resultados y mostrará una tabla de comparación en la consola.

## Descripción de los algoritmos

### Método tradicional (estándar)
El método tradicional evalúa un polinomio P(x) = a₀ + a₁x + a₂x² + ... + aₙxⁿ calculando cada término por separado y sumando los resultados. Para cada término aᵢxⁱ, se calcula la potencia xⁱ y se multiplica por el coeficiente aᵢ.

**Complejidad teórica**: O(n²), donde n es el grado del polinomio. Esta complejidad se debe principalmente al cálculo de las potencias de x.

### Método de Horner
El método de Horner reescribe el polinomio como:
P(x) = a₀ + x(a₁ + x(a₂ + ... + x(aₙ)))

Este algoritmo utiliza la factorización del polinomio para reducir el número de operaciones necesarias, evitando el cálculo explícito de potencias.

**Complejidad teórica**: O(n), donde n es el grado del polinomio. El método requiere exactamente n multiplicaciones y n sumas.

## Resultados experimentales y gráfica comparativa

## Análisis de resultados
Los experimentos confirman la diferencia teórica entre ambos métodos:

1. **Eficiencia**: El método de Horner es consistentemente más rápido que el método tradicional para todos los grados de polinomios evaluados.

2. **Escalamiento**: La diferencia de tiempo entre ambos métodos aumenta de forma no lineal con el grado del polinomio. Mientras que el tiempo del método de Horner crece linealmente (O(n)), el tiempo del método tradicional crece cuadráticamente (O(n²)).

3. **Factores de mejora**: Para polinomios de grado alto (>500), el método de Horner puede ser entre 10-100 veces más rápido que el método tradicional, dependiendo del hardware y las optimizaciones del compilador.

4. **Precisión numérica**: Además de ser más eficiente, el método de Horner también tiende a ser más estable numéricamente, ya que minimiza los errores de redondeo al reducir el número total de operaciones aritméticas.

La diferencia observada se corresponde directamente con la complejidad teórica de ambos algoritmos: el método tradicional requiere O(n²) operaciones debido al cálculo de potencias, mientras que el método de Horner solo requiere O(n) operaciones.

## Conclusiones
1. El algoritmo de Horner proporciona una mejora significativa en el rendimiento para la evaluación de polinomios, especialmente cuando aumenta el grado.

2. La implementación en C++ demuestra claramente las ventajas teóricas del método de Horner en la práctica.

3. El uso de técnicas de factorización algebraica, como el método de Horner, puede tener un impacto sustancial en la eficiencia computacional.

4. Este experimento valida la importancia de seleccionar algoritmos óptimos incluso para operaciones matemáticas aparentemente simples.

5. La diferencia de rendimiento se hace más pronunciada a medida que el grado del polinomio aumenta, lo que demuestra la importancia de usar algoritmos eficientes para problemas de mayor escala.

## Documentación del código

El código fuente está organizado en las siguientes clases principales:

- **Polinomio**: Implementa la representación de un polinomio y los dos métodos de evaluación (tradicional y Horner).

- **GeneradorAleatorio**: Proporciona funcionalidad para generar polinomios con coeficientes aleatorios y valores aleatorios para la variable independiente.

- **AnalizadorRendimiento**: Contiene métodos para medir y comparar el rendimiento de los diferentes algoritmos de evaluación.

- **RegistradorResultados**: Gestiona la persistencia de los resultados en un archivo CSV.

La función principal (main) orquesta el proceso completo de pruebas, generando polinomios de diferentes grados (de 10 a 1000), midiendo los tiempos de ejecución para ambos métodos, y presentando los resultados tanto en la consola como en un archivo CSV.
