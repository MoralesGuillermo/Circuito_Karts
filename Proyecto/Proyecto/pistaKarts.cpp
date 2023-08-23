/**Definición de la clase PistaKarts*/
#include "pistaKarts.h"
#include <iostream>
#include <random>
#include <unistd.h>
#include <unordered_map>


PistaKarts::PistaKarts(){
    this->kartAdulto = "Cilindrada alta";
    this->kartNino = "Cilindrada baja";      
}
bool PistaKarts::ingresarPista(int i){
    std::cout << "Ingresando persona " << i <<" a Pista" << std::endl;
    bool pista;
    switch (rand()%2){
        case 0:
            std::cout << "Pista elegida por corredor " << i <<": Normal" << std::endl;
            pista = true;
            break;
        case 1:
            std::cout << "Pista elegida por el corredor " << i <<": Todoterreno" << std::endl;
            pista = false;
            break;  
    }
    std::cout <<"Persona "<< i << " ha sido ingresada a Pista\n" << std::endl;
    return pista;
}

bool PistaKarts::ingresarPistaGrupos(int i, int grupo){
    std::cout << "Ingresando persona " << i << " del grupo "<< grupo << " a Pista" << std::endl;
    bool tipoPista;
    switch (rand()%2){
        case 0:
            std::cout << "Pista elegida por corredor " << i << " del grupo " << grupo <<": Normal" << std::endl;
            tipoPista = true;
            break;
        case 1:
            std::cout << "Pista elegida por el corredor " << i << " del grupo "<< grupo << ": Todoterreno" << std::endl;
            tipoPista = false;
            break;  
    }
    std::cout <<"Persona "<< i << " del grupo "<< grupo << " ha sido ingresada a Pista\n" << std::endl;
    return tipoPista;
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

void PistaKarts::correr(int i, int time, bool tipoPista, Semaforo semaforo, Reloj reloj, Emergencia emergencia){
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
    this->obstacleDamage(tipoPista);
    std::cout << "Corredor "<< i << " ha terminado de correr" << std::endl;
    reloj.tiempoRecorrido(i, time);
}

void PistaKarts::correrGrupos(int i, int grupo, bool tipoPista, int time, Semaforo semaforo, Reloj reloj, Emergencia emergencia){
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
    this->obstacleDamage(tipoPista);
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
    std::cout << "Colocando obstaculos en la pista normal..." << std::endl;
    std::cout << "Colocando conos..." << std::endl;
    std::cout << "Colocando pequeños charcos de agua..." << std::endl;
    std::cout << "Colocando llantas...\n" << std::endl;
    std::cout << "Colocando obstaculos en la pista todoterreno" << std::endl;
    std::cout << "Realizando pozas de agua..." << std::endl;
    std::cout << "Colocando troncos..." << std::endl;
    std::cout << "Cambiando desniveles..." << std::endl;
    std::cout << "Enlodando áreas..." << std::endl;    
    std::cout << "Colocando llantas...\n" << std::endl;
}

void PistaKarts::obstaculosKid(){
    std::cout << "Colocando obstaculos en la pista normal..." << std::endl;
    std::cout << "Colocando conos..." << std::endl;
    std::cout << "Colocando pequeños charcos de agua..." << std::endl;
    std::cout << "Colocando llantas...\n" << std::endl;
}


void PistaKarts::obstacleDamage(bool tipoPista){
    /**Ver si ocurrió algún daño a los obstaculos de la pista*/
    std::string obstaculosNormal[] = {"Conos", "Charcos de agua", "Llantas"};
    std::string obstaculosTodoterreno[] = {"Poza de agua", "Troncos", "Desniveles", "Área enlodada", "Llantas"};
    std::string motivo;
    // Mapa de motivos de daño
    std::unordered_map<int, std::string> normalDamage;
    std::unordered_map<int, std::string> offRoadDamage;
    // Inicializar los mapas de los motivos de daño
    normalDamage[0] = "Choque";
    normalDamage[1] = "Derrape";
    normalDamage[2] = "Choque";

    offRoadDamage[0] = "Derrape";
    offRoadDamage[1] = "Choque";
    offRoadDamage[2] = "Derrape";
    offRoadDamage[3] = "Desliz";
    offRoadDamage[4] = "Choque";
    int damage;
    int randVal = rand()%20;
    if (randVal >= 10){
        // Ocurrió un daño en la pista
        if (tipoPista){
            // Daño en la pista normal
            damage = rand()%3;
            std::cout << "Ocurrió un daño con el obstáculo " << obstaculosNormal[damage] << " en la pista normal" << std::endl;
            std::cout << "Motivo: " << normalDamage[damage] << "\n" << std::endl;
        }else{
            damage = rand()%5;
            // Daño en la pista todoterreno
            std::cout << "Ocurrió un daño con el obstáculo " << obstaculosTodoterreno[damage] << " en la pista todoterreno" << std::endl;
            std::cout << "Motivo: " << offRoadDamage[rand()%5] << "\n" << std::endl;
        }
    }
}
