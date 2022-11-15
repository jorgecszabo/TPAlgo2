#include "Juego.h"

Juego::Juego(Nat k, Variante& v, const Repositorio& r) {
    Tablero _tablero(v.tamanoTablero());
    _repositorio = r;
    _turno = 0;
    vector<vector<Nat>> _fichasxJugador(k);
    for (auto fichas: _fichasxJugador) {
        for (int i = 0; i < TAMANIO_ALFABETO; i++)
            fichas.push_back(0);
    }
    _variante = &v;
    vector<int> _puntaje(k);
}

void Juego::ubicar(const Ocurrencia &o) {
    for (tuple<Nat, Nat, Letra> l : o) {
        _tablero.ponerLetra(get<0>(l), get<1>(l), get<2>(l));
    }
    //FALTA CALCULAR PUNTOS!!!
}

IdCliente Juego::turno() {
    return _turno;
}

Variante& Juego::variante() {
    return *_variante;
}

void Juego::colocarFichas(const Ocurrencia &o) {
    for (auto l : o)
        _tablero.ponerLetra(get<0>(l), get<1>(l), get<2>(l));
}

void Juego::quitarFichas(const Ocurrencia &o) {
    for (auto l : o)
        _tablero.quitarLetra(get<0>(l), get<1>(l));
}

bool Juego::esTodaHorizontal(const Ocurrencia &o) {
    Ocurrencia::iterator it = o.begin();
    int actual = get<1>(*it);
    bool res = true;
    while (it != o.end() && res == true) {
        res = get<1>(*it) == actual;
        ++it;
    }
    return res;
}

bool Juego::esTodaVertical(const Ocurrencia &o) {
    Ocurrencia::iterator it = o.begin();
    int actual = get<0>(*it);
    bool res = true;
    while (it != o.end() && res == true) {
        res = get<0>(*it) == actual;
        ++it;
    }
    return res;
}

bool Juego::formaPalabraHorizontal(tuple<Nat, Nat, Letra> o) {
    int col = get<0>(o);
    int fila = get<1>(o);
    list<Letra> palabra;
    while (col < _tablero.tamano() && palabra.size() <= _variante->palabraMasLarga() + 1 && _tablero.hayLetra(col, fila)) {
            palabra.push_back(_tablero.letra(col, fila));
            col++;
    }
    col = get<1>(o);
    col--;
    while (col >= 0 && palabra.size() <= _variante->palabraMasLarga() + 1 && _tablero.hayLetra(col, fila)) {
        palabra.push_front(letra(col, fila));
        col--;
    }
    Palabra res;
    for (Letra l : palabra) {
        res.push_back(l);
    }
    return _variante->palabraLegitima(res);
}

bool Juego::formaPalabraVertical(tuple<Nat, Nat, Letra> o) {
    int col = get<0>(o);
    int fila = get<1>(o);
    list<Letra> palabra;
    while (fila < _tablero.tamano() && palabra.size() <= _variante->palabraMasLarga() + 1 && _tablero.hayLetra(col, fila)) {
        palabra.push_back(_tablero.letra(col, fila));
        fila++;
    }
    col = get<1>(o);
    col--;
    while (fila >= 0 && palabra.size() <= _variante->palabraMasLarga() + 1 && _tablero.hayLetra(col, fila)) {
        palabra.push_front(letra(col, fila));
        fila--;
    }
    Palabra res;
    for (Letra l : palabra) {
        res.push_back(l);
    }
    return _variante->palabraLegitima(res);
}

bool Juego::todasLegitimas(const Ocurrencia &o) {
    Ocurrencia::iterator it = o.begin();
    bool esValida = true;
    if (esTodaHorizontal(o)) {
        while(it != o.end() && esValida) {
            esValida = formaPalabraVertical(*it);
            ++it;
        }
    } else {
        while (it != o.end() && esValida) {
            esValida = formaPalabraHorizontal(*it);
            ++it;
        }
    }
    return esValida;
}

bool Juego::jugadaValida(const Ocurrencia &o, IdCliente cid) {
    if (o.size() == 0 || o.size() > _variante->palabraMasLarga() || cid != _turno)
        return false;
    if (_tablero.celdasLibres(o)) {
        colocarFichas(o);
        bool res = true;
        if (esTodaHorizontal(o)) {
            bool horizontal = formaPalabraHorizontal(*o.begin());
            bool verticales = todasLegitimas(o);
            res = verticales && horizontal;
        } else {
            bool vertical = formaPalabraVertical(*o.begin());
            bool horizontales = todasLegitimas(o);
            res = vertical && horizontales;
        }
        quitarFichas(o);
        return res;
    } else return false;
}

bool hayLetra(Nat x, Nat y);

Letra letra(Nat i, Nat j);

Nat puntaje(IdCliente id);

Nat cantFicha(IdCliente id, Letra l);

Nat cantJugadores();