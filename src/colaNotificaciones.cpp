//
// Created by jorge on 14/11/22.
//

#include "colaNotificaciones.h"
#include <cassert>

colaNotificaciones::colaNotificaciones() {
    colaNotificaciones(1);
}

colaNotificaciones::colaNotificaciones(int k) {
    cantidadJugadores = k;
    ordActual = 0;
    for (int i = 0; i < k; i++) {
        list<elem> l;
        personal.push_back(l);
    }
    ultimoGeneral = vector<int>(k);
    ultimoPersonal = vector<int>(k);
}

void colaNotificaciones::encolarJugador(Notificacion n, int cid) {
    assert(cid < cantidadJugadores);
    elem notifActual(n, ordActual);
    ordActual++;
    personal.at(cid).push_back(notifActual);
}

void colaNotificaciones::encolarGeneral(Notificacion n) {
    elem notifActual(n, ordActual);
    ordActual++;
    general.push_back(notifActual);
}

std::list<Notificacion> colaNotificaciones::notifJugador(int cid) {
    assert(cid < cantidadJugadores);
    list<Notificacion> res;
    int longRecorridoPersonal = personal[cid].size() - ultimoPersonal[cid];
    ultimoPersonal[cid] += longRecorridoPersonal;
    int longRecorridoGeneral = general.size() - ultimoGeneral[cid];
    ultimoGeneral[cid] += longRecorridoGeneral;
    list<elem>::reverse_iterator personalIt= personal[cid].rbegin();
    list<elem>::reverse_iterator generalIt= general.rbegin();
    while (longRecorridoGeneral > 0 && longRecorridoPersonal > 0) {
        if (personalIt->ord > generalIt->ord) {
            res.push_front(personalIt->notif);
            ++personalIt;
            longRecorridoPersonal--;
        } else {
            res.push_front(generalIt->notif);
            ++generalIt;
            longRecorridoGeneral--;
        }
    }
    while (longRecorridoGeneral > 0) {
        res.push_front(generalIt->notif);
        ++generalIt;
        longRecorridoGeneral--;
    }
    while (longRecorridoPersonal > 0) {
        res.push_front(personalIt->notif);
        ++personalIt;
        longRecorridoPersonal--;
    }
    return res;
}

int colaNotificaciones::cantJugadores() {
    return cantidadJugadores;
}