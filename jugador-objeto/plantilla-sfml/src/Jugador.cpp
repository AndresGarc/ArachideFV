#include "../include/Jugador.h"
#include "../include/Arachide.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;


Jugador::Jugador(int spr_clase, int cant_x1, int cant_y1, Vector2i fr_a){
    caminando=false;
    saltando=false;

  atacando=false;
    //REctangulos armas

    arma1.setSize(Vector2f(50,25));
    arma1.setFillColor(sf::Color::Green);
    arma2.setSize(Vector2f(25,25));
    arma2.setFillColor(sf::Color::Blue);
    arma3.setSize(Vector2f(75,25));
    arma3.setFillColor(sf::Color::White);


  //cargar textura
  set_sprite(spr_clase, cant_x1,cant_y1,fr_a);

    
    vel_desp=3;
    vel_salto=5;
    numvidas=0;
    
 Vector2f vector= Vector2f(320,240);
  



      // Rectangulo hitbox
    //rect.setOrigin(frame_size.x/2,frame_size.y/2);
  
    //Cojo el sprite que me interesa por defecto del sheet
    rect.setSize(Vector2f(frame_size.x,frame_size.y));
    rect.setFillColor(sf::Color::Blue);
    rect.scale(1,1);

  set_posicion(vector);
   
}

void Jugador::atacar(){
switch(arma){
  case normal:
    cubo = arma2;
  break;
  case bate:
    cubo = arma1;
  break;
  case latigo:
    cubo = arma3;
    
  break;



}
  if(arma==latigo){
      set_frame_y(2);
      cout<<"cambio a golpear latigo"<<endl;
  }

if(direccion==derecha)
    cubo.setPosition(pos_jugador.x,pos_jugador.y);
else
    cubo.setPosition(pos_jugador.x-55,pos_jugador.y);
    

}





void Jugador::set_texture_jugador(String cadena){
  set_texture(cadena);
  if(arma==latigo){
    //set_frame_y(2);
  }
   
}

void Jugador::set_velocidad(Vector2f vel){
  velocidad=vel;
}



void Jugador::animar_jugador(){
  if(!saltando){
      animar_frame();
  }
}



Sprite Jugador::get_Sprite(){
    return *sprite_jugador;

}


Vector2f Jugador::get_posicion(){
  return pos_jugador;

}

//esta no se esta usando esta te teletransportaa
  void Jugador::set_posicion( Vector2f posicion){

    pos_jugador=posicion;
    sprite_jugador->setPosition(posicion);

    pos_rect=posicion;
    rect.setPosition(posicion);

}


//modifica la posicion del jugador
  void Jugador::set_translacion( Vector2f translacion){
    pos_jugador+=translacion;
    pos_rect+=translacion;
   
    rect.setPosition(pos_rect);
    sprite_jugador->setPosition(pos_jugador);

}


//actualiza fisica del jugador
void Jugador::update(){
  if(caminando){
      seleccionar_velocidad();
      set_translacion(velocidad);
  }
 
}



void Jugador::seleccionar_velocidad(){

  switch (direccion)//segun direccion a la que voy se le asigna una velocidad
  {
    case arriba:
        velocidad=Vector2f(0,-vel_salto);
    
    break;

    case abajo:
        velocidad=Vector2f(0,vel_desp);
    break;

    case izquierda:
        //pos_sprite_jugador.y=0; 
        set_frame_y(0);
        velocidad=Vector2f(-vel_desp,0);
        break;

    case derecha:
     //pos_sprite_jugador.y=1;
        set_frame_y(1);

      velocidad=Vector2f(vel_desp,0);
    break;
    case izq_arriba:
      velocidad=Vector2f(-vel_desp,-vel_salto);
    break;
    case izq_abajo:
      velocidad=Vector2f(-vel_desp,vel_desp);
    break;

    case der_arriba:
      velocidad=Vector2f(vel_desp,-vel_salto);
    break;
    case der_abajo:
      velocidad=Vector2f(vel_desp,vel_desp);
    break;
  }

}


