#include "gtest-1.8.1/gtest.h"
#include "../src/Tablero.h"

TEST(tableroTest, vacio) {
    Tablero tab(10);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            EXPECT_FALSE(tab.hayLetra(i,j));
        }
    }
}

TEST(tableroTest, llenarTablero) {
    Tablero tab(10);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            tab.ponerLetra(i, j, 'q');
        }
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            EXPECT_TRUE(tab.hayLetra(i,j));
        }
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            EXPECT_EQ(tab.letra(i,j), 'q');
        }
    }
}