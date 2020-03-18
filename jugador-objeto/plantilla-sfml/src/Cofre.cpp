//#include <SFML/Graphics.hpp>
//#include <iostream>
#include "../include/Cofre.h"

Cofre::~Cofre(){
    //Llama al de objeto
    delete contenido;
}
//Antes el objeto ha de estar en estado interactuar
bool Cofre::getEstadoCofre(){
    return estadocofre;
} //Cerrado -> true
void Cofre::setEstadoCofre(){
    estadocofre=false;
} //Abierto -> false
Objeto* Cofre::getContenido(){
    return contenido;
} 
void Cofre::setContenido(){
    contenido=NULL;
} 