# Instrucciones para Pruebas de Algoritmos de Ordenamiento y Multiplicación de Matrices

### Notas:
- Los datos en bruto utilizados para generar los gráficos de los algoritmos de ordenamiento están en el archivo `inputGraficos.txt`.
- Para los algoritmos de multiplicación de matrices, los datos están en `matrixTimeStats.txt`.

---

**Compilaciones:**  
Todas las compilaciones deben realizarse con el siguiente comando:

```bash
g++ -O3 [input] -o [output]
```

### Algoritmos de Ordenamiento
Para llevar a cabo las pruebas descritas en el informe, se debe compilar el archivo `multiple.cpp` o `full.cpp` para medir el rendimiento de los algoritmos de ordenamiento.

#### Requisitos previos:
Es **importante** crear las carpetas `datasets` y `outputDataset` si no existen previamente. Luego, debes compilar y usar `datagen.cpp` para generar los datasets en el formato esperado por los algoritmos.

```bash
g++ -O3 datagen.cpp -o datagen
./datagen
```

#### Uso de los archivos:
- `multiple.cpp`: Está diseñado para ejecutar pruebas con un solo dataset a la vez.
- `full.cpp`: Realiza pruebas automáticas recorriendo todos los datasets, luego de seleccionar el algoritmo de ordenamiento deseado.

### Algoritmos de Multiplicación de Matrices
Para las pruebas de multiplicación de matrices, se debe compilar y ejecutar `matrixtest.cpp`.

```bash
g++ -O3 matrixtest.cpp -o matrixtest
./matrixtest
```

---

### Resultados de las Pruebas
Los resultados de rendimiento de cada prueba se almacenan en archivos `.txt`:

- `full.cpp` guarda los tiempos en: `fullTimeStats.txt`.
- `multiple.cpp` guarda los tiempos en: `timeStats.txt`.
- `matrixtest.cpp` guarda los tiempos en: `matrixTimeStats.txt`.

---

### Opcional: Salida de Datos Calculados
Cada script se puede configurar para activar la escritura de los arreglos o matrices calculadas en un archivo de salida.
