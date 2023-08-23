/**Definición de la clase Reloj*/
#include "reloj.h"
#include <iostream>

void Reloj::tiempoRecorrido(int i, int time){
    /**Mostar el tiempo recorrido por el corredor*/
    std::cout << "Tiempo recorrido del corredor " << i <<  ": "<< time*3 << " minutos\n" << std::endl;
}

void Reloj::tiempoRecorridoGrupos(int i, int grupo, int time){
    /**Mostar el tiempo recorrido por el corredor*/
    std::cout << "Tiempo recorrido del corredor " << i << " del grupo "<< grupo << ": " << time*3 << " minutos\n" << std::endl;
}

void Reloj::tiempoEspera(int i, int maxCorredores, Semaforo semaforo){
    /**Decidir si el tiempo de espera máximo fue superado*/
    // Ejecutar función solo para los corredores que han tenido que esperar
    if (i > maxCorredores){
        int tiempoEspera = rand()%10;
        if (tiempoEspera > 7){
            // Tiempo de espera máximo superado
            std::cout <<"El tiempo de espera de la persona " << i << " ha sido superado" << std::endl;
            std::cout << "Persona " << i << " abandona el circuito de karts" << std::endl;
            // Liberar el semaforo
            semaforo.aumentar();
            exit(0);
        }
    }
}
