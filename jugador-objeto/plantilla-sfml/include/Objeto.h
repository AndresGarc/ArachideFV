#ifndef _OBJETO
#define _OBJETO
#include <SFML/Graphics.hpp>
#include <iostream>
//#include <string>
//#include <sstream>

using namespace sf;
using namespace std;

class Objeto{
    
	protected:
        Texture * textura_objeto;
        Sprite  * sprite_objeto;
		Vector2f  pos_objeto,pos_rect;
		bool estadoObjeto; //Recoger(true) o interactuar(false)
		RectangleShape rect;
		int x,y,ancho,largo;
		
	public:
	 	Objeto(int objeto,int posx,int posy,bool estado);
		virtual ~Objeto();
        Sprite get_Sprite();
		RectangleShape get_SpriteRect();
		void set_posicion(Vector2f posicion);
		Vector2f get_posicion();
		void set_sprite(IntRect rect);
		bool getEstadoObjeto(); //Si es para recoger true
		void setEstadoObjeto(); //Antes de borrar el objeto , para darle mas exactitud xD aunque no servira ya que se eliminara
		//Si un objeto esta abierto o cerrado : si veo que son muchos pondre aqui sus metodos y si son pocos en sus subclases(como el cofre)
		
};
#endif