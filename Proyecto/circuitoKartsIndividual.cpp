/**Lógica principal del programa*/
/*
* UNIVERSIDAD NACIONAL AUTÓNOMA DE HONDURAS
* FACULTAD DE INGENIERÍA
* CARRERA DE INGENIERÍA DE SISTEMAS
* SISTEMAS OPERATIVOS I (II PAC 2023)
* PROYECTO: CIRCUITO DE KARTS
* INTEGRANTES:
* Danny Jamin Recarte Rivera 20211024790
* Fernando Javier Tercero Orellana 20201003991
* Hector Adalid Granados Cruz 20191900306
* Guillermo Daniel Martínez Morales 20211002682
* 
*/
/** Lógica principal de la pista de karts*/
#include "semaforo.cpp"
#include "clima.cpp"
#include "emergencia.cpp"
#include "pistaKarts.cpp"
#include "reloj.cpp"
#include "salaEspera.cpp"
#include "seguridad.cpp"
#include "Taquilla.cpp"

#include <iostream>
#include <wait.h>
#include <random>
#include <sys/sem.h>
#include <string>


struct critElem{
    int adultosEntrada;
    int ninosEntrada;
    int salaEspera;
    int corredoresAdultos;
    int corredoresNinos;
    bool corredorAdulto;
};

// Sección crítica
// Valores compartidos (Máximos de los semáforos)
critElem seccionCritica = {10, 10, 0, 0, 0, false};


int main(){
    pid_t pid;
    // Semáforos del sistema
    Semaforo semTaquilla(0, 1);
    Semaforo semSalaEspera(0, 6);
    Semaforo semPista(3, 4);

    // Inicializar semáforos del sistema
    semTaquilla.inicializarSemaforo();
    semSalaEspera.inicializarSemaforo();
    semPista.inicializarSemaforo();

    // Inicializar clases de los procesos del sistema
    Taquilla taquilla;
    SalaEspera salaEspera;
    PistaKarts pistaKarts;
    Seguridad seguridad;
    Clima clima;
    Reloj reloj;
    Emergencia emergencia;
    
    //Variables del sistema 
    int adultos = seccionCritica.adultosEntrada;
    int kids = seccionCritica.ninosEntrada;
    // Tiempo del corredor
    int runTime;
    // Variable para el turno de los adultos y los niños
    bool turno = true;

    // Inicializar semilla para elementos aleatorios de la revisión
    srand(time(NULL));
    if (clima.verificarClima() == -1){
        return -1;
    }

    std::cout << "TURNO DE LOS ADULTOS" << std::endl;
    // Inicializar el circuito de karts. Verificar que el circuito puede abrirse 
    // Verificar seguridad y obstáculos de la pista
    seguridad.seguridadPista();
    seguridad.seguridadKart(4);
    pistaKarts.obstaculos();
    for (int i = 0; i < adultos; i++){
        // Generar procesos hijo en paralelo
        pid = fork();  
        if (pid == -1){
            std::cout << "Error creando hijo "<< i <<" del proceso" << std::endl;
            return -1;
        }
        // Inicializar semilla única para generar números aleatorios en cada proceso
        srand(time(NULL) ^ getpid());      
        if (pid == 0){
            // Vender boleto en taquilla
            semTaquilla.decrementar();
            taquilla.venderBoleto(i);
            // Definir un tiempo para el corredor
            runTime = rand() % 7 + 1;
            semTaquilla.aumentar();

            // Ingresar persona a sala de espera
            semSalaEspera.decrementar();
            reloj.tiempoEspera(i, 4, semSalaEspera);
            salaEspera.ingresarPersona(i);
            sleep(2);

            // Ingresar persona a la pista (Realizar todas las acciones de la pista)
            semPista.decrementar();
            pistaKarts.ingresarPista(i);
            semSalaEspera.aumentar();
            pistaKarts.ingresarKart(i, turno);
            pistaKarts.correr(i, runTime, semPista, reloj, emergencia);
            pistaKarts.regresarKart(i);
            semPista.aumentar();

            exit(0);
        }
    }
    // Proceso Padre espera a que todos sus procesos hijo hayan culminado
    while (wait(NULL) > 0);

    std::cout << "TURNO DE LOS NIÑOS\n" << std::endl;
    turno = false;
    seguridad.seguridadPista();
    seguridad.seguridadKart(4);
    for (int i = 0; i < kids; i++){
        // Generar procesos en paralelo
        pid = fork();  
        if (pid == -1){
            std::cout << "Error creando hijo "<< i <<" del proceso" << std::endl;
            return -1;
        }
        // Inicializar semilla única para generar números aleatorios en cada proceso
        srand(time(NULL) ^ getpid());      
        if (pid == 0){
            // Vender boleto en taquilla
            semTaquilla.decrementar(); 
            taquilla.venderBoleto(i);
            // Definir un tiempo para el corredor
            runTime = rand() % 7 + 1;
            semTaquilla.aumentar();

            // Ingresar persona a sala de espera
            semSalaEspera.decrementar();
            reloj.tiempoEspera(i, 4, semSalaEspera);
            salaEspera.ingresarPersona(i);
            sleep(2);

            // Ingresar persona a la pista (Realizar todas las acciones de la pista)
            semPista.decrementar();
            pistaKarts.ingresarPistaKid(i);
            semSalaEspera.aumentar();
            pistaKarts.ingresarKart(i, turno);
            pistaKarts.correr(i, runTime, semPista, reloj, emergencia);
            pistaKarts.regresarKart(i);
            semPista.aumentar();

            exit(0);
        }
    }
    // Proceso Padre espera a que todos sus procesos hayan culminado
    while (wait(NULL) > 0);

    // Eliminar los semáforos
    semTaquilla.kill();
    semSalaEspera.kill();
    semPista.kill();
    std::cout << "Finalizado!" << std::endl;
    // Inicializar clases
    return -1;
}