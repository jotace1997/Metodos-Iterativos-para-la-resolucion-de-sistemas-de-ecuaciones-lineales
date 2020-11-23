#include "../include/array.h"
#include <iostream>
using namespace std;

Array::Array()
{
    datos.resize(0);
}

Array::~Array()
{
    datos.erase(datos.begin(), datos.end());
}

Array::Array(const int n)
{
    datos.resize(n);
}

Array::Array(const int n, const long double f)
{
    datos.assign(n, f);
}

Array::Array(const vector <long double> &v)
{
    datos= v;
}

Array& Array::operator=(const Array &v)
{
    if(this!=&v)
        datos= v.datos;             

    return *this;
}

Array Array::operator+(const Array &v)
{
    assert(this->datos.size()==v.datos.size());

    Array suma(this->datos.size());

    for(int i=0; i<this->datos.size(); i++)
        suma[i]= this->datos[i] + v.datos[i];

    return suma;
}

Array Array::operator-(const Array &v)
{
    assert(this->datos.size()==v.datos.size());

    Array resta(this->datos.size());

    for(int i=0; i<this->datos.size(); i++)
        resta[i]= this->datos[i] - v.datos[i];

    return resta;
}

Array Array::operator*(const Array &v)
{
    assert(this->datos.size()==v.datos.size());

    Array producto(this->datos.size());

    for(int i=0; i<this->datos.size(); i++)
        producto[i]= this->datos[i]*v.datos[i];

    return producto;
}

bool Array::operator==(const Array &v)
{
    assert(this->datos.size()==v.datos.size());

    bool iguales= true;

    for(int i=0; i<this->datos.size() && iguales; i++)
        if(this->datos[i]!=v.datos[i])
            iguales= false;

    return iguales;
}

long double Array::operator[](int i) const
{
    assert(i>=0 && i<this->datos.size());

    return datos[i];
}

long double& Array::operator[](int i)
{
    assert(i>=0 && i<this->datos.size());

    return datos[i];
}

int Array::Tamanio() const
{
    return datos.size();
}

void Array::Limpiar()
{
    datos.erase(datos.begin(), datos.end());
}

long double Array::NormaInfinito()
{
    assert(this->datos.size()>0);

    long double max= abs(datos[0]);

    for(int i=1; i<this->datos.size(); i++)
        if(abs(this->datos[i])>max)
            max= abs(this->datos[i]);

    return max;
}

istream& operator>>(istream &entrada, Array &v)
{
    string linea;
    
    while (getline(entrada, linea))     
        v.datos.push_back(stold(linea));      

    return entrada;
}

ostream& operator<<(ostream &salida, Array &v)
{
    for(int i=0; i<v.datos.size(); i++)
        salida << v.datos[i] << endl;

    return salida;
}