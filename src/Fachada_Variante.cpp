#include "Fachada_Variante.h"

Fachada_Variante::Fachada_Variante(
        Nat tamanoTab,
        Nat cantFichas,
        const map<Letra, Nat> &puntajes,
        const set<vector<Letra>> &palabrasLegitimas) {
    _palValidas = new string_map(convertirDiccionario(palabrasLegitimas));
    _variante = new Variante(convertirPuntaje(puntajes), tamanoTab, cantFichas, *_palValidas);
}

Fachada_Variante::~Fachada_Variante() {
        delete _variante;
        delete _palValidas;
}

Nat Fachada_Variante::tamanoTablero() const {
    return _variante->tamanoTablero();
}

Nat Fachada_Variante::fichas() const {
    return _variante->fichas();
}

Nat Fachada_Variante::puntajeLetra(Letra l) const {
    return _variante->puntajeLetra(l);
}

bool Fachada_Variante::palabraLegitima(const Palabra& palabra) const {
    return _variante->palabraLegitima(palabra);
}

const Variante& Fachada_Variante::nuestraVariante() const {
    return *_variante;
}
