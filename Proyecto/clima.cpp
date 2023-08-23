/**Implemenatación de la clase Clima*/
#include "clima.h"
#include <iostream>
#include <unistd.h>


int Clima::verificarClima(){
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
    if (climaAleatorio >= 7){
        // Ocurre un mal clima
        std::cout << "El clima no es óptimo para abrir el circuito" << std::endl;
        std::cout << "Tipo de clima: " << climasMalos[rand()%2] << std::endl;
        std::cout <<"NO SE ABRIRÁ EL CIRCUITO HOY\n" << std::endl;
        return -1;
    }
    std::cout << "El clima es óptimo para abrir el circuito" << std::endl;
    std::cout << "Tipo de clima: " << climasBuenos[rand()%2] << "\n" <<std::endl;
    return 1;
}
