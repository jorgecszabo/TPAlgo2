#ifndef FACHADA_VARIANTE_H
#define FACHADA_VARIANTE_H

#include "Tipos.h"
#include "Variante.h"
#include "string_map.h"

class Fachada_Variante {
public:
    /**
     * Construye una Fachada_Variante a partir de los parametros de las variantes
     */
    Fachada_Variante(
            Nat tamanoTab,
            Nat cantFichas,
            const map<Letra, Nat>& puntajes,
            const set<vector<Letra>>& palabrasLegitimas
    ) {
        vector<Nat> _puntaje(TAMANIO_ALFABETO, 0);
        for (auto e : puntajes) {
            _puntaje[ord(e.first)] = e.second;
        }
        _palLegitimas = new string_map(TAMANIO_ALFABETO);
        for (Palabra p : palabrasLegitimas)
            _palLegitimas->agregar(p);
        _variante = new Variante(_puntaje, tamanoTab, cantFichas , *_palLegitimas);
    };
    /**
     * Retorna el tamano del tablero de la variante
     */
    Nat tamanoTablero() const {
        return _variante->tamanoTablero();
    };

    /**
     * Retorna la cantidad de fichas que cada jugador deberia tener en su mano.
     */
    Nat fichas() const {
        return _variante->fichas();
        };

    /**
     * Retorna el puntaje de la letra l
     */
    Nat puntajeLetra(Letra l) const {
        return _variante->puntajeLetra(l);
    };

    /**
     * Indica si una palabra es legitima o no
     */
    bool palabraLegitima(const Palabra& palabra) const {
        return _variante->palabraLegitima(palabra);
    };

    /**
    * Retorna un puntero a la variante que implementamos, usada para que
    * podamos usar nuestra variante en Juego.h
    */
     const Variante* nuestraVariante() const {
        return _variante;
     }

private:
    Variante* _variante;
    vector<Nat> _puntaje;
    string_map* _palLegitimas;
};

#endif //FACHADA_VARIANTE_H
