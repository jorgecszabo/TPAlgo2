#ifndef TP_JUEGODEPALABRAS_SERVIDOR_H
#define TP_JUEGODEPALABRAS_SERVIDOR_H

#include "Tipos.h"
#include "Juego.h"
#include "colaNotificaciones.h"

using namespace std;


class Servidor {
public:
    /*
     * Inicializar un nuevo servidor, y todas sus dependencias (como el juego,
     * la variante, el tablero, etc)
     */
    Servidor(
        Juego j,
        const Repositorio& r,
        colaNotificaciones n
    );

    /*
     * Conecta un cliente al servidor y retorna su id de cliente
     */
    IdCliente conectarCliente();

    /*
     * Recibe un mensaje o del cliente id
     */
    void recibirMensaje(IdCliente id, const Ocurrencia& o);

    /*
     * Retorna la cantidad de jugadores necesarios para poder empezar el juego
     */
    Nat jugadoresEsperados();

    /*
     * Retorna la cantidad de jugadores necesarios para poder empezar el juego

     */
    Nat jugadoresConectados();

    /*
     * Consulta y vacia la cola de notificaciones del cliente id
     */
    list<Notificacion> notificaciones(IdCliente id);

    Juego juego();

private:
    Juego _juego;
    Nat _conectados;
    Repositorio _repInicial;
    colaNotificaciones _notificaciones;

    multiset<Letra> fichasAReponer(int cantidad);
    Repositorio::iterator _it;

    };

#endif