void Jugador::updateSFMLEvents(){


   
      float j1x =pos_jugador.x, j1y=pos_jugador.y;

      if(Arachide::getInstance()->getObjetos().size() > 0){ //Si hay objetos
        int cont = 0,objx, objy;
        Objeto * obj;
        bool cantidadobjetomaximo = false; //Ej ya tienes maximo de vida etc no puedes coger objeto
   
        Vida * vida;
        while(cont < Arachide::getInstance()->getObjetos().size()){ //Recorrer objetos sala
          obj = Arachide::getInstance()->getObjetos()[cont];
          objx = obj->get_posicion().x , objy = obj->get_posicion().y;
          //Empezar a comparar jugador con objeto
                  
        
              if(rect.getGlobalBounds().intersects(obj->get_SpriteRect().getGlobalBounds())){
                  std::cout << " X/Y de j1 es " << j1x <<"/"<<j1y<< " X/Y de obj es "<< objx <<"/" << objy <<std::endl;
                if(obj->getEstadoObjeto()){ //Si es para recoger
                /*
                  if(dynamic_cast<Moneda*>(obj)){ //Si es moneda
                    nummonedas++;
                    std::cout << " y tienes " << nummonedas << " monedas." << std::endl;
                  }
                  else */
                  if(dynamic_cast<Vida*>(obj)){ //Si es vida
                    vida = dynamic_cast<Vida*>(obj);
                    cantidadobjetomaximo = sumar_Vidas(vida->get_tipoVida());
                  }/*
                  else if(dynamic_cast<Arma*>(obj)){ //Si es arma
                      //arma = (Arma*)&obj;
                      arma = dynamic_cast<Arma*>(obj);
                      this->arma = arma;
                      
                      std::cout << " Has cogido un arma de tipo " << this->arma->get_tipoArma() <<endl;
                  }
                  else if(!dynamic_cast<Cofre*>(obj)){ //Si es objeto
                      std::cout << " Has cogido un objeto" << std::endl;
                  }*/
                  if(!cantidadobjetomaximo){ //Puedes recoger este objeto si no tienes su maximo,osea de vida
                     obj->setEstadoObjeto();
                    Arachide::getInstance()->eraseObjetosRecoger(obj);
                    //Por si acaso:
                    delete obj; //posicion memoria libre
                    obj = NULL; //ponerla a null
                    cout<<"se supone que se eliminan"<<endl;
                    
                  }
                  cantidadobjetomaximo = false; //Se reinicia
                }
                /*
                else{ //Para interactuar
                  if(Arachide::getInstance()->event.type == sf::Event::KeyPressed){ //Interactuar con alguna tecla
                    if(Arachide::getInstance()->event.key.code==sf::Keyboard::E){ //Para evitar que avance doble
                        
                            




                    }
                  }
                }
                */
              }
       
          cont++;
        }
      }
    //}
  
}





bool Jugador::sumar_Vidas(bool tipovida){

  bool completo=false;
  if(numvidas <6){ //1 2 3 4 5 6
    if(tipovida){//Si es vida entera;vida null para aumentar vida en modo tradeo
      numvidas+=2;
      if(numvidas>6){ //Si tienes 2 corazones y medio y le sumas uno entero te rellena el restante; si no lo pones en el switch no se actualiza
        numvidas=6;
      }
    }
    else{ //Si es media vida
      numvidas++;
    }
    float mostrarvida=(float)numvidas/2;
    std::cout << " y tienes " << mostrarvida << " vidas." << std::endl;
  }else{ 
    if(tipovida){
      std::cout << "Es vida entera, aun así";
    }
    else{
      std::cout << "Es media vida , aun así";
    }
    std::cout << " ya has alcanzado la vida máxima" << std::endl;
    completo=true;
  }
  return completo;
}



RectangleShape Jugador::get_rec_jugador(){
  return rect;
}