#include "gtest-1.8.1/gtest.h"
#include "../src/string_map.h"
#include "utils/PalabrasComunes.h"
#include <set>
TEST(string_map_test, vacio) {
	string_map conj(TAMANIO_ALFABETO);
	EXPECT_TRUE(conj.vacio());
}

TEST(string_map_test, miniTest) {
    string_map conj(TAMANIO_ALFABETO);
    conj.agregar({'a', 'b', 'a'});
    conj.agregar({'a'});
    EXPECT_TRUE(conj.pertenece({'a'}));
    EXPECT_TRUE(conj.pertenece({'a', 'b', 'a'}));
    conj.borrar({'a', 'b', 'a'});
    EXPECT_TRUE(conj.pertenece({'a'}));
    EXPECT_FALSE(conj.pertenece({'a', 'b', 'a'}));
    conj.borrar({'a'}); // Esto es para un breakpoint
}

TEST(string_map_test, palabras) {
    int masLarga = 0;
    for (Palabra palabra : palabrasComunes) {
        masLarga = palabra.size() > masLarga ? palabra.size() : masLarga;
    }
	string_map conj(TAMANIO_ALFABETO);
    set<Palabra> conjRef;
	for (Palabra palabra : palabrasComunes) {
		conj.agregar(palabra);
        conjRef.insert(palabra);
	}
	for (Palabra palabra : palabrasComunes) {
		EXPECT_TRUE(conj.pertenece(palabra));
	}
    EXPECT_EQ(conj.palMasLarga(), masLarga);
    EXPECT_EQ(conj.cardinal(), conjRef.size());
    for (Palabra palabra : palabrasComunes) {
            conj.borrar(palabra);
	}
	for (Palabra palabra : palabrasComunes) {
		EXPECT_FALSE(conj.pertenece(palabra));
	}
}

TEST(string_map_test, copia) {
    string_map conj1(TAMANIO_ALFABETO);
    for (Palabra palabra : palabrasComunes) {
        conj1.agregar(palabra);
    }
    string_map conj2(TAMANIO_ALFABETO);
    conj2 = conj1;
    for (Palabra palabra : palabrasComunes) {
        if (conj1.pertenece(palabra))
            conj1.borrar(palabra);
    }
    for (Palabra palabra : palabrasComunes) {
        EXPECT_TRUE(conj2.pertenece(palabra));
    }
}
/*
int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}*/
