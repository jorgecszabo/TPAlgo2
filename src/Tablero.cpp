#include "Tablero.h"

Tablero::Tablero(int n) {
    vector<vector<tuple<bool, Letra>>> tab;
    for (int i = 0; i < n; i++) {
        vector<tuple<bool, Letra>> fila;
        for (int j = 0; j < n; j++) {
            tuple<bool, Letra> casillero = make_tuple(false, 'a');
            fila.push_back(casillero);
        }
        tab.push_back(fila);
    }
    _tablero = tab;
}

Nat Tablero::tamano(){
    return _tablero.size();
}

bool Tablero::hayLetra(int i, int j){
    return get<0>(_tablero[i][j]);
}

void Tablero::ponerLetra(int i, int j, Letra l){
    get<0>(_tablero[i][j]) = true;
    get<1>(_tablero[i][j]) = l;
}

Letra Tablero::letra(int i, int j){
    return get<1>(_tablero[i][j]);
}

void Tablero::quitarLetra(int i, int j){
    get<0>(_tablero[i][j]) = false;
}

bool Tablero::celdasLibres(const Ocurrencia& o){
    bool res = true;
    for(tuple<Nat, Nat, Letra> e : o){
        Nat col = get<0>(e);
        Nat fila = get<1>(e);
        res = res && !get<0>(_tablero[col][fila]);
    }
    return res;
}
