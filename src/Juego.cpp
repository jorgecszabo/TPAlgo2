#include "Juego.h"

Juego(Nat k, const Variante& v, const Repositorio& r) {
    _tablero = Tablero(tamanoTablero(v));
    
}

void ubicar(const Ocurrencia& o);

IdCliente turno();

const Variante& variante();

bool validarJugada(const Ocurrencia& o, IdCliente cid);

bool hayLetra(Nat x, Nat y);

Letra letra(Nat i, Nat j);

Nat puntaje(IdCliente id);

Nat cantFicha(IdCliente id, Letra l);

Nat cantJugadores();