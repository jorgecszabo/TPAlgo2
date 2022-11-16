#include "Juego.h"
using namespace std;

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
    int jugador = _turno;
    _puntaje[jugador] = _puntaje[jugador] + puntosGanados(o, _tablero, _variante);
}



//Auxiliares de Ubicar

Nat Juego::puntosGanados(const Ocurrencia &o, Tablero t, Variante* v){
    if (o.empty()) {
        return 0;
    }else{
        if (esHorizontal(o)){
            return sumarHorizontal(o) + sumarTodasVerticales(o);
        }else{
            return sumarVertical(o) + sumarTodasHorizontales(o);
        }
    }
}

bool Juego::esHorizontal(const Ocurrencia &o){
    if(o.size() == 1 || get<1>(o.begin()) == get<1>(o.end())){
        return true;
        //acá en el pseudocodigo comparábamos el siguiente del iterador con el siguiente de avanzar(it),
        //como estábamos comparando para ver si es horizontal me pareció lo mismo?
    }else{
        return false;
    }
}

Nat Juego::sumarHorizontal(const Ocurrencia &o, Tablero t, Variante* v){
    int res = 0;

    Ocurrencia::iterator it = o.begin();
    int col = get<0>(it);
    int fila = get<1>(it);
    while(col < t.tamano() && hayLetra(col,fila)){
        res = res + v.puntajeLetra(t.letra(col,fila));
        col++;
    }

    col = get<0>(it) - 1;
    while(0 < col && hayLetra(col,fila)){
        res = res + v.puntajeLetra(t.letra(col,fila));
        col--;
    }
}

Nat Juego::sumarVertical(const Ocurrencia &o, Tablero t, Variante *v) {
    int res = 0;

    Ocurrencia::iterator it = o.begin();
    int col = get<0>(it);
    int fila = get<1>(it);

    while(fila < t.tamano() && hayLetra(col,fila)){
        res = res + v.puntajeLetra(t.letra(col,fila));
        col++;
    }

    fila = get<1>(it) - 1;
    while(0 < fila && hayLetra(col,fila)){
        res = res + v.puntajeLetra(t.letra(col,fila));
        fila--;
    }
    return res;
}

Nat Juego::sumarTodasHorizontales(const Ocurrencia &o, Tablero t, Variante* v){
    int res = 0;
    int col;
    int fila;

    for(x : o){
        col = get<0>(x);
        fila = get<1>(x);
        while(col < t.tamano() && hayLetra(col,fila)){
            res = res + v.puntajeLetra(t.letra(col,fila));
            col++;
        }

        col = get<0>(x) - 1;
        while(0 < col && hayLetra(col,fila)){
            res = res + v.puntajeLetra(t.letra(col,fila));
            col--;
        }

    }
}


Nat Juego::sumarTodasVerticales(const Ocurrencia &o, Tablero t, Variante* v){
    int res = 0;
    int col;
    int fila;

    for(x : o){
        col = get<0>(x);
        fila = get<1>(x);
        while(fila < t.tamano() && hayLetra(col,fila)){
            res = res + v.puntajeLetra(t.letra(col,fila));
            fila++;
        }

        fila = get<1>(x) - 1;
        while(0 < fila && hayLetra(col,fila)){
            res = res + v.puntajeLetra(t.letra(col,fila));
            fila--;
        }

    }
}
//



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


bool Juego::hayLetra(Nat x, Nat y){
    return _tablero.hayLetra(x,y);
}

Letra Juego::letra(Nat i, Nat j){
    return _tablero.letra(i,j);
}

Nat Juego::puntaje(IdCliente id){
    return _puntaje[id];
}

Nat Juego::cantFicha(IdCliente id, Letra l){
    return _fichasxJugador[id][ord(l)];
}

Nat Juego::cantJugadores(){
    return _fichasxJugador.size();
}

Tablero Juego::tablero(){
    return _tablero;
}

Repositorio Juego::repositorio(){
    return _repositorio;
}