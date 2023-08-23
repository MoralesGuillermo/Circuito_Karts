/**Ejecución del proyecto considerando grupos*/
#include "semaforo.cpp"
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


class Taquilla{
    public:
        Taquilla(struct critElem* critsec){
            this->critSec = critsec;
        }
        void venderBoleto(int i){
            /**Simular la venta de un boleto*/
            // Retornar un número aleatorio entre el 0 y el 10
            std::cout << "Vendiendo boleto "<< i << "..." << std::endl;
            // TODO: DETERMINE HOW TO CHOOSE WHICH PERSON TYPE THE TICKET IS BEING SOLD
            (*critSec).adultosEntrada = (*critSec).adultosEntrada - 1;
            sleep(1);
            std::cout << "Boleto " << i << " vendido\n" << std::endl;
        }
        void venderBoletoGrupos(int i, int grupo){
            /**Simular la venta de un boleto*/
            // Retornar un número aleatorio entre el 0 y el 10
            std::cout << "Vendiendo boleto "<< i << " del grupo: " << grupo << "..." << std::endl;
            // TODO: DETERMINE HOW TO CHOOSE WHICH PERSON TYPE THE TICKET IS BEING SOLD
            (*critSec).adultosEntrada = (*critSec).adultosEntrada - 1;
            sleep(1);
            std::cout << "Boleto " << i << " del grupo: " << grupo << " vendido\n" << std::endl;
        }
    private:
        struct critElem* critSec;
        void esperarEmpleado(){
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
};

class SalaEspera{
    public:
        SalaEspera(struct critElem* critsec){
            this->critSec = critsec;            
        }
        void ingresarPersona(int i){
            std::cout << "Ingresando persona "<< i <<" a sala de espera" << std::endl;
            (*critSec).salaEspera++;
            std::cout <<"Persona " << i <<" ha ingresado a la sala de espera\n" << std::endl;
        }
        void ingresarPersonaGrupos(int i, int grupo){
            std::cout << "Ingresando persona "<< i << " del grupo: " << grupo <<" a sala de espera" << std::endl;
            std::cout <<"Persona " << i << " del grupo " << grupo << "  ha ingresado a la sala de espera\n" << std::endl;
        }

    private:
        struct critElem* critSec;

};

class Reloj{
    public:
        void tiempoRecorrido(int i, int time){
            /**Mostar el tiempo recorrido por el corredor*/
            std::cout << "Tiempo recorrido del corredor " << i <<  ": "<< time*3 << " minutos\n" << std::endl;
        }

        void tiempoRecorridoGrupos(int i, int grupo, int time){
            /**Mostar el tiempo recorrido por el corredor*/
            std::cout << "Tiempo recorrido del corredor " << i << " del grupo "<< grupo << ": " << time*3 << " minutos\n" << std::endl;
        }

