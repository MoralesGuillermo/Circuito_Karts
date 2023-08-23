// Clase semáforo binario
#include "semaforo.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>


Semaforo::Semaforo(int keyval, int semSize){
    /**Constructor de semáforo*/
    // Inicializar la clave del semáforo
    this->clave = ftok("/bin/ls", keyval| IPC_CREAT);
    this->inicializado = false;
    this->verde = {0, 1, 0};
    this->rojo = {0, -1, 0};
    // Definir el tamaño del semáforo (Máximo número de procesos)
    this->semSize = semSize;
}

bool Semaforo::inicializarSemaforo(){
    if (this->clave == -1){
        std::cout << "No se pudo conseguir clave para el semáforo" << std::endl;
        return false;
    }
    // Inicializar el semáforo
    // (Se utilizan banderas de los semáforos: IPC_CREAT, IPC_EXCL, S_IRUSR, S_IWUSR)
    this->semId = semget(IPC_PRIVATE, 1, IPC_CREAT|IPC_EXCL|S_IRUSR|S_IWUSR);
    if (this->semId == -1){
        // No se pudo inicializar el semáforo
        std::cout << "No se pudo definir un ID para el semáforo" << std::endl;
        return false;
    }
    // Definir el valor del semáforo
    semctl(this->semId, 0, SETVAL, this->semSize);
    this->inicializado = true;
    return true;
}

int Semaforo::aumentar(){
    /** Aumentar el valor del semáforo*/
    if (this-> inicializado){
        return semop(this->semId, &this->verde, 1);
    }
    return -1;
}

int Semaforo::decrementar(){
    /**Decrementar el valor del semáforo*/
    if (this->inicializado){
        return semop(this->semId, &this->rojo, 1);
    }
    return -1;
}

int Semaforo::kill(){
    // Eliminar el semaforo
    if (this->inicializado){
        return semctl(this->semId, 0, IPC_RMID);
    }
    std::cout << "NO SE PUEDE ELIMINAR UN SEMÁFORO NO INICIALIZADO" << std::endl;
    return -1;
}
