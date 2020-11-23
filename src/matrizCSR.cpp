#include "../include/matrizCSR.h"

MatrizCSR::MatrizCSR()
{
    filas= 0;
    noNulos= 0;

    valores= Array(noNulos);
    idColumnas= vector<int>(noNulos);
    ptrFilas= vector<int>(filas + 1);
}

MatrizCSR::~MatrizCSR()
{
    filas= -1;
    noNulos= -1;

    valores.Limpiar();
    idColumnas.erase(idColumnas.begin(), idColumnas.end());
    ptrFilas.erase(ptrFilas.begin(), ptrFilas.end());
}

MatrizCSR::MatrizCSR(int f, int nn)
{
    assert(f>0 && nn>0);

    filas= f;
    noNulos= nn;

    valores= Array(noNulos);
    idColumnas.resize(noNulos);
    ptrFilas.resize(filas+1);
}

MatrizCSR::MatrizCSR(const MatrizCSR &m)
{
    filas= m.filas;
    noNulos= m.noNulos;

    valores= m.valores;
    idColumnas= m.idColumnas;
    ptrFilas= m.ptrFilas;
}

MatrizCSR& MatrizCSR::operator=(const MatrizCSR &m)
{
    if(this!=&m)
    {
        filas= m.filas;
        noNulos= m.noNulos;

        valores= m.valores;
        idColumnas= m.idColumnas;
        ptrFilas= m.ptrFilas;
    }

    return *this;
}

Array MatrizCSR::operator*(const Array &v)
{
    assert(v.Tamanio()==this->filas);

    Array mul(v.Tamanio());
    int inicioFila, finFila;
    long double suma;

    for (int i=0; i<this->ptrFilas.size()-1; i++)
    {
        inicioFila= this->ptrFilas[i];
        finFila= this->ptrFilas[i+1];
        suma= 0.0;

        for (int j=inicioFila; j<finFila; j++)
            suma+= this->valores[j]*v[this->idColumnas[j]];
            
        mul[i]= suma;
    }    

    return mul;
}

void MatrizCSR::Precondicionar(const Array &v)
{
    assert(v.Tamanio()==this->filas);
    
    for (int i=0; i<this->ptrFilas.size()-1; i++)
        for (int j=this->ptrFilas[i]; j<this->ptrFilas[i+1]; j++)
            this->valores[j]*= v[this->idColumnas[j]];     
}

Array MatrizCSR::GetNoDiagonal() const
{
    Array d(this->filas);
    bool salir;

    for(int i=0; i<d.Tamanio(); i++)
    {
        salir= false;
        for(int j=this->ptrFilas[i]; j<this->ptrFilas[i + 1] && !salir; j++)
            if(this->idColumnas[j]==i)      
            {
                salir= true;                                            
                d[i]= 1.0/this->valores[j];
            }
    }
    return d;
}

MatrizCSR MatrizCSR::GetDiagonalInvertida() const
{
    MatrizCSR diagonal(this->filas, this->filas);   //Llamo al constructor por parametros dandole cómo entrada el número de filas, columnas y valores noNulos que presenta la diagonal de cualquier matriz con todos los elementos de la diagonal distintos de 0
    bool salir;

    diagonal.ptrFilas[0]= 0;

    for(int i=0; i<diagonal.filas; i++)
    {
        //Al ser una matriz diagonal, las columnas se iran incrementando desde 0 hasta filas-1
        diagonal.idColumnas[i]= i;
        //Al ser una matriz diagonal, sólo hay 1 elemento en cada fila por tanto se incrementa en 1 cada celda del vector
        diagonal.ptrFilas[i+1]= i+1;

        //Recorro la fila actual hasta dar con la celda que corresponde a la diagonal
        salir= false;
        for(int j=this->ptrFilas[i]; j<this->ptrFilas[i + 1] && !salir; j++)
            if(this->idColumnas[j]==i)      //El identificador de columna de cada fila debe coincidir con la fila
            {
                salir= true;                                //Dejamos de seguir buscando
//                diagonal.valores.push_back(1.0/this->valores[j]);  //Al ser la inversa de la diagonal, el dato leido debe ser el inverso
                diagonal.valores[i]= 1.0/this->valores[j];
            }
    }
    return diagonal;
}

istream& operator>>(istream &entrada, MatrizCSR &m)
{
    string linea1, linea2, aux;
    int suma= 0, k= 1, valAux= 1, val;
    bool primeraColumna, primeraLineaUtil;
    int f, c, nn;

    //Nos saltamos las lineas con comentarios al principio del archivo
    primeraLineaUtil= true;
    while(getline(entrada, linea1) && primeraLineaUtil)
    {
        linea2= linea1;
        if(linea1[0]!='%')
            primeraLineaUtil= false;
    }

    //Leemos la primera linea util con el tamaño en filas, columnas y valores no nulos
    aux= "";
    primeraColumna= true;
    for(int i=0; i<linea2.size(); i++)
    {
        if(linea2[i]!=' ')
            aux+= linea2[i];
        else
        {
            if (primeraColumna)
            {
                f= stoi(aux);
                primeraColumna= false;
            }
            else
                c= stoi(aux);                                        

            aux= "";
        }
    }
    nn= stoi(aux);
   
    //Dimensionamos los vectores ahora que sabemos el tamaño e inicializamos la primera posicion del vec. ptrFilas a 0 
    m= MatrizCSR(f, nn);
    k= 0;
    m.ptrFilas[k++]= 0;

    //Leemos las lineas restantes del archivo e inicializamos los vectores
    suma= 0;
    valAux= 1;
    for(int i=0; i<m.noNulos; i++)
    {
        primeraColumna= true;
        aux= "";

        for(int j=0; j<linea1.size(); j++)
        {
            if(linea1[j]!=' ')
                aux+= linea1[j];
            else if(aux!="")
            {
                if (primeraColumna)                                 //Si se cumple, leemos la fila
                {
                    val= stoi(aux);                        //Leemos la posicion en la fila

                    if(valAux!=val)                                 //Si la fila es distinta a la anterior
                        k++;                                        //Incrementamos la posicion del vector ptrFIlas para escribir
                    
                    m.ptrFilas[k]= ++suma;                          //Incrementamos siempre con cada fila que leemos, el valor final de suma es igual a m.noNulos
                    valAux= val;
                    primeraColumna= false;
                }
                else                                                //Si se cumple, leemos la columna
                    m.idColumnas[i]= stoi(aux) - 1;
                        
                aux= "";
            }
        }
        m.valores[i]= stold(aux);                    //Leemos el valor asociado a la fila y columna correspondiente                    

        getline(entrada, linea1);                                   //Saltamos a la siguiente linea del archivo
    }

    return entrada;
}

ostream& operator<<(ostream &salida,  MatrizCSR &m)
{
    int inicio, fin;

    salida << m.filas << " " << m.filas << " " << m.noNulos << endl;

    for(int i=0; i<m.filas+1; i++)
    {
        inicio= m.ptrFilas[i];
        fin= m.ptrFilas[i+1];

        for(int j=inicio; j<fin; j++)
            salida << i << " " << m.idColumnas[j] << " " << m.valores[j] << endl;
    }
    
    return salida;
}
