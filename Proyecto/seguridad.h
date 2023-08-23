/**Definición de la clase Segurida*/
#pragma once
#include <string>

class Seguridad{
    /**Modelo de la seguridad de la pista de karts*/
    public:
        void seguridadKart(int maxKarts);
        void seguridadPista();
    private:
        int randomSecurity(int maxElem);
        void cambiarElemento(std::string msg, int elem);

};