        void tiempoEspera(int i, int maxCorredores, Semaforo semaforo){
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
};

class Emergencia{
    /**Representación de una emergencia en el circuito*/
    public:
        void medica(int i, Semaforo semaforo){
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

        void medicaGrupos(int i, int grupo, Semaforo semaforo){
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

        void mecanica(int i){
            /**Simular el proceso para una emergencia mecánica*/
            std::cout << "Llevando kart del corredor " << i << " al taller" << std::endl;
            std::cout << "Se le da un kart de repuesto al corredor. Corredor " << i << " vuelve a la pista" << std::endl;
            std::cout <<  "Revisando kart del corredor "<< i <<"..." << std::endl;
            std::cout << "El kart será reparado entre semana\n" << std::endl;
        }

        void mecanicaGrupos(int i, int grupo){
            /**Simular el proceso para una emergencia mecánica*/
            std::cout << "Llevando kart del corredor " << i << " del grupo " << grupo << " al taller" << std::endl;
            std::cout << "Se le da un kart de repuesto al corredor. Corredor " << i << " del grupo " << grupo << " vuelve a la pista" << std::endl;
            std::cout <<  "Revisando kart del corredor "<< i << " del grupo " << grupo << "..." << std::endl;
            std::cout << "El kart será reparado entre semana\n" << std::endl;
        }
};



class PistaKarts{
    public:
        PistaKarts(struct critElem* critsec){
            this->critSec = critsec;
            this->kartAdulto = "Cilindrada alta";
            this->kartNino = "Cilindrada baja";      
        }
        void ingresarPista(int i){
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

        void ingresarPistaGrupos(int i, int grupo){
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

        void ingresarPistaKid(int i){
            std::cout << "Ingresando persona " << i <<" a Pista" << std::endl;
            std::cout << "Pista del corredor " << i << ": Normal" << std::endl;
            std::cout <<"Persona "<< i << " ha sido ingresada a Pista\n" << std::endl;
        }

        void ingresarPistaKidGrupos(int i, int grupo){
            std::cout << "Ingresando persona " << i << " del grupo "<< grupo << " a Pista" << std::endl;
            std::cout << "Pista del corredor " << i << " del grupo " << grupo << ": Normal" << std::endl;
            std::cout <<"Persona "<< i << " del grupo "<< grupo << " ha sido ingresada a Pista\n" << std::endl;
        }

        

        void ingresarKart(int i, bool turno){
            std::string tipo = turno? this->kartAdulto: this->kartNino;
            std::cout << "Persona " << i << " ingresa a kart tipo: " << tipo << std::endl;
            std::cout << "Persona " << i << " ha ingresado al kart\n" << std::endl;
        }

        void ingresarKartGrupos(int i, int grupo, bool turno){
            std::string tipo = turno? this->kartAdulto: this->kartNino;
            std::cout << "Persona " << i << " del grupo "<< grupo <<" ingresa a kart tipo: " << tipo << std::endl;
            std::cout << "Persona " << i <<  " del grupo " << grupo <<" ha ingresado al kart\n" << std::endl;
        }

        void correr(int i, int time, Semaforo semaforo, Reloj reloj, Emergencia emergencia){
            /**Simlular la carrera de un corredor
             * Dormir el proceso una cantidad dada de tiempo
            */
            int randVal;
            std::cout << "Corredor " << i << " esta corriendo..." << std::endl;
            sleep(time);
            randVal = rand()%20;
            if (randVal > 18){
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

        void correrGrupos(int i, int grupo, int time, Semaforo semaforo, Reloj reloj, Emergencia emergencia){
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

        void regresarKart(int i){
            /**Simular el retorno del kart a la estación*/
            std::cout << "Corredor " << i << " ha retornado el kart\n" << std::endl;;
        }

        void regresarKartGrupos(int i, int grupo){
            /**Simular el retorno del kart a la estación*/
            std::cout << "Corredor " << i << " del grupo "<< grupo << " ha retornado el kart\n" << std::endl;;
        }

        void obstaculos() {
            std::cout << "Obstaculos en la pista han sido colocados\n" << std::endl;
        }

    private:
        struct critElem* critSec;
        std::string kartAdulto;
        std::string kartNino;

};

class Seguridad{
    /**Modelo de la seguridad de la pista de karts*/
    public:
        void seguridadKart(int maxKarts){
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

        void seguridadPista(){
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

    private:
        int randomSecurity(int maxElem){
            /**Simulador para verificación aleatoria de un elemento de seguridad*/
            if (rand()%10 == 3){
                return (rand()% maxElem + 1);
            }
            return -1;
        }

        void cambiarElemento(std::string msg, int elem){
            /**Simular el cambio de un elemento dañado*/
            std::cout << msg << elem << " esta dañado" << std::endl;
            std::cout << msg << elem << " ha sido reparado" << std::endl;
        }

};


class Clima{
    public:
        int verificarClima(){
            /**Verificar si el clima es adecuado para abrir el circuito*/
            std::string climasMalos[] = {"Tormenta", "Nevado"};
            std::string climasBuenos[] = {"Despejado", "Nublado"};
            std::cout << "Verificando clima..." << std::endl;
            std::cout << "Escuchando pronóstico de la radio..." << std::endl;
            sleep(1);
            std::cout << "Investigando páginas web..." << std::endl;
            std::cout << "Investigando en el sitio del centro meteorológico nacional..." << std::endl;
            sleep(2);
            int climaAleatorio = rand() % 10;
            // TODO: DEFINIR SI SE AGREGARÁ EL TIPO DE CLIMA
            if (climaAleatorio >= 7){
                std::cout << "El clima no óptimo para abrir el circuito" << std::endl;
                std::cout << "Tipo de clima: " << climasMalos[rand()%2] << std::endl;
                std::cout <<"NO SE ABRIRÁ EL CIRCUITO HOY\n" << std::endl;
                return -1;
            }
            std::cout << "El clima es óptimo para abrir el circuito" << std::endl;
            std::cout << "Tipo de clima: " << climasBuenos[rand()%2] << "\n" <<std::endl;
            return 1;
        }
    private:
};

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
    Taquilla taquilla(&seccionCritica);
    SalaEspera salaEspera(&seccionCritica);
    PistaKarts pistaKarts(&seccionCritica);
    Seguridad seguridad;
    Clima clima;
    Reloj reloj;
    Emergencia emergencia;
    
    //Variables del sistema 
    int grupos = 4;
    int grupoKids = 3;
    // Tiempo del corredor
    int runTime;
    // Variable para el turno de los adultos y los niños
    bool turno = true;
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
                pistaKarts.ingresarPistaGrupos(i, j);
                semSalaEspera.aumentar();
                pistaKarts.ingresarKartGrupos(i, j, turno);
                pistaKarts.correrGrupos(i, j, runTime, semPista, reloj, emergencia);
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
                pistaKarts.correrGrupos(i, j, runTime, semPista, reloj, emergencia);
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