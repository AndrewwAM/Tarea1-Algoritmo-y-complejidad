<!>  Todas las compilaciones son llevadas a cabo con g++ -O3 [input] -o [output]

Para llevar a cabo las pruebas efectuadas en el informe se debe compilar el archivo "multiple.cpp" o "full.cpp" para hacer mediciones de los algoritmos de ordenamiento
    
<!> IMPORTANTE <!>
Crear las carpetas "datasets" y "outputDataset" en caso de que no existan previamente,
compilar y utilizar "datagen.cpp" para generar los datasets en el formato que recibe este código 

"multiple.cpp" está pensado para hacer pruebas con un dataset a la vez.
"full.cpp" realiza mediciones a través de cada uno de los datasets luego de seleccionar el algoritmo deseado.

En el apartado de matrices se debe compilar "matrixtest.cpp".

Los resultados de rendimiento de cada prueba son guardados en archivos .txt
full.cpp ----------> fullTimeStats.txt
multiple.cpp ------> timeStats.txt
matrixtest.cpp ----> matrixTimeStats.txt

Se puede configurar cada script para activar la escritura en un archivo de salida de los arreglos o matrices calculados.