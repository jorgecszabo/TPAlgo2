#ifndef TP_JUEGODEPALABRAS_VARIANTE_H
#define TP_JUEGODEPALABRAS_VARIANTE_H

#endif //TP_JUEGODEPALABRAS_VARIANTE_H

#include "Tipos.h"
#include "string_map.h"
#include "Letra.h"
#include <vector>

class Variante {
public:
    /* Constructor */
    Variante(
            vector<Nat> pLetra,
            Nat tamTab,
            Nat cantFichas,
            string_map pLeg);

    /* Retorna el tamano del tablero de la variante    */
    Nat tamanoTablero() const;

    /* Retorna la cantidad de fichas que cada jugador deberia tener en su mano.
     */
    Nat fichas() const;

    /* Retorna el puntaje de la letra l  */
    Nat puntajeLetra(Letra l) const;

    /* Indica si una palabra es legitima o no     */
    bool palabraLegitima(const Palabra& palabra) const;

    /* Retorna la longitud de la palabra mas larga */
    Nat palabraMasLarga();

private:
    Nat _tamanoTab;
    Nat _cantFichas;
    vector<Nat> _puntLetra;
    string_map _legitimas;
};
