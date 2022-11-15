#ifndef TP_JUEGODEPALABRAS_TABLERO_H
#define TP_JUEGODEPALABRAS_TABLERO_H

#include "vector"
#include "Letra.h"
#include "Tipos.h"

class Tablero {
    public:
    //Crea nuevo Tablero.
    Tablero(int);
    //Crea nuevo Tablero vacío.
    Tablero();
    //Devuelve el tamaño del tablero.
    Nat tamano();

    //Afirma si hay o no una letra en la posicion <i,j>.
    bool hayLetra(int, int);

    //Dada una posicion <i,j> del tablero t, ubica la letra l en dicha posición, asumiendo que se encentra libre.
    void ponerLetra(int, int, Letra);

    //Asumiendo que hay una letra en la posicion <i,j>, la devuelve.
    Letra letra(int, int);

    /* Dada una posicion <i,j> del tablero t, elimina la letra que se encuentra en dicha posición,
     * asumiendo que había una en un principio. */
    void quitarLetra(int, int);

    //Afirma si todas las celdas a las que hace referencia una ocurrencia o están libres o no en el tablero t.
    bool celdasLibres(const Ocurrencia&);

    private:
    vector<vector<tuple<bool, Letra>>> _tablero;

};

#endif //TP_JUEGODEPALABRAS_TABLERO_H
