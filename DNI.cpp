#include "DNI.h"

DNI::DNI(void)
{
    valor = 0;
}

DNI::DNI(int v)
{
    valor = v;
}

DNI::~DNI()
{
    valor = 0;
}

int DNI::get_value(void)
{
    return valor;
}

//Sobrecarga de operadores
bool DNI::operator==(DNI &dni_)
{
    comparaciones++;
    // cout << "Comparaciones: " << comparaciones << endl;

    if(valor == dni_.get_value())
        return true;
    else
        return false;
}

bool DNI::operator<(DNI &dni_)
{
    comparaciones++;
    // cout << "Comparaciones: " << comparaciones << endl;
    if(valor < dni_.get_value())
        return true;
    else
        return false;
}

bool DNI::operator>(DNI &dni_)
{
    comparaciones++;
    // cout << "Comparaciones: " << comparaciones << endl;

    if(valor > dni_.get_value())
        return true;
    else
        return false;
}

bool DNI::operator<=(DNI &dni_)
{
    comparaciones++;
    // cout << "Comparaciones: " << comparaciones << endl;
    if(valor <= dni_.get_value())
        return true;
    else
        return false;
}

bool DNI::operator>=(DNI &dni_)
{
    comparaciones++;
    // cout << "Comparaciones: " << comparaciones << endl;

    if(valor >= dni_.get_value())
        return true;
    else
        return false;
}

//Impresión
ostream& operator<<(ostream &salida,const DNI dni_)
{
    salida << dni_.valor;
    return salida;
}

void DNI::set_value(int valor_)
{
    valor = valor_;    
}

//Lectura
istream& operator >>(istream& sin, DNI& dni_)
{
     int auxiliar = 0;
     sin >> auxiliar;
     dni_.set_value(auxiliar);
     return sin;
}

int DNI::comparaciones = 0;
