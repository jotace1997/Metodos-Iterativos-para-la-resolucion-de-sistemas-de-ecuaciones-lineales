#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <fstream>  /*! Para sobrecargar los operadores >> <<*/
#include <vector>   /*! Clase vector de la STL, los datos se guardan de forma secuencial*/
#include <math.h>   /*! abs() para el método NormaInfinito*/
#include <string>   /*! Para leer las líneas en >>*/
#include <assert.h> /*! Para comprobar errores*/    

using namespace std;

/**
 * @file array.h
 * @brief Archivo de cabecera de la clase Array
 * Vector abstracto para datos grande. Esta clase 
 * se usa para almacenar los vectores de datos(long double)
 * para poder manipularlos más facil. 
 * @author Juan Carlos Sánchez Cara
 * @date 20/11/20
*/
class Array
{
    private:
        vector <long double> datos; /*!< Vector secuencial de la STL para guardar datos */
    
    public:
        /**
         * No hacenada ya que de la reserva de memoria se encarga la biblioteca <vector>
         * @brief Contructor por defecto         
          @verbatim
           int main()
           {
               Array v;
           }
          @endverbatim
         */
        Array();

        /**
         * No hacenada ya que de la liberación de memoria se encarga la biblioteca <vector>
         * @brief Destructor         
         */
        ~Array();

        /** 
         * Reserva un vector de tamaño n.
         * @brief Constructor por parámetros.
         * @param n argumento entero.     
          @verbatim
           int main()
           {
               int n;
               Array v;
          
               cout << "Tamaño del vector:";
               cin >> n;
          
               v= Array(n);
           }
          @endverbatim   
         */
        Array(const int n);

        /**
         * Reserva un vector de tamaño n e inicializa todas las celdas a f
         * @brief Constructor por parametros
         * @param n argumento entero
         * @param f argumento long double
          @verbatim
           int main()
           {
               int n;
               long double l;
               Array v;
          
               cout << "Tamaño del vector: ";
               cin >> n;
               cout << "Valor de inicialización: ";
               cin >> l;
          
               v= Array(n, l);
           }
          @endverbatim          
         */
        Array(const int n, const long double f);

        /**
         * Convierte un vector <long double> en un Array
         * @brief Constructor por parametros
         * @param Un vector constante de la STL pasado por referencia
          @verbatim
           int main()
           {
               vector <long double> auxiliar;
               Array v;
               
               //Trabajamos con el vector auxiliar...
          
               v= Array(auxiliar);
           }
          @endverbatim 
         */
        Array(const vector <long double> &v);

        /**
         * Crea un Array exactamente igual que el pasado por parametro
         * @brief Constructor de copia
         * @param v Array constante pasado por referencia
          @verbatim
           int main()
           {
               Array a, b;
               
               //Trabajamos con a...
          
               b= Array(a);
           }
          @endverbatim          
         */
        Array(const Array &v);
        
        /**
         * Iguala un Array a otro (this= v)
         * @brief Operador de igualdad
         * @param v Array constante pasado por referencia
         * @return Un Array exactamente igual que el pasado por parametro
          @verbatim
           int main()
           {
               Array a, b;
               
               cin >> a;
          
               b= a;
           }
          @endverbatim           
         */
        Array& operator=(const Array &v);

        /** 
         * El método comprueba que ambos Array tengan el mismo tamaño y
         * crea otro Array del mismo tamaño con la suma componente a componente de cada Array
         * @brief Operador Suma.
         * @param v Array constante pasado por referencia
         * @return Un Array con la suma de ambos vectores elemento a elemento.
          @verbatim
           int main()
           {
               Array a, b, c;
               
               cin >> a;
               cin >> b;
               
               c= a + b;
           }
          @endverbatim            
         */
        Array  operator+(const Array &v);

        /** 
         * El método comprueba que ambos Array tengan el mismo tamaño y
         * crea otro Array del mismo tamaño con la resta componente a componente de cada Array
         * @brief Operador Resta.
         * @param v Array constante pasado por referencia
         * @return Un Array con la resta de ambos vectores elemento a elemento.
          @verbatim
           int main()
           {
               Array a, b, c;
               
               cin >> a;
               cin >> b;
               
               c= a - b;
           }
          @endverbatim           
         */
        Array  operator-(const Array &v);

