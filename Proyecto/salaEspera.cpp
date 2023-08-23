
/**Implementación de la clase SalaEspera*/
#include "salaEspera.h"
#include <iostream>

void SalaEspera::ingresarPersona(int i){
    std::cout << "Ingresando persona "<< i <<" a sala de espera" << std::endl;
    std::cout <<"Persona " << i <<" ha ingresado a la sala de espera\n" << std::endl;
}
void SalaEspera::ingresarPersonaGrupos(int i, int grupo){
    std::cout << "Ingresando persona "<< i << " del grupo: " << grupo <<" a sala de espera" << std::endl;
    std::cout <<"Persona " << i << " del grupo " << grupo << "  ha ingresado a la sala de espera\n" << std::endl;
}



