//
// Created by jorge on 14/11/22.
//
#include "gtest-1.8.1/gtest.h"
#include "../src/colaNotificaciones.h"

TEST(colaNotificaionesTest, cantJugadores) {
    colaNotificaciones cola(18);
    EXPECT_EQ(cola.cantJugadores(), 18);
}

TEST(colaNotificaionesTest, muchasNotificaiones) {
    colaNotificaciones cola(2);
    list<Notificacion> jugador1Orig;
    list<Notificacion> jugador2Orig;

    Notificacion n1(Notificacion::nuevaIdCliente(69));
    Notificacion n2(Notificacion::nuevaIdCliente(70));
    Notificacion general(Notificacion::nuevaEmpezar(70));

    cola.encolarJugador(n1, 0);
    cola.encolarJugador(n2, 1);
    cola.encolarGeneral(general);
    jugador1Orig.push_back(n1);
    jugador2Orig.push_back(n2);
    jugador1Orig.push_back(general);
    jugador2Orig.push_back(general);

    for (int i = 1; i <= 1500; i++) {
        Notificacion spam(Notificacion::nuevaMal());
        cola.encolarJugador(spam, 0);
        jugador1Orig.push_back(spam);
    }
    general = Notificacion::nuevaTurnoDe(4);
    cola.encolarGeneral(general);
    jugador1Orig.push_back(general);
    jugador2Orig.push_back(general);

    EXPECT_EQ(jugador1Orig, cola.notifJugador(0));
    EXPECT_EQ(jugador2Orig, cola.notifJugador(1));
}