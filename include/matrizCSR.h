#ifndef _MATRIZ_CSR_H
#define _MATRIZ_CSR_H

#include <vector>       /*! Clase vector de la STL, los datos se guardan de forma secuencial*/
#include <fstream>      /*! Para sobrecargar los operadores >> <<*/
#include <assert.h>     /*! Para comprobar errores*/
#include "array.h"      /*! Para guardar el vector de valores long double*/

using namespace std;

/**
 * @file matrizCSR.h
 * @brief Archivo de cabecera de la clase MatrizCSR
 * Implementación abstracta de una matriz en formato CSR
 * apta para almacenar matrices dispersas.  
 * @author Juan Carlos Sánchez Cara
 * @date 20/11/20
*/
class MatrizCSR
{
    private:
        int filas;                  /*!< Filas y columnas de la matriz(siempre matrices cuadradas)*/        
        int noNulos;                /*!< Elementos no nulos */

        Array valores;              /*!< Vector de long double de tamaño noNulos que almacena los valores distintos de 0 de la matriz*/
        vector<int> idColumnas;     /*!< Vector de int de tamaño noNulos que almacena las columnas con valores distintos de 0 de la matriz*/ 
        vector<int> ptrFilas;       /*!< Vector de int de tamaño filas+1 que almacena los inicios de cada fila*/

    public:
        /**
         * No hacenada ya que de la reserva de memoria se encarga la biblioteca <vector>
         * @brief Contructor por defecto   
        @verbatim
           int main()
           {
               MatrizCSR m;
           }
        @endverbatim      
         */
        MatrizCSR();                                                    

        /**
         * No hacenada ya que de la liberación de memoria se encarga la biblioteca <vector>
         * @brief Destructor       
         */        
        ~MatrizCSR();                                                   

        /**
         * Reserva memoria para los 3 vectores e iniciliza las variables
         * @brief Contructor por parámetros        
         * @param f Filas;
         * @param nn Elementos no nulos
        @verbatim
           int main()
           {
               int fil, noNulos;
               MatrizCSR m;

               cout << "Filas y elementos no nulos de la matriz: ";
               cin >> fil >> noNulos;

               m= MatrizCSR(fil, noNulos);  //valores.size()= idColumas.size()= noNulos; ptrFilas= fil+1;
           }
        @endverbatim             
         */        
        MatrizCSR(int f, int nn);                                

        /**
         * Crea una MatrizCSR exactamente igual que ls pasada por parametro
         * @brief Contructor de copia
         * @param m MatrizCSR constante pasada por referencia         
        @verbatim
           int main()
           {
               MatrizCSR a, b;

               cin >> a;

               b= MatrizCSR(a);
           }
        @endverbatim             
         */        
        MatrizCSR(const MatrizCSR &m);                                        

        /**
         * Iguala una MatrizCSR a otra (this= m)
         * @brief Operador de igualdad
         * @param m MatrizCSR constante pasada por referencia
         * @return Una MatrizCSR exactamente igual que la pasada por parametro
        @verbatim
           int main()
           {
               MatrizCSR a, b;

               cin >> a;

               b= a;
           }
        @endverbatim 
         */        
        MatrizCSR& operator=(const MatrizCSR &m);                       

        /**
         * Método más importante de todos, el método crea un Array del mismo tamaño que v y mediante un bucle
         * desde 0 hasta this->ptrFilas.size()-1 lo va rellenando, cada iteración de este bucle corresponde a
         * una fila de la matriz, por tanto, en cada iteración de este bucle se multiplica el valor correspondiente
         * del Array con toda la fila, se suman estos valores y se introducen en el vector resultado. Para ello,
         * se declaran dos variables, inicio y fin, inicio valdrá this->ptrFilas[i] y fin this->ptrFilas[i+1] 
         * (i es el iterador del primer bucle) ahora ya tenemos el inicio y final de fila por tanto, creamos otro 
         * bucle que recorra el vector valores desde inicio hasta fin que sume todos los productos del valor correspondiente
         * del vector con los valores de la fila en cuestión y cuando acabe, escribimos la suma en el vector resultado.
         * @brief Producto Matriz-Vector.
         * @param v Array constante pasado por referencia.
         * @return Un Array resultado de la multiplicación de la matriz por el vector.   
        @verbatim
           int main()
           {
               MatrizCSR m;
               Array v, mul;

               cin >> m;
               cin >> v

               mul= m*v;

               cout << "m*v= " << mul << endl;
           }
        @endverbatim      
         */        
        Array operator*(const Array &v);                           

