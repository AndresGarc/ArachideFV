#ifndef _ARMA
#define _ARMA
//#include <SFML/Graphics.hpp>
//#include <iostream>
#include "Objeto.h"

//using namespace sf;
//using namespace std;

class Arma : public Objeto{
    private:
		int tipoarma;
	public:
		Arma(int arma,int posx,int posy,bool estado):Objeto(arma,posx,posy,estado){ //3 tipos de int arma
			 if(arma==0){//bate
				 tipoarma=0;
			 }
			 else if(arma==1){//latigo
				 tipoarma=1;
			 }
			 else if(arma==2){ //puño
				 tipoarma=2;
			 }
			 else{
				x=0 * 24,y=2*16,ancho=24,largo=24;
				sprite_objeto->setOrigin(ancho/2,largo/2);
				sprite_objeto->setTextureRect(sf::IntRect(x,y,ancho,largo));
				rect.setOrigin(ancho/2,largo/2);
				//Cojo el sprite que me interesa por defecto del sheet
				rect.setSize(Vector2f(ancho,largo));
				tipoarma=0;
			 }
		}
		virtual ~Arma(); //Virtual por si acaso
		int get_tipoArma();
};
#endif