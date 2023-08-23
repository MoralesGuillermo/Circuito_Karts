#pragma once
#include <sys/sem.h>

struct semun{
    int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *__buf;
};

class Semaforo{
    public:
        Semaforo(int val, int semSize);
        bool inicializarSemaforo();
        int aumentar();
        int decrementar();
        int kill();
        
    private:
        key_t clave;
        bool inicializado;
        struct sembuf verde;
        struct sembuf rojo;
        struct semun arg;
        int semId;
        int semSize;
};