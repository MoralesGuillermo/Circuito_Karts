/**Definición de la clase pista karts*/
#pragma once
#include <string>
#include "emergencia.h"
#include "semaforo.h"
#include "reloj.h"

class PistaKarts{
    public:
        PistaKarts();
        bool ingresarPista(int i);
        bool ingresarPistaGrupos(int i, int grupo);
        void ingresarPistaKid(int i);
        void ingresarPistaKidGrupos(int i, int grupo);
        void ingresarKart(int i, bool turno);
        void ingresarKartGrupos(int i, int grupo, bool turno);
        void correr(int i, int time, bool tipoPista, Semaforo semaforo, Reloj reloj, Emergencia emergencia);
        void correrGrupos(int i, int grupo, bool tipoPista, int time, Semaforo semaforo, Reloj reloj, Emergencia emergencia);
        void regresarKart(int i);
        void regresarKartGrupos(int i, int grupo);
        void obstaculos();
        void obstaculosKid();
    private:
        void obstacleDamage(bool tipoPista);
        std::string kartAdulto;
        std::string kartNino;

};