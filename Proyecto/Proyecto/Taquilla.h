/**Definición de la clase taquilla*/
#pragma once
class Taquilla{
    public:
        void venderBoleto(int i);
        void venderBoletoGrupos(int i, int grupo);
    private:
        void esperarEmpleado();
};