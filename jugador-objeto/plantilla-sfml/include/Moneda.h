#ifndef _MONEDA
#define _MONEDA
//#include <SFML/Graphics.hpp>
//#include <iostream>
#include "Objeto.h"


//using namespace sf;

class Moneda : public Objeto{ //Para no enviar ruta spritemoneda en constructor Objeto y saber si es Moneda por algun motivo en el futuro
    private:
		int moneda=5;
	public:
		Moneda(int posx,int posy,bool estado):Objeto(5,posx,posy,estado){
			//moneda = this->moneda;
		}
		virtual ~Moneda(); //Virtual por si acaso
};
#endif