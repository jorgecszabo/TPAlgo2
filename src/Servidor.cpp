#include "Servidor.h"
#include "Notificacion.h"
#include "colaNotificaciones.h"

Servidor::Servidor(Juego j, const Repositorio& r, colaNotificaciones n) : _juego(j), _repInicial(r), _notificaciones(n), _conectados(0){
    _it = _repInicial.begin();
}


IdCliente Servidor::conectarCliente(){
    Notificacion n = Notificacion::nuevaIdCliente(_conectados);
    int id = _conectados;
    _notificaciones.encolarJugador(n, _conectados);
    _conectados++;
    if (_conectados == _juego.cantJugadores()){
        Notificacion n2 = Notificacion::nuevaEmpezar((_juego.tablero()).tamano());
        _notificaciones.encolarGeneral(n2);
        _notificaciones.encolarGeneral(Notificacion::nuevaTurnoDe(_juego.turno()));
        for (int i = 0; i < _conectados; i++) {
            _notificaciones.encolarJugador(Notificacion::nuevaReponer(fichasAReponer(_juego.variante().fichas())) , i);
        }
    }
    return id;
}


void Servidor::recibirMensaje(IdCliente id, const Ocurrencia& o){
    int puntajeAnterior = _juego.puntaje(id);
    if (_juego.turno() == id && _juego.jugadaValida(o, id)){
        _notificaciones.encolarGeneral(Notificacion::nuevaUbicar(id, o));
        _juego.ubicar(o);
        _notificaciones.encolarGeneral(Notificacion::nuevaSumaPuntos(id,_juego.puntaje(id) - puntajeAnterior));
        _notificaciones.encolarJugador(Notificacion::nuevaReponer(fichasAReponer(o.size())), id);
        _notificaciones.encolarGeneral(Notificacion::nuevaTurnoDe((id+1)%_notificaciones.cantJugadores()));

    }else{
        _notificaciones.encolarJugador(Notificacion::nuevaMal(),id);
    }
}

multiset<Letra> Servidor::fichasAReponer(int cantidad){
    multiset<Letra> ms;
    for(int i = 0; i < cantidad; i++){
        Letra elem = *_it;
        ms.insert(elem);
        _it++;
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