/**Implementación de la clase seguridad*/
#include "seguridad.h"
#include <iostream>
#include <random>
#include <unistd.h>

void Seguridad::seguridadKart(int maxKarts){
    /**Verificar la seguridad que está en el kart*/
    int elementoInseguro;
    std::cout << "Verificando la seguridad de los karts" << std::endl;
    std::cout << "Verificando cascos..." << std::endl;
    sleep(1);
    elementoInseguro = randomSecurity(maxKarts);
    if (elementoInseguro != -1){
        cambiarElemento("Casco del kart ", elementoInseguro);
    }
    std::cout << "Verificando la seguridad de las rodilleras" << std::endl;
    std::cout << "Verificando rodilleras..." << std::endl;
    sleep(1);
    elementoInseguro = randomSecurity(maxKarts);
    if (elementoInseguro != -1){
        cambiarElemento("Rodilleras del kart: ", elementoInseguro);
    }
    std::cout << "Verificando la seguridad de las coderas" << std::endl;
    std::cout << "Verificando coderas..." << std::endl;
    elementoInseguro = randomSecurity(maxKarts);
    if (elementoInseguro != -1){
        cambiarElemento("Coderas del kart: ", elementoInseguro);
    }
    std::cout << "Activando acceso a control remoto de los karts..." << std::endl;
    elementoInseguro = randomSecurity(maxKarts);
    if (elementoInseguro != -1){
        cambiarElemento("Control remoto del kart: ", elementoInseguro);
    }
    std::cout << "REVISION DE LOS ELEMENTOS DE SEGURIDAD DE LOS KARTS FINALIZADA\n" << std::endl;
}

void Seguridad::seguridadPista(){
    /**Verificar la seguridad de la pista*/
    int banderaRota;
    std::string nombreBandera;
    std::cout << "Verificando la seguridad de la pista..."<< std::endl;
    std::cout << "Verificando banderas..." << std::endl;
    banderaRota = randomSecurity(4);
    if (banderaRota != -1){
        switch (banderaRota) {
            case 1:
                nombreBandera = "Roja";
                break;
            case 2:
                nombreBandera = "Verde";
                break;
            case 3: 
                nombreBandera = "Amarilla";
                break;
            case 4: 
                nombreBandera = "Cuadros";
                break;
            default:
                nombreBandera = "ROJA";
                break;
        }
        std::cout << "La bandera " << nombreBandera << " no está en condiciones de uso" << std::endl;
        std::cout << "La bandera " << nombreBandera << " ha sido cambiada por otra" << std::endl;
    }
    std::cout << "REVISION DE LOS ELEMENTOS DE SEGURIDAD DE LA PISTA HA FINALIZADO\n" << std::endl;     
}


int Seguridad::randomSecurity(int maxElem){
    /**Simulador para verificación aleatoria de un elemento de seguridad*/
    if (rand()%10 == 3){
        return (rand()% maxElem + 1);
    }
    return -1;
}

void Seguridad::cambiarElemento(std::string msg, int elem){
    /**Simular el cambio de un elemento dañado*/
    std::cout << msg << elem << " esta dañado" << std::endl;
    std::cout << msg << elem << " ha sido reparado" << std::endl;
}
