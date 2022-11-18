#include "Juego.h"
using namespace std;

Juego::Juego(Nat k, const Fachada_Variante v, const Repositorio& r): _variante(v), _tablero(Tablero (v.tamanoTablero())) {
    _repositorio = r;
    _turno = 0;
    vector<vector<Nat>> fichasXJugador(k);
    for (auto fichas: fichasXJugador) {
        for (int i = 0; i < TAMANIO_ALFABETO; i++)
            fichas.push_back(0);
    }
    _fichasxJugador = fichasXJugador;
    _puntaje = vector<Nat>(k, 0); 
}

void Juego::ubicar(const Ocurrencia &o) {
    for (tuple<Nat, Nat, Letra> l : o) {
        _tablero.ponerLetra(get<0>(l), get<1>(l), get<2>(l));
    }
    int jugador = _turno;
    _puntaje[jugador] = _puntaje[jugador] + puntosGanados(o);
    _turno = (_turno+1)%(_puntaje.size());
}



//Auxiliares de Ubicar

Nat Juego::puntosGanados(const Ocurrencia &o){
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
    if(o.size() == 1 || get<1>(*o.begin()) == get<1>(*o.end())){
        return true;
        //acá en el pseudocodigo comparábamos el siguiente del iterador con el siguiente de avanzar(it),
        //como estábamos comparando para ver si es horizontal me pareció lo mismo?
    }else{
        return false;
    }
}

Nat Juego::sumarHorizontal(const Ocurrencia &o){
    int res = 0;

    Ocurrencia::iterator it = o.begin();
    int col = get<0>(*it);
    int fila = get<1>(*it);
    while(col < _tablero.tamano() && hayLetra(col,fila)){
        res = res + _variante.puntajeLetra(_tablero.letra(col,fila));
        col++;
    }

    col = get<0>(*it) - 1;
    while(0 < col && hayLetra(col,fila)){
        res = res + _variante.puntajeLetra(_tablero.letra(col,fila));
        col--;
    }
    return res;
}

Nat Juego::sumarVertical(const Ocurrencia &o) {
    int res = 0;

    Ocurrencia::iterator it = o.begin();
    int col = get<0>(*it);
    int fila = get<1>(*it);

    while(fila < _tablero.tamano() && hayLetra(col,fila)){
        res = res + _variante.puntajeLetra(_tablero.letra(col,fila));
        col++;
    }

    fila = get<1>(*it) - 1;
    while(0 < fila && hayLetra(col,fila)){
        res = res + _variante.puntajeLetra(_tablero.letra(col,fila));
        fila--;
    }
    return res;
}

Nat Juego::sumarTodasHorizontales(const Ocurrencia &o){
    int res = 0;
    int col;
    int fila;

    for(auto x : o){
        col = get<0>(x);
        fila = get<1>(x);
        while(col < _tablero.tamano() && hayLetra(col,fila)){
            res = res + _variante.puntajeLetra(_tablero.letra(col,fila));
            col++;
        }

        col = get<0>(x) - 1;
        while(0 < col && hayLetra(col,fila)){
            res = res + _variante.puntajeLetra(_tablero.letra(col,fila));
            col--;
        }
    }
    return res;
}


Nat Juego::sumarTodasVerticales(const Ocurrencia &o){
    int res = 0;
    int col;
    int fila;

    for(auto x : o){
        col = get<0>(x);
        fila = get<1>(x);
        while(fila < _tablero.tamano() && hayLetra(col,fila)){
            res = res + _variante.puntajeLetra(_tablero.letra(col,fila));
            fila++;
        }

        fila = get<1>(x) - 1;
        while(0 < fila && hayLetra(col,fila)){
            res = res + _variante.puntajeLetra(_tablero.letra(col,fila));
            fila--;
        }
    }
    return res;
}

IdCliente Juego::turno() {
    return _turno;
}

const Fachada_Variante& Juego::variante() {
    return _variante;
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
    int fila = get<1>(*it);
    bool res = true;
    while (it != o.end() && res) {
        res = get<1>(*it) == fila;
        ++it;
    }
    if(res){
        int minCol = colMin(o);
        int maxCol = colMax(o);
        while(minCol<maxCol  &&  res){
            res = _tablero.hayLetra(minCol, fila);
            minCol++;
        }
    }
    return res;
}

bool Juego::esTodaVertical(const Ocurrencia &o) {
    Ocurrencia::iterator it = o.begin();
    int col = get<0>(*it);
    bool res = true;
    while (it != o.end() && res) {
        res = get<0>(*it) == col;
        ++it;
    }
    if(res){
        int minFila = filaMin(o);
        int maxFila = filaMax(o);
        while(minFila<maxFila  &&  res){
            res = _tablero.hayLetra(minFila, col);
            minFila++;
        }
    }
    return res;
}

int Juego::colMin(const Ocurrencia &o){
    int min = get<0>(*o.begin());
    for(auto e : o){
        if(get<0>(e) < min){
            min = get<0>(e);
        }
    }
    return min;
}
int Juego::colMax(const Ocurrencia &o){
    int max = get<0>(*o.begin());
    for(auto e : o){
        if(get<0>(e) > max){
            max = get<0>(e);
        }
    }
    return max;
}
int Juego::filaMin(const Ocurrencia &o){
    int min = get<1>(*o.begin());
    for(auto e : o){
        if(get<1>(e) < min){
            min = get<1>(e);
        }
    }
    return min;
}
int Juego::filaMax(const Ocurrencia &o){
    int max = get<1>(*o.begin());
    for(auto e : o){
        if(get<1>(e) > max){
            max = get<1>(e);
        }
    }
    return max;
}

bool Juego::formaPalabraHorizontal(tuple<Nat, Nat, Letra> o) {
    int col = get<0>(o);
    int fila = get<1>(o);
    list<Letra> palabra;
    while (col < _tablero.tamano() && palabra.size() <= _variante.palabraMasLarga() + 1 && _tablero.hayLetra(col, fila)) {
            palabra.push_back(_tablero.letra(col, fila));
            col++;
    }
    col = get<1>(o);
    col--;
    while (col >= 0 && palabra.size() <= _variante.palabraMasLarga() + 1 && _tablero.hayLetra(col, fila)) {
        palabra.push_front(letra(col, fila));
        col--;
    }
    Palabra res;
    for (Letra l : palabra) {
        res.push_back(l);
    }
    return _variante.palabraLegitima(res);
}

bool Juego::formaPalabraVertical(tuple<Nat, Nat, Letra> o) {
    int col = get<0>(o);
    int fila = get<1>(o);
    list<Letra> palabra;
    while (fila < _tablero.tamano() && palabra.size() <= _variante.palabraMasLarga() + 1 && _tablero.hayLetra(col, fila)) {
        palabra.push_back(_tablero.letra(col, fila));
        fila++;
    }
    col = get<1>(o);
    col--;
    while (fila >= 0 && palabra.size() <= _variante.palabraMasLarga() + 1 && _tablero.hayLetra(col, fila)) {
        palabra.push_front(letra(col, fila));
        fila--;
    }
    Palabra res;
    for (Letra l : palabra) {
        res.push_back(l);
    }
    return _variante.palabraLegitima(res);
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
    if (o.size() == 0 || o.size() > _variante.palabraMasLarga() || cid != _turno)
        return false;
    if (_tablero.celdasLibres(o)) {
        colocarFichas(o);
        bool res = true;
        if (esTodaHorizontal(o)) {
            bool horizontal = formaPalabraHorizontal(*o.begin());
            bool verticales = todasLegitimas(o);
            res = verticales && horizontal;
        } else if (esTodaVertical(o)){
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
