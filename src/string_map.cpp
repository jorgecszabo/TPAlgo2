#include "string_map.h"

string_map::string_map(int tam){
    _raiz = new Nodo(tam);
    _size = 0;
    _tamAlfabeto = tam;
    _longPalMasLarga = 0;
}

string_map::string_map(const string_map& aCopiar) : string_map(this->_tamAlfabeto) { *this = aCopiar; }

void string_map::borrarNodo(string_map::Nodo * n) {
    if (n != nullptr) {
        const int size = n->siguientes.size();
        for (int i = 0; i < size; i++)
            borrarNodo(n->siguientes[i]);
        delete n;
    }
}

string_map& string_map::operator=(const string_map& d) {
    borrarNodo(_raiz);
   _size = d._size;
   _raiz = copiarNodo(d._raiz);
   _longPalMasLarga = d._longPalMasLarga;
   return *this;
}

void string_map::agregar(const Palabra& palabra) {
    if (palabra.size() > _longPalMasLarga)
        _longPalMasLarga = palabra.size();
    Nodo* actual = _raiz;
    for (int i = 0; i < palabra.size(); i++) {
        if (actual->siguientes[ord(palabra[i])] == nullptr)
            actual->siguientes[ord(palabra[i])] = new Nodo(_tamAlfabeto);
        actual = actual->siguientes[ord(palabra[i])];
    }
    if (actual->finPalabra == false)
        _size++;
    actual->finPalabra = true;
}

string_map::~string_map(){
    borrarNodo(_raiz);
}

bool string_map::pertenece(const Palabra& clave) const{
    Nodo* actual = _raiz;
    int i = 0;
    while (actual != nullptr && i < clave.size()) {
        actual = actual->siguientes[ord(clave[i])];
        i++;
    }
    if (actual != nullptr)
        return actual->finPalabra;
    else return false;
}

int string_map::cantidadHijos(const Nodo* n) const{
    if (n == nullptr)
        return 0;
    else {
        const int size = n->siguientes.size();
        int hijos = 0;
        for (int i = 0; i < size; i++) {
            if (n->siguientes[i] != nullptr)
                hijos++;
        }
        return hijos;
    }
}

int string_map::altura(const string_map::Nodo * n) const {
    if (n == nullptr) {
        return 0;
    } else {
        const int size = n->siguientes.size();
        int maxAltura = 0;
        for (int i = 0; i < size; i++) {
            int alturaActual = 1 + altura(n->siguientes[i]);
            if (alturaActual > maxAltura)
                maxAltura = alturaActual;
        }
        return maxAltura;
    }
}

void string_map::borrar(const Palabra& clave) {
    if (!pertenece(clave))
        return;
    Nodo* actual = _raiz;
    Nodo* anterior = nullptr;
    Nodo* ultimo = nullptr;
    int idx;
    int ultIdx;
    for (int i = 0; i < clave.size(); i++) {
        if (cantidadHijos(actual) > 1 || actual->finPalabra == true) {
            ultimo = actual;
            idx = ord(clave[i]);
        }
        anterior = actual;
        ultIdx = ord(clave[i]);
        actual = actual->siguientes[ord(clave[i])];
    }
    actual->finPalabra = false;
    if (ultimo != nullptr && cantidadHijos(actual) == 0) {
        Nodo* aBorrar = ultimo->siguientes[idx];
        ultimo->siguientes[idx] = nullptr;
        borrarNodo(aBorrar);
    } else if (anterior != nullptr && cantidadHijos(actual) == 0) {
        Nodo* aBorrar = anterior->siguientes[ultIdx];
        anterior->siguientes[ultIdx] = nullptr;
        borrarNodo(aBorrar);
    }
    _size--;
    if (clave.size() == _longPalMasLarga)
        _longPalMasLarga = altura(_raiz);
}

int string_map::cardinal() const{
    return _size;
}

bool string_map::vacio() const{
    return _size == 0;
}

int string_map::palMasLarga() const {
    return _longPalMasLarga;
}
