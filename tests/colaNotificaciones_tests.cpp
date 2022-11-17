//
// Created by jorge on 14/11/22.
//
#include "gtest-1.8.1/gtest.h"
#include "../src/colaNotificaciones.h"

TEST(colaNotificaionesTest, cantJugadores) {
    colaNotificaciones cola(18);
    EXPECT_EQ(cola.cantJugadores(), 18);
}
/*
TEST(colaNotificaionesTest, muchasNotificaiones) {
    colaNotificaciones cola(2);
    list<int> j0Orig;
    list<int> j1Orig;
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            cola.encolarGeneral(i);
            j0Orig.push_back(i);
            j1Orig.push_back(i);
        } else {
            cola.encolarJugador(i, 0);
            j0Orig.push_back(i);
        }
    }
    list<int> j0Encolada0 = cola.notifJugador(0);
    list<int> j1Encolada0 = cola.notifJugador(1);
    EXPECT_EQ(j0Encolada0, j0Orig);
    EXPECT_EQ(j1Orig, j1Encolada0);
    for (int i = 20; i < 30; i++) {
        if (i % 2 == 0) {
            cola.encolarGeneral(i);
            j0Orig.push_back(i);
            j1Orig.push_back(i);
        } else {
            cola.encolarJugador(i, 0);
            j0Orig.push_back(i);
        }
    }
    list<int> j0Encolada1 = cola.notifJugador(0);
    list<int> j1Encolada1 = cola.notifJugador(1);
    for (int e : j0Encolada1)
        j0Encolada0.push_back(e);
    for (int e : j1Encolada1)
        j1Encolada0.push_back(e);
    EXPECT_EQ(j0Encolada0, j0Orig);
    EXPECT_EQ(j1Orig, j1Encolada0);
    j0Encolada1 = cola.notifJugador(0);
    j1Encolada1 = cola.notifJugador(1);
    EXPECT_EQ(j0Encolada1.size(), 0);
    EXPECT_EQ(j1Encolada1.size(), 0);

}*/