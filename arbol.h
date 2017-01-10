#pragma once
#include <queue>
#include "nodo.h"
#include "DNI.h"

typedef struct
{
    nodo<TDATO>* nd;
    int nivel;
}NODO_T;

template<class TDATO>
class Arbol{
    
    private:
        int num_niveles;
        int num_nodos;
        nodo<TDATO>* raiz;
        void podar(nodo<TDATO>* &nd);
        //nodo<TDATO>* get_raiz(void);
        //bool eshoja(nodo<TDATO>* nd);
        nodo<TDATO>* buscarRama(nodo<TDATO>* nd, TDATO x);
        void imprimirArbol(nodo<TDATO>* nd);
        void eliminarRama(nodo<TDATO>* &nd, TDATO clave_dada, bool &decrece);
        void sustituye(nodo<TDATO>* &eliminado_, nodo<TDATO>* &sust, bool &decrece);
        bool si_vacio(void);
        
        //Métodos de Rotación
        void rotacion_II(nodo<TDATO>* &nd);
        void rotacion_DD(nodo<TDATO>* &nd);
        void rotacion_ID(nodo<TDATO>* &nd);
        void rotacion_DI(nodo<TDATO>* &nd);
        
        //Inserción
        void inserta_bal(nodo<TDATO>* &nd, nodo<TDATO>* nuevo, bool &crece);
        void insert_re_balancea_izquierda(nodo<TDATO>* &nd, bool &crece);
        void insert_re_balancea_derecha(nodo<TDATO>* &nd, bool &crece);

        //Eliminación
        void eliminar_re_balancea_izquierda(nodo<TDATO>* &nd, bool &decrece);
        void eliminar_re_balancea_derecha(nodo<TDATO>* &nd, bool &decrece);
        
    public:
        Arbol();
        ~Arbol();
        //int get_niveles(void);
        
        void insertar(TDATO d);
        
        void eliminar(TDATO clave_dada);
        
        //BUSCANDO
        nodo<TDATO>* buscar(TDATO x);
        
        //Imprimiendo arbol
        void imprimir(void);
};

template <class TDATO>
nodo<TDATO>* Arbol<TDATO>::buscar(TDATO x)
{
    return buscarRama(raiz, x);
}

template <class TDATO>
nodo<TDATO>* Arbol<TDATO>::buscarRama(nodo<TDATO>* nd, TDATO x)
{
    if(nd == NULL)
        return NULL;
    if(x == nd->dato)
        return nd;
    if(x < nd->dato)
        return  buscarRama(nd->izq, x);
    return buscarRama(nd->der, x);
}



/*template <class TDATO>
nodo<TDATO>* Arbol<TDATO>::get_raiz(void)
{
    //cout << "Valor:" << raiz->dato << endl;
    return raiz;
}*/


template <class TDATO>
Arbol<TDATO>::Arbol()
{
    num_nodos = 0;
    num_niveles = 0;
    raiz = NULL;
    //raiz->der = NULL;
    //raiz->izq = NULL;
}

template <class TDATO>
Arbol<TDATO>::~Arbol()
{
    podar(raiz);
}

template <class TDATO>
bool Arbol<TDATO>::si_vacio(void)
{
    return raiz == NULL;
}

template <class TDATO>
void Arbol<TDATO>::insertar(TDATO d)
{
    nodo<TDATO>* nuevo = new nodo<TDATO>(d, 0);
    bool crece = false;
    inserta_bal(raiz, nuevo, crece);
}

template <class TDATO>
void Arbol<TDATO>::inserta_bal(nodo<TDATO>* &nd, nodo<TDATO>* nuevo, bool &crece)
{
    if(nd == NULL)
    {
        nd = nuevo;
        crece = true;
    }
    else
    {
        if(nuevo->dato < nd->dato)
        {
            inserta_bal(nd->izq, nuevo, crece);
            if(crece)
                insert_re_balancea_izquierda(nd, crece);
        }
        else
        {
            inserta_bal(nd->der, nuevo, crece);
            if(crece)
                insert_re_balancea_derecha(nd, crece);
        }
    }
}


template <class TDATO>
void Arbol<TDATO>::insert_re_balancea_izquierda(nodo<TDATO>* &nd, bool &crece)
{
    switch(nd->balanceo)
    {
        case -1:
        {
            nd->balanceo = 0;
            crece = false;
            break;
        }
        case 0:
        {
            nd->balanceo = 1;
            break;
        }
        case 1:
        {
            nodo<TDATO>* nodo1 = nd->izq;
            if(nodo1->balanceo == 1)
                rotacion_II(nd);
            else
                rotacion_ID(nd);
            crece = false;
            break;
        }
    }
}

