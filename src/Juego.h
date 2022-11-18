#ifndef TP_JUEGODEPALABRAS_JUEGO_H
#define TP_JUEGODEPALABRAS_JUEGO_H

#include "Tablero.h"
#include "Notificacion.h"
#include "Variante.h"
#include <queue>

class Juego {
public:
    /*  Construye un juego a partir de la cantidad de jugadores k, la variante v y el repositorio r  */
    /*  Complejidad: O(tamanoTab**2 + ALPHABET_SIZE*cantJugadores + cantFichas*cantJugadores)  */
    Juego(Nat k, const Variante v, const Repositorio& r);

    /*  Ubica una Ocurrencia o en el juego  */
    /*  Complejidad: O(m)  -   donde m es el numero de fichas que se ubican  */
    void ubicar(const Ocurrencia& o);

    /*  Retorna el id del cliente al cual le toca jugar  */
    /*  Complejidad: O(1)  */
    IdCliente turno();

    /*  Retorna informacion sobre la variante del juego  */
    /*  Complejidad: O(1)  */
    const Variante& variante();

    /*  Determina si una jugada es valida o no  */
    /*  Complejidad: O(Lmax ** 2)  */
    bool jugadaValida(const Ocurrencia& o, IdCliente cid);

    /*  Retorna true sii la coordenada se encuentra ocupada.  */
    /*  Complejidad: O(1)  */
    bool hayLetra(Nat x, Nat y);

    /*  Obtiene el contenido del tablero en una coordenada.  */
    /*  Complejidad: O(1)  */
    Letra letra(Nat i, Nat j);

    /*  Retorna el puntaje del jugador id  */
    /*  Complejidad: O(1 + m*Lmax)
     *   donde m es la cantidad de fichas que ubico el jugador desde la ultima vez que se preguntó por su puntaje.  */
    Nat puntaje(IdCliente id);

    /*  Dado un jugador id y una letra l, retorna cuantas fichas tiene el jugador de dicha letra.  */
    /*  Complejidad: O(1)  */
    Nat cantFicha(IdCliente id, Letra l);

    Nat cantJugadores();

    /* Devuelve el tablero del juego. */
    Tablero tablero();

    Repositorio repositorio();

    void repartirFichas(multiset<Letra> fichas, int cid);
    void quitarFichas(const Ocurrencia& o, int cid);
    const multiset<Letra>& ultimaReposicion(int cid);

private:
    Tablero _tablero;
    vector<vector<Nat>> _fichasxJugador;
    Nat _turno;
    const Variante _variante;
    vector<Nat> _puntaje = {0};
    Repositorio _repositorio;
    Repositorio::const_iterator _it;
    vector<multiset<Letra>> _ultimaReposicion;

    //Auxiliares
    multiset<Letra> fichasAReponer(int cantidad);
    bool tieneFichas(const Ocurrencia &o, int cid);
    void colocarFichas(const Ocurrencia &o);
    void quitarFichas(const Ocurrencia &o);
    bool esTodaHorizontal(const Ocurrencia &o);
    bool esTodaVertical(const Ocurrencia &o);
    bool formaPalabraVertical(tuple<Nat, Nat, Letra> o);
    bool formaPalabraHorizontal(tuple<Nat, Nat, Letra> o);
    bool todasLegitimas(const Ocurrencia &o);

    Nat puntosGanados(const Ocurrencia &o);
    bool esHorizontal(const Ocurrencia &o);
    Nat sumarHorizontal(const Ocurrencia &o);
    Nat sumarVertical(const Ocurrencia &o);
    Nat sumarTodasHorizontales(const Ocurrencia &o);
    Nat sumarTodasVerticales(const Ocurrencia &o);

    int colMin(const Ocurrencia &o);
    int colMax(const Ocurrencia &o);
    int filaMin(const Ocurrencia &o);
    int filaMax(const Ocurrencia &o);
};

#endif //TP_JUEGODEPALABRAS_JUEGO_H
