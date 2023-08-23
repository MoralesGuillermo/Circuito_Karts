/**Definición de la clase Emergencia*/
#include "emergencia.h"
#include <iostream>
#include <random>
#include <unistd.h>

void Emergencia::medica(int i, Semaforo semaforo){
    /**Simular el proceso de una emergencia médica*/
    // Liberar el semaforo
    semaforo.aumentar();
    std::cout << "Llevando corredor " <<  i << " a la enfermería" << std::endl;
    std::cout << "Atendiendo corredor " << i << std::endl;
    std::cout << "Verificando tipo de emergencia..." << std::endl;
    if (rand()%10 > 7){
        std::cout << "La emegencia del corredor " << i << " es grave!" << std::endl;
        std::cout <<"Llamando servicios de emergencia..." << std::endl;
        sleep(3);
        std::cout << "Se remite el corredor " << i << " a los servicios de emergencia" << std::endl;
    }else{
        std::cout << "La emegencia del corredor " << i << " es leve" << std::endl;
        std::cout << "Se atienden las heridas del corredor " << i << std::endl;
        std::cout << "El corredor " << i << " ha sido atendido" << std::endl;
    }
    std::cout << "Corredor " << i << " abandona el circuito\n" <<  std::endl;
    // Terminar el proceso
    exit(0);
}

void Emergencia::medicaGrupos(int i, int grupo, Semaforo semaforo){
    /**Simular el proceso de una emergencia médica*/
    // Liberar el semaforo
    semaforo.aumentar();
    std::cout << "Llevando corredor " <<  i << " del grupo "<< grupo << " a la enfermería" << std::endl;
    std::cout << "Atendiendo corredor " << i << " del grupo " << grupo <<std::endl;
    std::cout << "Verificando tipo de emergencia..." << std::endl;
    if (rand()%10 > 7){
        std::cout << "La emegencia del corredor " << i << " del grupo " << grupo << " es grave!" << std::endl;
        std::cout <<"Llamando servicios de emergencia..." << std::endl;
        sleep(3);
        std::cout << "Se remite el grupo " << grupo << " a los servicios de emergencia" << std::endl;
    }else{
        std::cout << "La emegencia del corredor " << i << " del grupo "<< grupo <<" es leve" << std::endl;
        std::cout << "Se atienden las heridas del corredor " << i << " del grupo " << grupo << std::endl;
        std::cout << "El corredor " << i << " del grupo " << grupo << " ha sido atendido" << std::endl;
    }
    std::cout << "Grupo " << grupo << " abandona el circuito\n" <<  std::endl;
    // Terminar el proceso
    exit(0);

}

void Emergencia::mecanica(int i){
    /**Simular el proceso para una emergencia mecánica*/
    std::cout << "Llevando kart del corredor " << i << " al taller" << std::endl;
    std::cout << "Se le da un kart de repuesto al corredor. Corredor " << i << " vuelve a la pista" << std::endl;
    std::cout <<  "Revisando kart del corredor "<< i <<"..." << std::endl;
    std::cout << "El kart será reparado entre semana\n" << std::endl;
}

void Emergencia::mecanicaGrupos(int i, int grupo){
    /**Simular el proceso para una emergencia mecánica*/
    std::cout << "Llevando kart del corredor " << i << " del grupo " << grupo << " al taller" << std::endl;
    std::cout << "Se le da un kart de repuesto al corredor. Corredor " << i << " del grupo " << grupo << " vuelve a la pista" << std::endl;
    std::cout <<  "Revisando kart del corredor "<< i << " del grupo " << grupo << "..." << std::endl;
    std::cout << "El kart será reparado entre semana\n" << std::endl;
}
