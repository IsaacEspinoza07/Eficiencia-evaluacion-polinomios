# Eficiencia-evaluacion-polinomios
Autor: Isaac Espinoza Hernández

## Descripción del programa.
En este proyecto de C++ se comparan dos metodos distinotas para evaluar polinomios: el método común (o evaluación directa) que consiste en evaluar término por término e ir sumando los valores, y el metodo de Horner el cual evalua el polinomio factorizandolo de una forma especifica para reducir la cantidad de multiplicaciones necesarias.

## Requisitos del sistema
**Sistema operativo:**
- Windows 7 o posterior.
- Linux.
- MacOS.

**Componentes:**
- Procesador Intel o AMD 1 GH.z
- memoria RAM: 512 MB mínimo.
- Espacio disponible: minimo 500 MB.

**Software:**
- Compilador compatible con estándar C++11 o superior.

## Instrucciones de compilación
Descargar el archivo .cpp y colocarlo en una carpeta. Despues, a traves de la terminal dirigirse hasta el directorio donde se encuentre el archivo ```EvaluarPolinomiosTiempo.cpp``` y ejecutar estos comandos:

**Compilar:**
```
g++ EvaluarPolinomiosTiempo.cpp -o EvaluarPolinomiosTiempo
```

**Ejecutar:**
```
.\EvaluarPolinomiosTiempo.exe
```

## Descripcion de los algoritmos
**1.-Evaluacion directa.**
Este método evalúa cada término del polinomio por separado, y se toma mucho tiempo al calcular explícitamente cada potencia.

La forma en la que se ve el polinomio evaluado con este metodo es:

$P(x) = a_n x^n + a_{n-1} x^{n-1} + ... + a_1 x + a_0$


Aqui, cada coeficiente a_i se multiplica por su potencia correspondiente x^i.

**2.-Evaluacion con método de Horner:**
El metodo de Horner reduce la cantidad de multiplicaciones necesarias mediante una reagrupacion muy conveniente del polinomio. El polinomio termina tomando esta forma:


$P(x) = (... ((a_n x + a_{n-1})x + a_{n-2})...)x + a_0$


Al evaluar el polinomio en forma descedente, se realiza una unica multiplicación y suma por paso:

| Grado del Polinomio |                Evaluación Común              |            Método de Horner                 |
|---------------------|----------------------------------------------|---------------------------------------------|
| 10                  | Multiplicaciones: 55<br>Sumas: 10            | Multiplicaciones: 10<br>Sumas: 10           |
| 100                 | Multiplicaciones: 5050<br>Sumas: 100         | Multiplicaciones: 100<br>Sumas: 100         |
| 1000                | Multiplicaciones: 500500<br>Sumas: 1000      | Multiplicaciones: 1000<br>Sumas: 1000       |

En conclusión, el metodo común realiza $frac{n(n-1)}{2}$ multiplicaciones, y $n$ sumas; mientras que el metodo de Horner realiza tantas multiplicaciones y sumas como grado del polinomio, es decir, $n$ multiplicaciones y $n$ sumas.


## Formato de salida
Al terminar de ejecutar el programa se te crearan 3 archivos con los siguientes nombres ```MetodoEvaluacionComun.csv```, ```MetodoEvaluacionHorner.csv``` y ```Promedios.csv```


En los archivos ```MetodoEvaluacion ... .csv``` encontraremos el tiempo de ejecución de el algoritmo correspondiente en nanosegundos. Por columna podemos encontrar el grado del polinomio, partiendo desde grado 10 hasta grado 1000 en saltos de 10 en 10. Tambien encontraremos 1000 renglones por grado ya que se realizan 1000 pruebas para obtener un promedio más preciso.


## Verificación de resultados

![image](https://github.com/user-attachments/assets/a55ce26b-3033-4f58-9763-e7863b8e6f4f)

Como podemos ver, la grafica de la evaluación común podemos ver que tiene una figura geometrica, y esto encaja con que la evaluación común tiene una complejidad $O(n^2)$. Tambien podemos observar que este metodo de evaluación alcanza hasta $1,630,000$ de nanosegundos, lo cual es bastante tiempo.

Por otra parte el metodo de Horner es de orden lineal ($O(n)$), y lo podemos ver claramente en la grafica. Este metodo alcanza (en grado 1000) tiempos de hasta 4,460 nanosegundos, lo cual en comparacion al metodo común hay una gran diferencia y ya podemos saber por que metodo de evaluación optar cuando sea necesario.


