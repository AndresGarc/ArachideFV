#ifndef _ARACHIDE
#define _ARACHIDE
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Jugador.h"
#include "Vida.h"
#include "Objeto.h"

using namespace sf;

class Arachide{
    

	private:
        int kVel;
		Jugador * j1;

		//SINGLETON
		static Arachide* pinstance;
		//virtual ~Arachide();
		
		//alguien lo usara
		//Arachide(const Arachide&);
		//Arachide&operator= (const Arachide &);

		RenderWindow *window;		 
		vector<Objeto *> objetos ; //objetos a recoger;cuando se pase de sala se vacia
		Arachide();
		 float groundHeight;
    	 float gravitySpedd;
		  Clock relojico,relojico2,relojico3;
		  float timeAnim,timeAnim2,timeAttack;

	public:
	
		void jugar();
		void iniciar();
		void inicializacion();
		void renderArachide();
		void updateArachide();
		Event event;
		
		void controles(Event event);
		void controles2(Event event);

		void procesar_logica();
		bool teclas_j1[5];//izq der arriba y abajo
		float altura_personaje;

		int fps;
		Clock * reloj1;
		Time * cronometro1;

		//SINGLETON
		static Arachide* getInstance();

		RenderWindow* get_Window();
		Event get_event();

		vector<Objeto*> getObjetos();
		void eraseObjetosRecoger(Objeto *o);
};

#endif