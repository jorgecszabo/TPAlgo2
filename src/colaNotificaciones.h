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
    colaNotificaciones();
    void encolarJugador(Notificacion n, int cid);
    void encolarGeneral(Notificacion n);
    list<Notificacion> notifJugador(int cid);
    int cantJugadores();

private:
    int cantidadJugadores;
    int ordActual;
    struct elem {
        elem(Notificacion n, Nat o): notif(n), ord(o){};
        Notificacion notif;
        int ord;
    };
    list<elem> general;
    vector<list<elem>> personal;
    vector<int> ultimoGeneral;
    vector<int> ultimoPersonal;
};

#endif //TP_JUEGODEPALABRAS_COLANOTIFICACIONES_H
