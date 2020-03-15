#ifndef _VIDA
#define _VIDA
//#include <SFML/Graphics.hpp>
//#include <iostream>
#include "Objeto.h"


//using namespace sf;

class Vida : public Objeto{

	private:
		bool tipovida; //Vida entera o mitad
    
	public:
		Vida(int vida,int posx,int posy,bool estado):Objeto(vida,posx,posy,estado){
			if(vida==3){ //medio cora
				tipovida=false;
			}else if(vida==4){ //corazon entero
				tipovida=true;
			}
			else{ //corazon entero
				x=3 * 16,y=2*16,ancho=16,largo=16;
				sprite_objeto->setOrigin(ancho/2,largo/2);
				sprite_objeto->setTextureRect(sf::IntRect(x,y,ancho,largo));
				rect.setOrigin(ancho/2,largo/2);
				//Cojo el sprite que me interesa por defecto del sheet
				rect.setSize(Vector2f(ancho,largo));
				tipovida=true;
			}
		}
		virtual ~Vida(); //Virtual por si acaso 
		bool get_tipoVida();
};
#endif