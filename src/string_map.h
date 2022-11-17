#ifndef STRING_MAP_H_
#define STRING_MAP_H_

#include <string>
#include <vector>
#include "Tipos.h"
#include "Letra.h"

using namespace std;

class string_map {
public:
    /**
    CONSTRUCTOR
    * Construye un conjunto vacio dado el tamaño del alfabeto. Para caracteres ASCII usar 256.
    **/
    string_map(int tam);

    /**
    CONSTRUCTOR POR COPIA
    * Construye un conjunto por copia.
    **/
    string_map(const string_map& aCopiar);

    /**
    OPERADOR ASIGNACION
     */
    string_map& operator=(const string_map& d);

    /**
    DESTRUCTOR
    **/
    ~string_map();

    /**
    AGREGAR
    * Inserta una palabra al conjunto
    **/
    void agregar(const Palabra&);

    /**
    PERTENECE
    * Sirve para identificar si una palabra pertenece al conjunto.
    **/

    bool pertenece(const Palabra &key) const;

    /**
    BORRAR
    * Dada un elemento del conjunto, lo borra.
    --PRODUCE ALIASING--
    **/
    void borrar(const Palabra& key);

    /**
     CARDINAL
     * Devuelve cantidad de claves definidas */
    int cardinal() const;

    /**
     VACIO?
     * devuelve true si no hay ningún elemento en el diccionario */
    bool vacio() const;

    /**
    PALMASLARGA
    * devuelve el tamaño de la palabra definida mas larga */
    int palMasLarga() const;
private:
    struct Nodo {
        vector<Nodo*> siguientes;
        bool finPalabra;
        Nodo(int tam) : siguientes(tam, nullptr), finPalabra(false) {}
    };

    Nodo* _raiz;
    int _size;
    int _tamAlfabeto;
    int _longPalMasLarga;
    int cantidadHijos(const Nodo*) const;
    void borrarNodo(Nodo*);
    int altura(const Nodo*) const;
    bool noHayNadaAbajo(Nodo*) const;
    Nodo* copiarNodo(Nodo* n) {
        if (n == nullptr)
            return nullptr;
        else {
            const int size = n->siguientes.size();
            Nodo* nuevo = new Nodo(size);
            for (int i = 0; i < size; i++) {
                nuevo->siguientes[i] = copiarNodo(n->siguientes[i]);
            }
            nuevo->finPalabra = n->finPalabra;
            return nuevo;
        }
    }
};

#endif // STRING_MAP_H_

//
