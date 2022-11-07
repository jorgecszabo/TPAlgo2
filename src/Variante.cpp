#include "Variante.h"



Variante::Variante(vector<Nat> p, Nat t, Nat f, string_map pl) : _puntLetra(p), _tamanoTab(t), _cantFichas(f), _legitimas(pl) {
}

Nat Variante::tamanoTablero() const {
    return _tamanoTab;
}

Nat Variante::fichas() const {
    return _cantFichas;
}

Nat Variante::puntajeLetra(Letra l) const {
    return _puntLetra[ord(l)];
}

bool Variante::palabraLegitima(const Palabra &palabra) const {
    return _legitimas.pertenece(palabra);
}

Nat Variante::palabraMasLarga() {
    return palMasLarga(_legitimas);
}


