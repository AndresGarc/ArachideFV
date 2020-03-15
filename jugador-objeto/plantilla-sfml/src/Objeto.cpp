//#include <SFML/Graphics.hpp>
//#include <iostream>

#include "../include/Objeto.h"


Objeto::Objeto(int objeto,int posx,int posy,bool estado){ //Por defecto el objeto a crear es moneda
   
    switch(objeto){
      case 0: //bate
        x=0 * 24,y=2*16,ancho=24,largo=24;
        break;
      case 1: //latigo
        x=1 * 24,y=2*16,ancho=24,largo=24;
        break;
      case 2: //puño
        x=1 * 24,y=56,ancho=24,largo=24;
        break;
      case 3: //medio cora
        x=2 * 24,y=56,ancho=16,largo=16;
        break;
      case 4: //entero cora
        x=3 * 16,y=2*16,ancho=16,largo=16;
        break;
      case 5: //moneda
        x=0 * 24,y=1*56,ancho=24,largo= 24;
        break;
      case 6: //cofre cerrado
        x=0*16,y=0*16,ancho=2*16,largo=2*16;
        break;
      case 7: //cofre abierto
        x=2*16,y=0*16,ancho=2*16,largo=2*16;
        break;
      default : //Moneda
        x=0 * 24,y=1*56,ancho=24,largo= 24;
        break;
    }
    //Cargo la imagen donde reside la textura del sprite
    textura_objeto=new Texture();
    textura_objeto->loadFromFile("sprites/5.png");
    //Y creo el spritesheet a partir de la imagen anterior
    sprite_objeto=new Sprite(*textura_objeto);
    //Le pongo el centroide donde corresponde
    sprite_objeto->setOrigin(ancho/2,largo/2);
    sprite_objeto->setScale(2,2);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite_objeto->setTextureRect(sf::IntRect(x,y,ancho,largo));
    Vector2f vector= Vector2f(posx,posy);
    set_posicion(vector);

    estadoObjeto = estado;

    // Rectangulo hitbox
    rect.setOrigin(ancho/2,largo/2);
    //Cojo el sprite que me interesa por defecto del sheet
    rect.setSize(Vector2f(ancho,largo));
    rect.setFillColor(sf::Color::Blue);
    rect.scale(2,2);
}
Objeto::~Objeto(){
  //Primero el ultimo creado
  delete sprite_objeto;
  delete textura_objeto;
  // Vector no se borra ya que es estatico , solo se borra lo dinamico/puntero
}
Sprite Objeto::get_Sprite(){
    return *sprite_objeto;
}
RectangleShape Objeto::get_SpriteRect(){
    return rect;
}
void Objeto::set_sprite(IntRect rect){
   sprite_objeto->setTextureRect(rect);
}
Vector2f Objeto::get_posicion(){
  return pos_objeto;
}
void Objeto::set_posicion( Vector2f posicion){

  pos_objeto=posicion;
  sprite_objeto->setPosition(posicion);
  pos_rect=posicion;
  rect.setPosition(posicion);

}
bool Objeto::getEstadoObjeto(){ //Si es para recoger true
  return estadoObjeto;
}
void Objeto::setEstadoObjeto(){ //Antes de borrar el objeto , para darle mas exactitud xD aunque no servira ya que se eliminara
  estadoObjeto=false;
} 