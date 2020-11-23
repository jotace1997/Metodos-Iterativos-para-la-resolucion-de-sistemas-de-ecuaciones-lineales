/**
 * @file jacobi.cpp
 * Omitiendo la lectura y escritura de datos, el algoritmo en pocas palabras sería tal que así:\n
 * DO\n 
 * {\n
 *      x1= x0 + noD*(b - A*x0);\n
 *      x0= x1;\n
 * } WHILE(MAXIMO_ABSOLUTO(b - A*x0)>(umbralError*MAXIMO_ABSOLUTO(b)));\n\n
 * 
 * Siendo los datos de entrada:\n
 * MatrizCSR A:= Matriz de coeficientes\n
 * Array b:= vector del lado derecho\n
 * Array x0:= Aproximación inicial\n
 * long double umbralError:= Precisión de la solución que se quiere obtener (del roden de 1e-20)\n\n
 * 
 * Los datos que se calculan:\n
 * MatrizCSR noD:= Matriz con la diagonal de A negada\n
 * Array x1:= Solución del sistema\n\n
 * 
 * Funciones:\n
 * long double MAXIMO_ABSOLUTO(Array):= Devuelve el máximo absoluto de un vector.\n\n
 * @brief Código en C++ que resuelve el algoritmo de Jacobi para sistemas lineales
 * @author Juan Carlos Sánchez Cara
 * @date 20/11/20
*/

#include <iostream>                 /*! Para leer y escribir por pantalla y teclado*/
#include "../include/matrizCSR.h"   /*! Para manipular matrices dispersas en formato CSR*/
#include "../include/array.h"       /*! Para manipular vectores*/
#include <fstream>                  /*! Para leer y escribir en ficheros*/
#include <sys/time.h>               /*! Para calcular el tiempo de ejecución del algoritmo */

using namespace std;

int main(int argc, char **argv)
{
    /**Declaración de datos*/
    MatrizCSR A, noD;              
    Array b, aux, x0, x1, aux1, P;
    long double tolerancia, e;
    bool salir=false, precondicionar=0;
    int iteraciones=0;
    ifstream datosMatriz, datosVector;
    ofstream solucionVector;
    string coeficientes, vectorDerecho, aproximacionInicial;
    struct timeval t0, t1;
    long double tiempo;

    /**Lectura de la matriz de coeficientes*/
    datosMatriz.open(argv[1]);
    datosMatriz >> A;
    datosMatriz.close();

    /**Lectura del vector derecho*/
    datosVector.open(argv[2]);
    datosVector >> b;
    datosVector.close();

    /**Lectura de la aproximación inicial*/
    datosVector.open(argv[3]);
    datosVector >> x0;
    datosVector.close();

    /**Lectura del umbral de error*/
    cout << "Umbral de error: ";
    cin >> e;

    gettimeofday(&t0, NULL);                        /*! Inicio del cronómetro*/      
        noD= A.GetDiagonalInvertida();              /*! Cálculo de la diagonal invertida de la matriz de coeficientes*/
        tolerancia= e*b.NormaInfinito();            /*! Cálculo de la tolerancia para saber cuando parar*/     
        iteraciones= 0;                             /*! Inicialización de las iteraciones a 0*/

        do                                          /*! HACER:*/
        {     
            aux= b - A*x0;                          /*!     Array aux= (Array b) - (MatrizCSR A)*(Array x0) */
            x1= x0 + noD*aux;                       /*!     Array x1= (Array x0) + (MatrizCSR noD)*(Array aux)*/

            if(aux.NormaInfinito()<tolerancia)      /*!     SI el máximo absoluto del Array aux es menor que la tolerancia previamente calculada:*/
                salir= true;                        /*!         salir= true*/
            else                                    /*!     EN CASO CONTRARIO:*/  
                x0= x1;                             /*!         Array x0= Array x1*/
        
            iteraciones++;                          /*!     Incremento las iteraciones en 1*/

            cout << iteraciones << ": " << aux.NormaInfinito() - tolerancia << endl;
        } while (!salir);                           /*! MIENTRAS SALIR= FALSE*/
    gettimeofday(&t1, NULL);                        /*! Fin del cronometro*/

    /**Calculamos el tiempo total en segundos*/
    tiempo = ((t1.tv_sec  - t0.tv_sec)*1000000u + t1.tv_usec - t0.tv_usec)/1.e6;

    /**Creamos un fichero en el que escribimos la solución*/
    solucionVector.open("solucion.dat");
    solucionVector << x1;
    solucionVector.close(); 

    /**Mostramos información de la ejecución del programa por pantalla*/
    cout << "\n\n> METODO DE JACOBI:" << endl;
    cout << "\t> Fichero de datos: " << argv[1] << endl;
    cout << "\t> Umbral de error: " << e << endl;
    cout << "\t> Iteraciones: " << iteraciones << endl;
    cout << "\t> Tiempo: " << tiempo << endl;
}