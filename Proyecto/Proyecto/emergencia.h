/**Definición de la clase Emergencia*/
#pragma once
#include "semaforo.h"

class Emergencia{
    /**Representación de una emergencia en el circuito*/
    public:
        void medica(int i, Semaforo semaforo);
        void medicaGrupos(int i, int grupo, Semaforo semaforo);
        void mecanica(int i);
        void mecanicaGrupos(int i, int grupo);
};