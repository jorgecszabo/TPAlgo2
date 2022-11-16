#ifndef TP_JUEGODEPALABRAS_COLANOTIFICACIONES_H
#define TP_JUEGODEPALABRAS_COLANOTIFICACIONES_H
#include <list>
#include <vector>
#include "Notificacion.h"

using namespace std;
//IMPORTANTE:
//Las notif son un int por ahora. Cambiar al tipo correcto de notif!!!!!!
//IMPORTANTE ^
class colaNotificaciones {
public:
    colaNotificaciones(int k);
    void encolarJugador(Notificacion n, int cid);
    void encolarGeneral(Notificacion n);
    list<Notificacion> notifJugador(int cid);
    int cantJugadores();

private:
    int cantidadJugadores;
    int ordActual;
    struct elem {
        Notificacion notif;
        int ord;
    };
    list<elem> general;
    vector<list<elem>> personal;
    vector<int> ultimoGeneral = {0};
    vector<int> ultimoPersonal = {0};
};

#endif //TP_JUEGODEPALABRAS_COLANOTIFICACIONES_H
