/**Definición de la clase pista karts*/
#pragma once
#include <string>
#include "emergencia.h"
#include "semaforo.h"
#include "reloj.h"

class PistaKarts{
    public:
        PistaKarts();
        void ingresarPista(int i);
        void ingresarPistaGrupos(int i, int grupo);
        void ingresarPistaKid(int i);
        void ingresarPistaKidGrupos(int i, int grupo);
        void ingresarKart(int i, bool turno);
        void ingresarKartGrupos(int i, int grupo, bool turno);
        void correr(int i, int time, Semaforo semaforo, Reloj reloj, Emergencia emergencia);
        void correrGrupos(int i, int grupo, int time, Semaforo semaforo, Reloj reloj, Emergencia emergencia);
        void regresarKart(int i);
        void regresarKartGrupos(int i, int grupo);
        void obstaculos();
    private:
        std::string kartAdulto;
        std::string kartNino;

};