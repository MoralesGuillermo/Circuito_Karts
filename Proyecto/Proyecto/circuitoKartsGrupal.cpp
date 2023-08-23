/**Lógica del circuito de karts con implementación de grupos*/
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
critElem seccionCritica = {10, 10, 0, 0, 0, false};

int main(){
    pid_t pid;
    Semaforo semTaquilla(0, 1);
    Semaforo semSalaEspera(0, 3);
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
    int grupos = 4;
    int grupoKids = 3;
    // Tiempo del corredor
    int runTime;
    bool tipoPista;
    bool turno = true;
    // Variable para el turno de los adultos y los niños
    // Tamaño del grupo
    int  groupSize;

    // Inicializar el circuito de karts. Verificar que el circuito puede abrirse 
    // Verificar seguridad y obstáculos de la pista
    // Inicializar semilla para elementos aleatorios de la revisión y el tamaño del grupo
    srand(time(NULL));
    if (clima.verificarClima() == -1){
        return -1;
    }

    std::cout << "TURNO DE LOS ADULTOS" << std::endl;
    seguridad.seguridadPista();
    seguridad.seguridadKart(4);
    pistaKarts.obstaculos();
    for (int i = 0; i < grupos; i++){
        // Generar procesos en paralelo
        pid = fork(); 
        if (pid == -1){
            std::cout << "Error creando hijo "<< i <<" del proceso" << std::endl;
            return -1;
        }
        // Inicializar semilla única para generar números aleatorios en cada proceso
        if (pid == 0){
            srand(time(NULL) ^ getpid()); 
            groupSize = rand()%3+1;
            std::cout << "TAMAÑO DEL GRUPO " << i << ": " << groupSize << "\n" << std::endl;
            sleep(1);
            for (int j = 0; j < groupSize; j++){
                // Vender boleto en taquilla
                semTaquilla.decrementar();
                taquilla.venderBoletoGrupos(j, i);
                // Definir un tiempo para el corredor
                runTime = rand() % 7 + 1;
                semTaquilla.aumentar();

                // Ingresar persona a sala de espera
                semSalaEspera.decrementar();
                salaEspera.ingresarPersonaGrupos(i, j);
                sleep(2);

                // Ingresar persona a la pista (Realizar todas las acciones de la pista)
                semPista.decrementar();
                tipoPista = pistaKarts.ingresarPistaGrupos(i, j);
                semSalaEspera.aumentar();
                pistaKarts.ingresarKartGrupos(i, j, turno);
                pistaKarts.correrGrupos(i, j, runTime, tipoPista, semPista, reloj, emergencia);
                pistaKarts.regresarKartGrupos(i, j);
            
                semPista.aumentar(); 
            }
            std::cout << "GRUPO " << i << " HA FINALIZADO\n" << std::endl;
            exit(0);
        }
    }
    // Proceso Padre espera a que todos sus procesos hayan culminado
    while (wait(NULL) > 0);

    std::cout << "TURNO DE LOS NIÑOS\n" << std::endl;
    turno = false;
    seguridad.seguridadPista();
    seguridad.seguridadKart(4);
    pistaKarts.obstaculosKid();
    for (int i = 0; i < grupoKids; i++){
        // Generar procesos en paralelo
        pid = fork(); 
        if (pid == -1){
            std::cout << "Error creando hijo "<< i <<" del proceso" << std::endl;
            return -1;
        }
        // Inicializar semilla única para generar números aleatorios en cada proceso
        if (pid == 0){
            srand(time(NULL) ^ getpid()); 
            groupSize = rand()%3+1;
            std::cout << "TAMAÑO DEL GRUPO " << i << ": " << groupSize << "\n" << std::endl;
            sleep(1);
            for (int j = 0; j < groupSize; j++){
                // Vender boleto en taquilla
                semTaquilla.decrementar();
                taquilla.venderBoletoGrupos(j, i);
                // Definir un tiempo para el corredor
                runTime = rand() % 7 + 1;
                semTaquilla.aumentar();

                // Ingresar persona a sala de espera
                semSalaEspera.decrementar();
                salaEspera.ingresarPersonaGrupos(i, j);
                sleep(2);

                // Ingresar persona a la pista (Realizar todas las acciones de la pista)
                semPista.decrementar();
                pistaKarts.ingresarPistaKidGrupos(i, j);
                semSalaEspera.aumentar();
                pistaKarts.ingresarKartGrupos(i, j, turno);
                pistaKarts.correrGrupos(i, j, runTime, true, semPista, reloj, emergencia);
                pistaKarts.regresarKartGrupos(i, j);
                semPista.aumentar(); 
            }
            std::cout << "GRUPO " << i << " HA FINALIZADO\n" << std::endl;
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
