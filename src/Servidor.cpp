#include "Servidor.h"
#include "Notificacion.h"
#include "colaNotificaciones.h"

Servidor::Servidor(Nat k, const Variante& v, const Repositorio& r) : _juego(Juego(k, v, r)), _notificaciones(colaNotificaciones(k)), _conectados(0){
}


IdCliente Servidor::conectarCliente(){
    Notificacion n = Notificacion::nuevaIdCliente(_conectados);
    int id = _conectados;
    _notificaciones.encolarJugador(n, _conectados);
    _conectados++;
    if (_conectados == _juego.cantJugadores()){
        _notificaciones.encolarGeneral(Notificacion::nuevaEmpezar((_juego.tablero()).tamano()));
        _notificaciones.encolarGeneral(Notificacion::nuevaTurnoDe(_juego.turno()));
        for (int i = 0; i < _conectados; i++) {
            _notificaciones.encolarJugador(Notificacion::nuevaReponer(_juego.ultimaReposicion(i)) , i);

        }
    }
    return id;
}


void Servidor::recibirMensaje(IdCliente id, const Ocurrencia& o){
    int puntajeAnterior = _juego.puntaje(id);
    if (_juego.jugadaValida(o, id) && _conectados == _juego.cantJugadores()){
        _notificaciones.encolarGeneral(Notificacion::nuevaUbicar(id, o));
        _juego.ubicar(o);
        _notificaciones.encolarGeneral(Notificacion::nuevaSumaPuntos(id,_juego.puntaje(id) - puntajeAnterior));
        _notificaciones.encolarJugador(Notificacion::nuevaReponer(_juego.ultimaReposicion(id)), id);
        _notificaciones.encolarGeneral(Notificacion::nuevaTurnoDe(_juego.turno()));

    }else{
        _notificaciones.encolarJugador(Notificacion::nuevaMal(),id);
    }
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

const Juego& Servidor::juego(){
    return _juego;
}
