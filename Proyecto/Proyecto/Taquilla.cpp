/**Implementación de la clase Taquilla*/
# include "Taquilla.h"
#include <iostream>
#include <unistd.h>


void Taquilla::venderBoleto(int i){
    /**Simular la venta de un boleto*/
    // Retornar un número aleatorio entre el 0 y el 10
    std::cout << "Vendiendo boleto "<< i << "..." << std::endl;
    sleep(1);
    std::cout << "Boleto " << i << " vendido\n" << std::endl;
}

void Taquilla::venderBoletoGrupos(int i, int grupo){
    /**Simular la venta de un boleto*/
    // Retornar un número aleatorio entre el 0 y el 10
    std::cout << "Vendiendo boleto "<< i << " del grupo: " << grupo << "..." << std::endl;
    // TODO: DETERMINE HOW TO CHOOSE WHICH PERSON TYPE THE TICKET IS BEING SOLD
    sleep(1);
    std::cout << "Boleto " << i << " del grupo: " << grupo << " vendido\n" << std::endl;
}
void Taquilla::esperarEmpleado(){
    /**Simular la espera del empleado a la taquilla*/
    int randFlag;
    std::cout << "No se encuentra el empleado vendedor de boletos" << std::endl;
    do{
        std::cout << "Esperando empleado..." << std::endl;
        randFlag = rand() % 11;
        sleep(1);
    }while(randFlag == 5);
    std::cout << "Empleado ha llegado" << std::endl;
}
