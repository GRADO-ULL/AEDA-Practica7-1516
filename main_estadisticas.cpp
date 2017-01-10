#include<iostream>
#include<stdlib.h>
#include<vector>

#include "DNI.h"
#include "nodo.h"
#include "arbol.h"

using namespace std;



template <class TDATO>
bool comprobar_aleatorios_dni(vector<TDATO> v_aleatorios, int valor)
{
  int contador = 0;
  bool encontrado = false;
  while(contador < v_aleatorios.size() && encontrado != true)
  {
    if(v_aleatorios[contador].get_value() == valor)
    {
      encontrado = true;
    }
    contador++;
  }
  return encontrado;
}

template <class TDATO>
void inicializacion_vector(vector<TDATO> &v, Arbol<TDATO> &arbol_, int tamanio)
{
    v.resize(tamanio);
    for(int i=0;i<tamanio;i++)
    {
        srand(clock());
        int aux = 30000000 + rand()%(80000001-30000000);
        
        while(comprobar_aleatorios_dni(v,aux))
        {
            aux = 30000000 + rand()%(80000001-30000000);
        }
    
        DNI d(aux);
        v[i] = d;
        arbol_.insertar(d);
    }
}

bool comprobar_aleatorios_pruebas(vector<int> v_aleatorios, int valor)
{
  int contador = 0;
  bool encontrado = false;
  while(contador < v_aleatorios.size() && encontrado != true)
  {
    if(v_aleatorios[contador] == valor)
    {
      encontrado = true;
    }
    contador++;
  }
  return encontrado;
}

void generar_aleatorios(vector<int> &v, int limite_inferior, int limite_superior)
{
  for(int i=0;i<v.size();i++)
  {
      srand(clock());
      int aux_p = limite_inferior+rand()%(((limite_superior + 1 ) -1) -limite_inferior);
      while(comprobar_aleatorios_pruebas(v,aux_p))
      {
         aux_p = limite_inferior+rand()%(((limite_superior + 1 ) -1) -limite_inferior);
      }
      v[i] = aux_p;
      /*cout << v[i];
      if(i < v.size()-1)
      {
        cout << ","; 
      }*/
  }
}

int main()
{
    vector<TDATO> muestra; //Vector de tamanio 2N
    vector<int> pruebas_busqueda;
    vector<int> pruebas_insercion;
    
    Arbol<TDATO> a1;
    int numero_nodos = 0;
    int numero_pruebas = 0;
    
    cout << "-----PRACTICA 6. ARBOLES BINARIOS DE BUSQUEDA.-----" << endl;
    cout << "Modo estadistico." << endl;
    cout << "Introduzca numero de nodos[N]:";
    cin >> numero_nodos;
    cout << "Introduzca numero de pruebas[P]:";
    cin >> numero_pruebas;
    inicializacion_vector(muestra,a1, numero_nodos*2);
    cout << "-----------------------------" << endl;

    cout << "Fase de Busqueda." << endl;
    cout << "Genero aleatorios para las pruebas." << endl;
    //cout << "Vector de pruebas de dimension " << numero_pruebas << ": ";
    pruebas_busqueda.resize(numero_pruebas);
    
    generar_aleatorios(pruebas_busqueda,0,numero_nodos);
    
    cout << endl;
    int maximo_busqueda = 0;
    int minimo_busqueda = 100000000;
    double suma_busqueda = 0;
    double media_busqueda = 0;
    
    DNI::comparaciones = 0;
    for(int i=0;i<numero_pruebas;i++)
    {
      a1.buscar(muestra[pruebas_busqueda[i]]);
      
      //cout << "DNI::comparaciones: " << DNI::comparaciones << endl;
      if(maximo_busqueda<DNI::comparaciones)
        maximo_busqueda = DNI::comparaciones;
      
      if(minimo_busqueda>DNI::comparaciones)
        minimo_busqueda = DNI::comparaciones;
      
      suma_busqueda += DNI::comparaciones;
      DNI::comparaciones = 0;
    }
    
    media_busqueda = suma_busqueda / numero_pruebas;
  
    cout << endl;
    cout << "-----------------------------" << endl;
    cout << "Fase de insercion." << endl;
    pruebas_insercion.resize(numero_pruebas);
    
    cout << "Genero aleatorios para las pruebas." << endl;
    //cout << "Vector de pruebas de dimension " << numero_pruebas << ": ";
    
    int maximo_insercion = 0;
    int minimo_insercion = 100000000;
    double suma_insercion = 0;
    double media_insercion = 0;
    
    //Inicializando vector
    generar_aleatorios(pruebas_insercion,numero_nodos,2*numero_nodos);
    
    DNI::comparaciones = 0;
    for(int i=0;i<numero_pruebas;i++)
    {
      a1.buscar(muestra[pruebas_insercion[i]]);
      
      //cout << "DNI::comparaciones: " << DNI::comparaciones << endl;
      if(maximo_insercion<DNI::comparaciones)
        maximo_insercion = DNI::comparaciones;
      
      if(minimo_insercion>DNI::comparaciones)
        minimo_insercion = DNI::comparaciones;
      
      suma_insercion += DNI::comparaciones;
      DNI::comparaciones = 0;
    }
    media_insercion = suma_insercion / numero_pruebas;
    cout << endl;
    cout << "-----------------------------" << endl;
        
    cout << "ESTADISTICAS" << endl;
    cout << "\t\tN\tP\tMinimo\tMedio\tMaximo"<<endl;
    cout << "Busqueda\t"<<numero_nodos<<"\t"<<numero_pruebas<<"\t"<<minimo_busqueda<<"\t"<<media_busqueda<<"\t"<<maximo_busqueda<<endl;
    cout << "Insercion\t"<<numero_nodos<<"\t"<<numero_pruebas<<"\t"<<minimo_insercion<<"\t"<<media_insercion<<"\t"<<maximo_insercion<<endl;

    cout << endl;
    return 0;
}