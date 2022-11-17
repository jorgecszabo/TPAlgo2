#include "Fachada_Variante.h"

Fachada_Variante::Fachada_Variante(
        Nat tamanoTab,
        Nat cantFichas,
        const map<Letra, Nat> &puntajes,
        const set<vector<Letra>> &palabrasLegitimas)  {

    _puntaje = vector<Nat>(TAMANIO_ALFABETO, 0);
    for(int ord = 0; ord < TAMANIO_ALFABETO; ord++) {
        Letra letra = inversaDeOrd(ord);
        if(puntajes.count(letra) == 1){
            const Nat algo = puntajes[letra];
            _puntaje[ord] = algo;
        } else {
            _puntaje[ord] = 1;
        }
    }
    _palLegitimas = new string_map(TAMANIO_ALFABETO);
    for (Palabra p : palabrasLegitimas)
        _palLegitimas->agregar(p);
    _variante = new Variante(_puntaje, tamanoTab, cantFichas , *_palLegitimas);
}

Nat Fachada_Variante::tamanoTablero() const {
    return _variante->tamTablero();
}

Nat Fachada_Variante::fichas() const {
    return _variante->fichas();
}

Nat Fachada_Variante::puntajeLetra(Letra l) const {
    return _variante->puntajeLetra(l);
}

bool Fachada_Variante::palabraLegitima(const Palabra& palabra) const {
    return _variante->palLegitima(palabra);
}

const Variante* Fachada_Variante::nuestraVariante() const {
    return _variante;
}
