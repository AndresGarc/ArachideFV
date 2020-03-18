#ifndef _COFRE
#define _COFRE
//#include <SFML/Graphics.hpp>
//#include <iostream>
#include <stdlib.h>
#include "Vida.h"
#include "Arma.h"
#include "Moneda.h"


//using namespace sf;

class Cofre : public Objeto{
    
	private:
        bool estadocofre; //Cerrado o abierto
		Objeto * contenido; //El contenido del cofre
	public:
		Cofre(int cofre,int posx,int posy,bool estado):Objeto(cofre,posx,posy,estado){ //Dos tipos de int cofre
			 if(cofre==6){ //Cerrado
				 estadocofre=true;
			 }else if(cofre==7){//Abierto
				 estadocofre=false;
			 }
			 else{ //Cerrado por defecto
				x=0*16,y=0*16,ancho=2*16,largo=2*16;
				sprite_objeto->setOrigin(ancho/2,largo/2);
				sprite_objeto->setTextureRect(sf::IntRect(x,y,ancho,largo));
				rect.setOrigin(ancho/2,largo/2);
				//Cojo el sprite que me interesa por defecto del sheet
				rect.setSize(Vector2f(ancho,largo));
				estadocofre=true;
				 
			 }
			 srand (time(NULL));//Valor distinto cada vez que se ejecute programa
			 //int v1 = 3, //1 al 4
			 int v1 = rand()%3+1, //1 al 4
			 v2 = rand()%1+1, //1 al 2
			 v3 = rand()%1+1; //1 al 2
			 switch(v1){
				 case 1:
				 	//Aqui iria un Factory de esos con el arma,vida etc
					std::cout << "Arma:";
					if(v2 ==1){
						std::cout << "bate" <<std::endl;
						
					}else{ //2
						std::cout << "latigo" <<std::endl;
					}
					contenido = new Arma(v2-1,260,240,true);
					break;
				 case 2:
					contenido = new Moneda(100,240,true);
					std::cout << "Moneda" <<std::endl;
					break;
				 case 3:
					int vida;
				 	if(v3 ==1){ //Vida entera
						vida=4;
					}
					else{ //Media vida
						vida=3;
					}
					contenido = new Vida(vida,240,240,true);
					std::cout << "Vida" <<std::endl;
					break;
				 case 4:
				 std::cout << "Nada" <<std::endl;
					contenido =NULL;
					break;
			 }
		}
		virtual ~Cofre(); //Virtual por si acaso
		//Antes el objeto ha de estar en estado interactuar
		bool getEstadoCofre();
		void setEstadoCofre();
		Objeto* getContenido();
		void setContenido(); //quitar contenido
        
};
#endif