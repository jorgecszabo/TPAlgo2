#include "gtest-1.8.1/gtest.h"
#include "../src/Fachada_Servidor.h"

#include "utils/Repositorio.h"
#include "utils/PalabrasComunes.h"

TEST(juegosTestsPropios, miniJuego) {
    string_map conjPal;
    conjPal.agregar({'a','a'});
    conjPal.agregar({'a','b'});
    conjPal.agregar({'b','b'});
    conjPal.agregar({'a'});
    conjPal.agregar({'b'});
    vector<Nat> puntaje(TAMANIO_ALFABETO, 1);
    puntaje[0] = 2;
    puntaje[1] = 3;
    Variante var(puntaje, 2, 2, conjPal);
    Repositorio r = {'a', 'a', 'b', 'a', 'b', 'b', 'b', 'b','a', 'a', 'b', 'b', 'b', 'b', 'b', 'b','a', 'a', 'b', 'a', 'b', 'b', 'b', 'b' };
    Juego j(2, var, r);
    EXPECT_TRUE(j.jugadaValida({{0,0,'a'}, {0,1,'a'}},0));
    EXPECT_FALSE(j.jugadaValida({{0,0,'a'}, {0,1,'a'}},1));
    EXPECT_TRUE(j.jugadaValida({{0,0,'a'}, {1,0,'a'}},0));
    EXPECT_FALSE(j.jugadaValida({{0,0,'a'}, {1,1,'a'}},0));
    EXPECT_FALSE(j.jugadaValida({{0,1,'b'}},0));
    Ocurrencia jugada = {{0,0,'a'}, {0,1,'a'}};
    j.ubicar(jugada); // Ubica 0
    EXPECT_TRUE(j.jugadaValida({{1,0,'b'}},1));
    EXPECT_FALSE(j.jugadaValida({{0,0,'a'}, {0,1,'a'}},1));
    j.ubicar({{1,0,'b'}}); // Ubica 1
    EXPECT_FALSE(j.jugadaValida({{1,0,'b'}},0));
    EXPECT_TRUE(j.jugadaValida({{1,1,'b'}}, 0));
    j.ubicar({{1,0,'b'}}); // Ubica 0
    cout << j.puntaje(0) << " " << j.puntaje(1) << endl;
};