        /**
         * @brief Tamaño de la matriz       
         * @return Devuelve el número de filas (o columnas, da igual ya que la matriz es cuadrada) de la matriz
        @verbatim
           int main()
           {
               MatrizCSR a;

               cin >> a;

               cout << "La matriz a tiene " << a.GetFilas() << " filas" << endl;
           }
        @endverbatim 
         */        
        int GetFilas() const;                     
        
        /**
         * Dos bucles anidados que recorren la matriz por filas y cuando coincidan el indice de fila y columna
         * escribir el valor correspondiente invertido en el vector.
         * @brief Por cuestiones de eficiencia, para algunas cosas, es bueno tener la diagonal en un vector  
         * @return Devuelve la diagonal negada en forma de Array  
        @verbatim
           int main()
           {
                MatrizCSR a;
                Array noD;

                cin >> a;

                noD= a.GetNoDiagonal();
           }
        @endverbatim      
         */
        Array GetNoDiagonal() const;  

        /**
         * Creamos una matriz en la que las filas coinciden con los elementos no nulos.
         * @brief Inversa de la matriz 
         * @return Devuelve una MatrizCSR con la inversa de la diagonal de la matriz.
        @verbatim
           int main()
           {
                MatrizCSR a, noD;
                MatrizCSR b;

                cin >> a;
                noD= a.GetDiagonalInvertida();

                b= noD*a;   //La diagonal de b son todos 1
           }
        @endverbatim       
         */                                       
        MatrizCSR GetDiagonalInvertida() const;                        

        /**
         * El método recorre la matriz y multiplica todos los valores de la misma fila con el valor
         * correspondiente del vector (el vector es la inversa de esta matriz).
         * @brief Precondiciona la matriz para conseguir una convergencia más rápida.
         * @param v El vector que "multiplicará" la matriz         
        @verbatim
           int main()
           {
                MatrizCSR a;
                Array P;

                cin >> a;

                P= a.GetNoDiagonal();

                a.Precondicionar(P);

                cout << a; //La diagonal de a son todos 1
           }
        @endverbatim
         */        
        void Precondicionar(const Array &v);               

        /** 
         * El método lee matrices en formato matrix market de un fichero y las convierte en formato CSR.
         * Para ello, lee las dimensiones de la matriz en la primera línea y seguidamente reserva memoria para
         * los 3 vectores. Luego lee linea a linea el archivo, cada línea se compone de 3 valores:
         * fila columna valor
         * Mientras no cambie la fila se incrementa un contador para saber cuantos valores hay en la fila y 
         * la columna y el valor se escriben en los vectores correspondientes en el mismo orden en el que se leen,
         * cuando el valor de la fila cambia, se escribe el valor que haya en el contador en el vector prtFilas y se 
         * vuelve a inicializar el contador a 0.
         * @brief Sobrecarga del operador >> (cin).
         * @param entrada Flujo de entrada.
         * @param m MatrizCSR para guardar los datos.
         * @return Flujo de entrada.
        @verbatim
           int main(int argc, char **argv[])
           {
                MatrizCSR a;
                ifstream datosMatriz;

                datosMatriz.open(argv[1]);      //Path del fichero con los datos de la matriz en matrix market
                datosMatriz >> A;
                datosMatriz.close();
           }
        @endverbatim
         */      
        friend istream& operator>>(istream &entrada, MatrizCSR &m); 

        /** 
         * Hace lo contrario que el operador >> convierte una matriz CSR en una matriz en formato matrix market
         * @brief Sobrecarga del operador << (cout).
         * @param salida Flujo de salida.
         * @param m MatrizCSR para obtener los datos.
         * @return Flujo de salida.
        @verbatim
           int main(int argc, char **argv[])
           {
                MatrizCSR a;
                ifstream datosMatriz;
                ofstream solucionMatriz;

                datosMatriz.open(argv[1]);     
                datosMatriz >> A;
                datosMatriz.close();

                //Trabajar con A

                solucionMatriz.open("solucion.dat");    //Nombre que le hemos dado al fichero
                solucionMatriz << A;
                solucionMatriz.close();
           }
        @endverbatim
         */  
        friend ostream& operator<<(ostream &salida,  MatrizCSR &m);
};
#endif
