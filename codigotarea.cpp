/*
 * =====================================================================================
 *
 *       Filename:  codigotarea.cpp
 *
 *    Description:  editando
 *
 *        Version:  1.0
 *        Created:  11/03/2013 05:27:49 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */


// CÃ³digo para el tercer examen parcial de Estructuras de Datos, semestre AD12, elaborado por RMM
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
#define TAM 100  

//ImplementaciÃ³n del nivel fÃ­sico de un ABB
template <class T>
class NodoArbol
{ public:
	T info;
	NodoArbol<T> *izq, *der;
	NodoArbol() { izq = der = NULL; }
	NodoArbol(T dato) { info = dato; izq = der = NULL; }
};

template <class T>
class ABB
{
private:
		NodoArbol<T> *raiz;
public:
		ABB() { raiz = NULL; }
		void inserta (T dato);
		void despliega() { inorden(raiz); }
		int cuenta () { return contar(raiz); }
		int altura () { return niveles(raiz); }
		~ABB() { libera(raiz); }
};

template <class T>
void libera (NodoArbol<T>* raiz)
{
	if (raiz != NULL)
	{ 
		libera(raiz->izq);
		libera(raiz->der);
		delete(raiz);
	}
}

template <class T>
void inorden (NodoArbol<T>* raiz)
{
	if (raiz != NULL)
	{ 
		inorden(raiz->izq);
		cout << raiz->info <<" ";
		inorden(raiz->der);
	}
}

template <class T>
int contar (NodoArbol<T>* raiz)
{
	if (raiz == NULL)
		return 0;
	return(1+contar(raiz->izq)+contar(raiz->der));
}

template <class T>
int niveles (NodoArbol<T>* raiz)
{
	int altizq, altder;
	if (raiz == NULL)
		return 0;
	altizq = niveles(raiz->izq);
	altder = niveles(raiz->der);
	return(1+ (altizq>altder? altizq : altder));
}

template <class T>
void ABB<T>::inserta (T valor)
{
	NodoArbol<T> *NuevoNodo = new NodoArbol<T>(valor);
	NodoArbol<T> *actual = raiz, *anterior = NULL;
	while (actual != NULL)
	{
		anterior=actual;
		actual=(actual->info>valor? actual->izq: actual->der);
	}
	if (anterior==NULL)
		raiz = NuevoNodo;
	else
		if (anterior->info > valor)
			anterior->izq = NuevoNodo;
		else
			anterior->der = NuevoNodo;
}

// ImplementaciÃ³n del nivel fÃ­sico de una Tabla de Hash

template <class T>
class tablaHash
{
private:
	ABB<T> tabla[TAM];
	int cantidad;
	
public:
	tablaHash() {cantidad = 0;}
	void inserta (T dato);
	void despliega ();
};

template <class T>
void tablaHash<T>::inserta (T dato)
{
	int posicion = dato / 100 % TAM;
	tabla[posicion].inserta(dato);
	cantidad++;
}

template <class T>
void tablaHash<T>::despliega()
{
	cout << "Cantidad de datos: "<<cantidad<<"\n";
	for (int i = 0; i < TAM; i++)
	{
		cout << "Posicion "<<i<<": "<<tabla[i].cuenta()<<" datos en "<<tabla[i].altura()<<" niveles ";
		tabla[i].despliega();
		cout << "\n";
	}
}

// ImplementaciÃ³n del programa de aplicaciÃ³n
int main()
{
    tablaHash<int> hashing;
	ifstream arch;
	string nomarch;
	int dato;

	cout << "Ingrese el nombre del archivo a cargar: ";
	cin >> nomarch;

	arch.open(nomarch.c_str());
	while (!arch.eof())
	{
		arch >> dato;
		hashing.inserta(dato);
	}
	arch.close();

	hashing.despliega();	
	

	return 0;
}

