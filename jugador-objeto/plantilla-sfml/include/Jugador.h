#ifndef _JUGADOR
#define _JUGADOR
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Sprite_arachide.h"
#include"Arma.h"
#include "Cofre.h"

using namespace sf;
enum estados{reposo, andando,corriendo,muerto};
enum direcciones{arriba, izq_arriba, der_arriba, derecha,   der_abajo,   izq_abajo, abajo,  izquierda};
enum armas{normal,bate,latigo};

using namespace std;

class Jugador: public Sprite_arachide{
    

	private:
      
		
		Vector2f  pos_jugador,pos_rect,pos_vida,pos_moneda,pos_arma;
		Texture *textura_vida, *textura_moneda,*textura_arma;
		Sprite * sprite_vida, *sprite_moneda,*sprite_arma;
		 int nummonedas;
		  Text texto;
		  Font fuente;
		  Arma * armaGigante;
	
		
	public:
		int numvidas;
		void atacar();
		RectangleShape cubo;
		RectangleShape arma1;
		RectangleShape arma2;
		RectangleShape arma3;
		RectangleShape rect;



		RectangleShape get_rec_jugador();

		Vector2f velocidad;
		float vel_desp;
		float vel_salto;
		void set_velocidad(Vector2f vel);
		Vector2i pos_sprite_jugador;
		bool caminando;
		bool saltando;
		bool atacando;
		void update();
		Jugador(int spr_clase, int cant_x1, int cant_y1, Vector2i fr_a);
        Sprite get_Sprite();
		void set_translacion(Vector2f translacion);
		void set_posicion(Vector2f posicion);
		void set_texture_jugador(String cadena);
		Vector2f get_posicion();
		void controles_jugador(Event event,Objeto * obj);
		
		//void seleccionar_frame();
		void animar_jugador();
		void seleccionar_velocidad();

		armas arma=normal;

		direcciones direccion = izquierda ; //direccion a la que mira el jugador

		//vidas jugador
		bool sumar_Vidas(bool tipovida);
		void quitar_Vida(int cant);
		void updateSFMLEvents();
		void set_posicionVida(Vector2f posicion);
		Sprite get_SpriteVida();
		void cambiaSpriteVida();
		void set_spriteVida(IntRect rect);

		//Monedas
		int get_Monedas();
		 Sprite get_SpriteMoneda();
		void set_posicionMoneda(Vector2f posicion);
		void monedasPorVida();
		
		//COFRE

		void abrir_Cofre(Objeto* obj);
		bool asignarContenido(Objeto * obj);
	
		//ARMA

    void set_posicionArma(Vector2f posicion);
	void set_spriteArma(IntRect recta);
	void cambiaSpriteArma();
	Sprite get_SpriteArma();


		//REnder jugador
		void render_jugador();
};

#endif