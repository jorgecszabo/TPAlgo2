#include "gtest-1.8.1/gtest.h"
#include "../src/string_map.h"
#include "../src/Tipos.h"
#include "../src/Letra.h"
#include "utils/PalabrasComunes.h"

TEST(string_map_test, vacio) {
	string_map conj(TAMANIO_ALFABETO);
	EXPECT_TRUE(conj.vacio());
}

TEST(string_map_test, palabras) {
    int masLarga = 0;
    for (Palabra palabra : palabrasComunes) {
        masLarga = palabra.size() > masLarga ? palabra.size() : masLarga;
    }
	string_map conj(TAMANIO_ALFABETO);
	for (Palabra palabra : palabrasComunes) {
		conj.agregar(palabra);
	}
	for (Palabra palabra : palabrasComunes) {
		EXPECT_TRUE(conj.pertenece(palabra));
	}
	for (Palabra palabra : palabrasComunes) {
		if (conj.pertenece(palabra)) // Para cumplir la precondición :)
            conj.borrar(palabra);
	}
	for (Palabra palabra : palabrasComunes) {
		EXPECT_FALSE(conj.pertenece(palabra));
	}
    EXPECT_EQ(conj.palMasLarga(), masLarga);
}

TEST(string_map_test, copia) {
    string_map conj1(TAMANIO_ALFABETO);
    for (Palabra palabra : palabrasComunes) {
        conj1.agregar(palabra);
    }
    string_map conj2(TAMANIO_ALFABETO);
    conj2 = conj1;
    for (Palabra palabra : palabrasComunes) {
        if (conj1.pertenece(palabra)) // Para cumplir la precondición :)
            conj1.borrar(palabra);
    }
    for (Palabra palabra : palabrasComunes) {
        EXPECT_TRUE(conj2.pertenece(palabra));
    }
}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
