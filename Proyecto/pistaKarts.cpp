/**Definición de la clase PistaKarts*/
#include "pistaKarts.h"
#include <iostream>
#include <random>
#include <unistd.h>


PistaKarts::PistaKarts(){
    this->kartAdulto = "Cilindrada alta";
    this->kartNino = "Cilindrada baja";      
}
void PistaKarts::ingresarPista(int i){
    std::cout << "Ingresando persona " << i <<" a Pista" << std::endl;
    switch (rand()%2){
        case 0:
            std::cout << "Pista elegida por corredor " << i <<": Normal" << std::endl;
            break;
        case 1:
            std::cout << "Pista elegida por el corredor " << i <<": Todoterreno" << std::endl;
            break;  
    }
    std::cout <<"Persona "<< i << " ha sido ingresada a Pista\n" << std::endl;
}

void PistaKarts::ingresarPistaGrupos(int i, int grupo){
    std::cout << "Ingresando persona " << i << " del grupo "<< grupo << " a Pista" << std::endl;
    switch (rand()%2){
        case 0:
            std::cout << "Pista elegida por corredor " << i << " del grupo " << grupo <<": Normal" << std::endl;
            break;
        case 1:
            std::cout << "Pista elegida por el corredor " << i << "del grupo "<< grupo << ": Todoterreno" << std::endl;
            break;  
    }
    std::cout <<"Persona "<< i << " del grupo "<< grupo << " ha sido ingresada a Pista\n" << std::endl;
}

void PistaKarts::ingresarPistaKid(int i){
    std::cout << "Ingresando persona " << i <<" a Pista" << std::endl;
    std::cout << "Pista del corredor " << i << ": Normal" << std::endl;
    std::cout <<"Persona "<< i << " ha sido ingresada a Pista\n" << std::endl;
}

void PistaKarts::ingresarPistaKidGrupos(int i, int grupo){
    std::cout << "Ingresando persona " << i << " del grupo "<< grupo << " a Pista" << std::endl;
    std::cout << "Pista del corredor " << i << " del grupo " << grupo << ": Normal" << std::endl;
    std::cout <<"Persona "<< i << " del grupo "<< grupo << " ha sido ingresada a Pista\n" << std::endl;
}

void PistaKarts::ingresarKart(int i, bool turno){
    std::string tipo = turno? this->kartAdulto: this->kartNino;
    std::cout << "Persona " << i << " ingresa a kart tipo: " << tipo << std::endl;
    std::cout << "Persona " << i << " ha ingresado al kart\n" << std::endl;
}

void PistaKarts::ingresarKartGrupos(int i, int grupo, bool turno){
    std::string tipo = turno? this->kartAdulto: this->kartNino;
    std::cout << "Persona " << i << " del grupo "<< grupo <<" ingresa a kart tipo: " << tipo << std::endl;
    std::cout << "Persona " << i <<  " del grupo " << grupo <<" ha ingresado al kart\n" << std::endl;
}

void PistaKarts::correr(int i, int time, Semaforo semaforo, Reloj reloj, Emergencia emergencia){
    /**Simlular la carrera de un corredor
    * Dormir el proceso una cantidad dada de tiempo
    */
    int randVal;
    std::cout << "Corredor " << i << " esta corriendo..." << std::endl;
    sleep(time);    
    randVal = rand()%20;
    if (randVal >= 18){
        // Ocurre una emergencia médica
        std::cout << "El corredor " << i << " ha sufrido una emergencia médica!" << std::endl;
        emergencia.medica(i, semaforo);
    } else if (randVal > 15){
        std::cout << "El corredor " << i << " ha sufirdo una emergencia mecánica" << std::endl;
        emergencia.mecanica(i);
    }
    std::cout << "Corredor "<< i << " ha terminado de correr" << std::endl;
    reloj.tiempoRecorrido(i, time);
}

void PistaKarts::correrGrupos(int i, int grupo, int time, Semaforo semaforo, Reloj reloj, Emergencia emergencia){
    /**Simlular la carrera de un corredor
     * Dormir el proceso una cantidad dada de tiempo
    */
    int randVal;
    std::cout << "Corredor " << i << " del grupo " << grupo << " esta corriendo..." << std::endl;
    sleep(time);
    randVal = rand()%20;
    if (randVal > 18){
        // Ocurre una emergencia médica
        std::cout << "El corredor " << i << " del grupo " << grupo <<" ha sufrido una emergencia médica!" << std::endl;
        emergencia.medicaGrupos(i, grupo,  semaforo);
    } else if (randVal > 15){
        std::cout << "El corredor " << i << " del grupo "<< grupo <<" ha sufirdo una emergencia mecánica" << std::endl;
        emergencia.mecanicaGrupos(i, grupo);
    }
    std::cout << "Corredor "<< i << " del grupo " << grupo << " ha terminado de correr" << std::endl;
    reloj.tiempoRecorridoGrupos(i, grupo, time);
}

void PistaKarts::regresarKart(int i){
    /**Simular el retorno del kart a la estación*/
    std::cout << "Corredor " << i << " ha retornado el kart\n" << std::endl;;
}

void PistaKarts::regresarKartGrupos(int i, int grupo){
    /**Simular el retorno del kart a la estación*/
    std::cout << "Corredor " << i << " del grupo "<< grupo << " ha retornado el kart\n" << std::endl;;
}

void PistaKarts::obstaculos() {
    std::cout << "Obstaculos en la pista han sido colocados\n" << std::endl;
}
