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
    );
    /**
     * Retorna el tamano del tablero de la variante
     */
    Nat tamanoTablero() const;

    /**
     * Retorna la cantidad de fichas que cada jugador deberia tener en su mano.
     */
    Nat fichas() const;

    /**
     * Retorna el puntaje de la letra l
     */
    Nat puntajeLetra(Letra l) const;

    /**
     * Indica si una palabra es legitima o no
     */
    bool palabraLegitima(const Palabra& palabra) const;

    /**
    * Retorna un puntero a la variante que implementamos, usada para que
    * podamos usar nuestra variante en Juego.h
    */
     const Variante& nuestraVariante() const;

private:
    Variante _variante;

    vector<Nat> convertirPuntaje(const map<Letra, Nat>& puntajes) {
        vector<Nat> res(TAMANIO_ALFABETO, 1);
        for (auto e : puntajes) {
            res[ord(e.first)] = e.second;
        }
        return res;
    };
    string_map convertirDiccionario(const set<vector<Letra>>& palabrasLegitimas) {
        string_map palLegitimas = string_map(TAMANIO_ALFABETO);
        for (Palabra p : palabrasLegitimas)
            palLegitimas.agregar(p);
        return palLegitimas;
    };
};


#endif //FACHADA_VARIANTE_H