template <class TDATO>
void Arbol<TDATO>::insert_re_balancea_derecha(nodo<TDATO>* &nd, bool &crece)
{
    switch(nd->balanceo)
    {
        case 1:
        {
            nd->balanceo = 0;
            crece = false;
            break;
        }
        case 0:
        {
            nd->balanceo = -1;
            break;
        }
        case -1:
        {
            nodo<TDATO>* nodo1 = nd->der;
            if(nodo1->balanceo == -1)
                rotacion_DD(nd);
            else
                rotacion_DI(nd);
            crece = false;
            break;
        }
    }
}


/*template <class TDATO>
int Arbol<TDATO>::get_niveles(void)
{
    return num_niveles;
}


*/
template <class TDATO>
void Arbol<TDATO>::podar(nodo<TDATO>* &nd)
{
    if(nd == NULL) return;
    podar(nd->izq);
    podar(nd->der);
    delete nd;
    nd = NULL;
}

/*template <class TDATO>
bool Arbol<TDATO>::eshoja(nodo<TDATO>* nd)
{
    return !nd->der && !nd->izq;
}*/

template <class TDATO>
void Arbol<TDATO>::eliminar(TDATO clave_dada)
{
    bool decrece = false;
    eliminarRama(raiz,clave_dada,decrece);
}

template <class TDATO>
void Arbol<TDATO>::sustituye(nodo<TDATO>* &eliminado_, nodo<TDATO>* &sust, bool &decrece)
{
    if(sust->der != NULL)
    {
        sustituye(eliminado_, sust->der, decrece);
        if(decrece)
            eliminar_re_balancea_derecha(sust, decrece);   
    }
    else
    {
        //eliminado_->Info = sust->Info;
        eliminado_->dato = sust->dato;
        eliminado_ = sust;
        sust = sust->izq;
        decrece = true;
    }
}

template <class TDATO>
void Arbol<TDATO>::eliminar_re_balancea_izquierda(nodo<TDATO>* &nd, bool &decrece)
{
    switch(nd->balanceo)
    {
        case -1: 
        {
            nodo<TDATO>* nodo1 = nd->der;
            if(nodo1->balanceo > 0)
                rotacion_DI(nd);
            else
            {
                if(nodo1->balanceo == 0)
                    decrece = false;
                rotacion_DD(nd);
            }
            break;
        }
        
        case 0:
        {
            nd->balanceo = -1;
            decrece = false;
            break;
        }
        
        case 1:
        {
            nd->balanceo = 0;
            break;
        }
    }
}

template <class TDATO>
void Arbol<TDATO>::eliminar_re_balancea_derecha(nodo<TDATO>* &nd, bool &decrece)
{
    switch(nd->balanceo)
    {
        case 1: 
        {
            nodo<TDATO>* nodo1 = nd->izq;
            if(nodo1->balanceo < 0)
                rotacion_ID(nd);
            else
            {
                if(nodo1->balanceo == 0)
                    decrece = false;
                rotacion_II(nd);
            }
            break;
        }
        
        case 0:
        {
            nd->balanceo = 1;
            decrece = false;
            break;
        }
        
        case -1:
        {
            nd->balanceo = 0;
            break;
        }
    }
}

template <class TDATO>
void Arbol<TDATO>::eliminarRama(nodo<TDATO>* &nd, TDATO clave_dada, bool &decrece)
{
    if(nd == NULL)
        return ;
    if(clave_dada < nd->dato)
    {
        eliminarRama(nd->izq, clave_dada, decrece);
        if(decrece)
            eliminar_re_balancea_izquierda(nd, decrece);
    }
    else
    {
        if(clave_dada > nd->dato)
        {
            eliminarRama(nd->der, clave_dada, decrece);
            if(decrece)
                eliminar_re_balancea_derecha(nd, decrece);
        }
        else
        {
            nodo<TDATO>* eliminado = nd;
            if(nd->izq == NULL)
            {
                nd = nd->der;
                decrece = true;
            }
            else
            {
                if(nd->der == NULL)
                {
                    nd = nd->izq;
                    decrece = true;
                }
                else
                {
                    sustituye(eliminado, nd->izq, decrece);
                    if(decrece)
                        eliminar_re_balancea_izquierda(nd, decrece);
                }
            }
            
            delete eliminado;
        }
    }
}


template <class TDATO>
void Arbol<TDATO>::imprimir(void)
{
    cout << "Imprimiendo arbol:" << endl;
    if(si_vacio())
    {
        cout << "Arbol vacio" << endl;
    }
    else
    {
        //cout << "Arbol no vacio" << endl;
        imprimirArbol(raiz);
    }
    cout << endl;
}


