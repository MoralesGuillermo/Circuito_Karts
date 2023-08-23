/**Definición de la clase Reloj*/
#pragma once
#include "semaforo.h"

class Reloj{
    public:
        void tiempoRecorrido(int i, int time);
        void tiempoRecorridoGrupos(int i, int grupo, int time);
        void tiempoEspera(int i, int maxCorredores, Semaforo semaforo);
};