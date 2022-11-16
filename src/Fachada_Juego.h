#ifndef FACHADA_JUEGO_H
#define FACHADA_JUEGO_H

#include "Tipos.h"
#include "Fachada_Variante.h"
#include "Juego.h"


class Fachada_Juego {
public:
    /**
     * Construye un juego a partir de la cantidad de jugadores k, la variante v y el repositorio r
     *
     * Complejidad: O(tamanoTab**2 + ALPHABET_SIZE*cantJugadores + cantFichas*cantJugadores)
     */
    Fachada_Juego(Nat k, const Fachada_Variante& v, const Repositorio& r) {
        _juego = new Juego(k, v, r);
    };
    ~Fachada_Juego() { delete _juego; };
    /**
     * Ubica una Ocurrencia o en el juego
     *
     * Complejidad: O(m)
     *   donde m es el numero de fichas que se ubican
     */
    void ubicar(const Ocurrencia& o) {
        _juego->ubicar(o);
    };

    /**
     * Retorna el id del cliente al cual le toca jugar
     *
     * Complejidad: O(1)
     */
    IdCliente turno() {
        _juego->turno();
    };

    /**
     * Retorna informacion sobre la variante del juego
     *
     * Complejidad: O(1)
     */
    const Fachada_Variante& variante() {
        _juego->variante();
    };

    /**
     * Determina si una jugada es valida o no
     *
     * Complejidad: O(Lmax ** 2)
     */
    bool jugadaValida(const Ocurrencia& o) {
        _juego->jugadaValida(o, turno());
    };

    /**
     * Retorna true sii la coordenada se encuentra ocupada.
     *
     * Complejidad: O(1)
     */
    bool hayLetra(Nat x, Nat y) {
        _juego->hayLetra(x,y);
    };

    /**
     * Obtiene el contenido del tablero en una coordenada.
     *
     * Complejidad: O(1)
     */
    Letra letra(Nat i, Nat j) {
        _juego->letra(i,j);
    };

    /**
     * Retorna el puntaje del jugador id
     *
     * Complejidad: O(1 + m*Lmax)
     *   donde m es la cantidad de fichas que ubico el jugador desde la ultima vez que se preguntó por su puntaje.
     */
    Nat puntaje(IdCliente id) {
        _juego->puntaje(id);
    };


    /**
     * Dado un jugador id y una letra l, retorna cuantas fichas tiene el jugador de dicha letra.
     *
     * Complejidad: O(1)
     */
    Nat cantFicha(IdCliente id, Letra l) {
        _juego->cantFicha(id, l);
    };

private:
    Juego* _juego;
};

#endif // FACHADA_JUEGO_H