template <class TDATO>
void Arbol<TDATO>::imprimirArbol(nodo<TDATO>* nd)
{
    cout << "Numero de nodos del arbol:" << num_nodos << endl;
    queue<NODO_T> Q;
    
    
    NODO_T raiz_;

    int nivel = 0;
    int nivel_actual = 0;
    bool final = false;
    NODO_T nodo_actual;
    
    raiz_.nd = raiz;
    raiz_.nivel = 0;
    Q.push(raiz_);
    cout << "Nivel " << nivel_actual << ":\t";
    while(!Q.empty())
    {
        //nodo_actual.nd = NULL;
        //nodo_actual.nivel = 0;
        
        nodo_actual = Q.front();
        Q.pop();

        if(nodo_actual.nivel > nivel_actual)
        {
            //cout << "Nivel del nodo actual:" << nodo_actual.nivel << ", Nivel actual:" << nivel_actual << endl;
            /*if(comprobar_cola(Q))
            {
                final = false;
            }
            else
            {
                final = true;
            }*/
            //cout << "Comprobar cola:" << comprobar_cola(Q) << ", final:" << final << endl;
            nivel_actual = nodo_actual.nivel;   
            cout << endl;
            cout << "Nivel " << nivel_actual << ":\t"; 
        }
        
        if(nodo_actual.nd != NULL)
        {
            //cout << "Entro1" << endl;
            //Hago la impresion del nodo actual
            cout << (nodo_actual.nd)->dato << "\t";
            
            //Inserto nuevos valores en la cola
            //if(final == false)
            //{
                NODO_T hijo_izquierdo;
                NODO_T hijo_derecho;
                
                if((nodo_actual.nd)->izq != NULL)
                {
                    hijo_izquierdo.nd = (nodo_actual.nd)->izq;
                }
                else
                {
                    hijo_izquierdo.nd = NULL;
                }
                if((nodo_actual.nd)->der != NULL)
                {
                    hijo_derecho.nd = (nodo_actual.nd)->der;
                }
                else
                {
                    hijo_derecho.nd = NULL;
                }   
                
                hijo_izquierdo.nivel = nivel_actual+1;
                hijo_derecho.nivel = nivel_actual+1;
                Q.push(hijo_izquierdo);
                Q.push(hijo_derecho);
        }
        else
        {
            //Subárbol vacío
            cout << "[.]" << "\t";
        }
    }
}

template <class TDATO>
void Arbol<TDATO>::rotacion_II(nodo<TDATO>* &nd)
{
    nodo<TDATO>* nodo1 = nd->izq;
    nd->izq = nodo1->der;
    nodo1->der = nd;
    if(nodo1->balanceo == 1)
    {
        nd->balanceo = 0;
        nodo1->balanceo = 0;
    }
    else
    {
        nd->balanceo = 1;
        nodo1->balanceo = -1;
    }
    nd = nodo1;
}

template <class TDATO>
void Arbol<TDATO>::rotacion_DD(nodo<TDATO>* &nd)
{
    nodo<TDATO>* nodo1 = nd->der;
    nd->der = nodo1->izq;
    nodo1->izq = nd;
    if(nodo1->balanceo == -1)
    {
        nd->balanceo = 0;
        nodo1->balanceo = 0;
    }
    else
    {
        nd->balanceo = -1;
        nodo1->balanceo = 1;
    }
    nd = nodo1;
}

template <class TDATO>
void Arbol<TDATO>::rotacion_DI(nodo<TDATO>* &nd)
{
    nodo<TDATO>* nodo1 = nd->der;
    nodo<TDATO>* nodo2 = nodo1->izq;
    nd->der = nodo2->izq;
    nodo2->izq = nd;
    nodo1->izq = nodo2->der;
    nodo2->der = nodo1;
    if(nodo2->balanceo == 1)
        nodo1->balanceo = -1;
    else
        nodo1->balanceo = 0;
    if(nodo2->balanceo == -1)
        nd->balanceo = 1;
    else
        nd->balanceo = 0;
    nodo2->balanceo = 0;
    nd = nodo2;
}

template <class TDATO>
void Arbol<TDATO>::rotacion_ID(nodo<TDATO>* &nd)
{
    nodo<TDATO>* nodo1 = nd->izq;
    nodo<TDATO>* nodo2 = nodo1->der;
    nd->izq = nodo2->der;
    nodo2->der = nd;
    nodo1->der = nodo2->izq;
    nodo2->izq = nodo1;
    if(nodo2->balanceo == -1)
        nodo1->balanceo = 1;
    else
        nodo1->balanceo = 0;
    if(nodo2->balanceo == 1)
        nd->balanceo = -1;
    else
        nd->balanceo = 0;
    nodo2->balanceo = 0;
    nd = nodo2;
}