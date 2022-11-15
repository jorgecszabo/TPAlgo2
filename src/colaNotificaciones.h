#ifndef TP_JUEGODEPALABRAS_COLANOTIFICACIONES_H
#define TP_JUEGODEPALABRAS_COLANOTIFICACIONES_H
#include <list>
#include <vector>

using namespace std;
//IMPORTANTE:
//Las notif son un int por ahora. Cambiar al tipo correcto de notif!!!!!!
//IMPORTANTE ^
class colaNotificaciones {
public:
    colaNotificaciones(int k);
    void encolarJugador(int n, int cid);
    void encolarGeneral(int n);
    list<int> notifJugador(int cid);
    int cantJugadores();

private:
    int cantidadJugadores;
    int ordActual;
    struct elem {
        int notif;
        int ord;
    };
    list<elem> general;
    vector<list<elem>> personal;
    vector<int> ultimoGeneral = {0};
    vector<int> ultimoPersonal = {0};
};

#endif //TP_JUEGODEPALABRAS_COLANOTIFICACIONES_H