        /** 
         * El método comprueba que ambos Array tengan el mismo tamaño y
         * crea otro Array del mismo tamaño con el producto componente a componente de cada Array.
         * @brief Operador Producto.
         * @param v Array constante pasado por referencia.
         * @return Un Array con la suma de ambos vectores elemento a elemento.
          @verbatim
           int main()
           {
               Array a, b, c;
               
               cin >> a;
               cin >> b;
               
               c= a*b;
           }
          @endverbatim                    
         */
        Array  operator*(const Array &v);

        /** 
         * El método comprueba que ambos Array tengan el mismo tamaño y
         * que cada componente sea igual.
         * @brief Operador Comparación.
         * @param v Array constante pasado por referencia.
         * @return TRUE si ambos Array son iguales, FALSE en otro caso.
          @verbatim
           int main()
           {
               Array a, b;
               
               cin >> a;
               cin >> b;
               
               if(a==b)
                   cout << "Los dos Arrays son iguales." << endl;
               else
                   cout << "Son distintos." << endl;
           }
          @endverbatim           
         */
        bool operator==(const Array &v);

        /** 
         * @brief Operador de Indexacion Constante.
         * @param i Entero para indexar el vector.
         * @return El valor correspondiente a i para variables constantes.
          @verbatim
           int main()
           {
               Array a;
               int n;
              
               cout << "Tamaño: "
               cin >> n;
               
               a= Array(n);
          
               for(int i=0; i<n; i++)
                   cin >> a[i];
           }
          @endverbatim 
         */
        long double operator[](int i) const;

        /** 
         * @brief Operador de Indexacion.
         * @param i Entero para indexar el vector.
         * @return El valor correspondiente a i para variables constantes.
          @verbatim
           int main()
           {
               Array a;
               int n;
               
               cout << "Tamaño: "
               cin >> n;
               
               a= Array(n);
          
               for(int i=0; i<n; i++)
                   cin >> a[i];
          
               for(int i=0; i<n; i++)
                   cout << a[i] << " ";
           }
          @endverbatim 
         */
        long double& operator[](int i);

        /** 
         * @brief Get Tamaño.
         * @return Devuelve el tamaño del vector.
          @verbatim
           int main()
           {
               Array a;
               int n;
               
               cin >> a;
          
               n= a.Tamanio();
          
               cout << "El array tiene " << n << " elementos" << endl;
           }
          @endverbatim          
         */
        int Tamanio() const;

        /** 
         * @brief Elimina todos los elementos del vector.
          @verbatim
           int main()
           {
               Array a;
               
               cin >> a;
          
               //Trabajo con los datos de a...
          
               a.Limpiar();
          
               //Ahora puedo volver a rellenar el vector con otros datos
          
           }
          @endverbatim    
         */
        void Limpiar();
    
        /** 
         * El método busca el valor absoluto más alto en el vector.
         * @return El valor basoluto (long double) más alto.
          @verbatim
           int main()
           {
               Array a;
               int n;
               
               cin >> a;
          
               cout << "El máximo del vector es: " << a.NormaInfinito() << endl;
           }
          @endverbatim    
         */
        long double NormaInfinito();            

        /** 
         * El método lee una serie de números (1 por línea), los convierte 
         * a long double y los guarda en el mismo orden en el vector datos.
         * @brief Sobrecarga del operador >> (cin).
         * @param entrada Flujo de entrada.
         * @param v Array para guardar los datos.
         * @return Flujo de entrada.
          @verbatim
           int main(int argc, char **argv[])
           {
               Array a;
               ifstream datosMatriz;
          
               datosMatriz.open(argv[1]);
               datosMatriz >> a;
               datosMatriz.close();
           }
          @endverbatim
         */
        friend istream& operator>>(istream &entrada, Array &v);  

        /** 
         * El método escribe una serie de números (1 por línea).
         * @brief Sobrecarga del operador << (cout).
         * @param salida Flujo de salida.
         * @param v Array para obtener los datos.
         * @return Flujo de salida.
          @verbatim
           int main(int argc, char **argv[])
           {
               Array a;
               ifstream datosMatriz;
               ofstream datosSalida;
          
               datosMatriz.open(argv[1]);
               datosMatriz >> a;
               datosMatriz.close();
          
               //Trabajamos con a...
          
               datosSalida.open("solucion.dat");
               datosSalida << a;
               datosSalida.close(); 
           }
          @endverbatim         
         */
        friend ostream& operator<<(ostream &salida, Array &v);   
};
#endif