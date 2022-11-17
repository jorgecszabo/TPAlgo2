#include "Servidor.h"
#include "Notificacion.h"
#include "colaNotificaciones.h"

Servidor::Servidor(Juego j, const Repositorio& r, colaNotificaciones n) : _juego(j), _repInicial(r), _notificaciones(n){
}


IdCliente Servidor::conectarCliente(){
    Notificacion n = Notificacion::nuevaIdCliente(_conectados);
    int id = _conectados;
    _notificaciones.encolarJugador(n, _conectados);
    _conectados++;

    if (_conectados == _juego.cantJugadores()){
        Notificacion n2 = Notificacion::nuevaEmpezar((_juego.tablero()).tamano());
        _notificaciones.encolarGeneral(n2);
    }
    return id;
}


void Servidor::recibirMensaje(IdCliente id, const Ocurrencia& o){
    int puntajeAnterior = _juego.puntaje(id);
    if (_juego.turno() == id && _juego.jugadaValida(o, id)){
        _notificaciones.encolarGeneral(Notificacion::nuevaUbicar(id, o));
        _notificaciones.encolarGeneral(Notificacion::nuevaTurnoDe((id+1)%_notificaciones.cantJugadores()));

        _juego.ubicar(o);
        _notificaciones.encolarGeneral(Notificacion::nuevaSumaPuntos(id,_juego.puntaje(id) - puntajeAnterior));

        _notificaciones.encolarJugador(Notificacion::nuevaReponer(fichasAReponer(o, _juego.repositorio())), id);
    }else{
        _notificaciones.encolarJugador(Notificacion::nuevaMal(),id);
    }
}

multiset<Letra> Servidor::fichasAReponer(const Ocurrencia& o, Repositorio r){
    multiset<Letra> ms;
    Repositorio::iterator it = r.begin();
    for(int i = 0; i < o.size(); i++){
        Letra elem = *it;
        ms.insert(elem);
        it++;
    }
    return ms;
}


Nat Servidor::jugadoresEsperados(){
    return _notificaciones.cantJugadores();
}

Nat Servidor::jugadoresConectados(){
    return _conectados;
}

list<Notificacion> Servidor::notificaciones(IdCliente id){
    return _notificaciones.notifJugador(id);
}

Juego Servidor::juego(){
    return _juego;
}