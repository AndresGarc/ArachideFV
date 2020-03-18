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

    //HUD jugador
    textura_vida=new Texture();
    textura_vida->loadFromFile("sprites/8.png");
    //Y creo el spritesheet a partir de la imagen anterior
    sprite_vida=new Sprite(*textura_vida);
    //Le pongo el centroide donde corresponde
    sprite_vida->setOrigin(96/2,32/2);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite_vida->setTextureRect(sf::IntRect(0 * 96, 0*32, 96,32));
    // Lo dispongo en el centro de la pantalla
    
    set_posicionVida(Vector2f(60,50));

    textura_moneda=new Texture();
    textura_moneda->loadFromFile("sprites/8.png");    
    sprite_moneda=new Sprite(*textura_moneda);    
     sprite_moneda->setOrigin(32/2, 32/2);  
    sprite_moneda->setTextureRect(sf::IntRect(0 * 32, 4*32, 32, 32));      
    set_posicionMoneda(Vector2f(200,50));

     if (!fuente.loadFromFile("FreeMono.ttf"))
    {
      std::cout << "ERROR FUENTE" <<std::endl;
    }
	  texto.setString(std::to_string(nummonedas));
	// Asignamos la fuente que hemos cargado al texto
	  texto.setFont(fuente);
	// Tamaño de la fuente
	  texto.setCharacterSize(20);
    texto.setOrigin(texto.getLocalBounds().width/2,texto.getLocalBounds().height/2);
	// Posición del texto
	  texto.setPosition(235, 45);
	// Lo rotamos un poco
	  //texto.rotate(20);
    texto.setColor(sf::Color::White);

//Arma
//Creo que mejor poner sprites barra junto al de objetos y creandome el objeto evito lo de abajo
    textura_arma=new Texture();
    textura_arma->loadFromFile("sprites/8.png");
    //Y creo el spritesheet a partir de la imagen anterior
    sprite_arma=new Sprite(*textura_arma);
    //Le pongo el centroide donde corresponde
    sprite_arma->setOrigin(24/2,24/2);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite_arma->setTextureRect(sf::IntRect(80, 128, 24, 24)); //Puño por defecto
    // Lo dispongo en el centro de la pantalla
    
    set_posicionArma(Vector2f(150,50));

    //Lo de arriba sobraria si lo hiciera de otra forma
    armaGigante = new Arma(2,260,240,true);


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

//Funcion ivy
void Jugador::updateSFMLEvents(){
  /*
    while (window->pollEvent(event)) {

          switch(event.type){

            //Si se recibe el evento de cerrar la ventana la cierro
            case sf::Event::Closed:
              window->close();
              break;
                  //Verifico si se pulsa alguna tecla de movimiento
            case sf::Event::KeyPressed:    
                  controles(event,NULL);//pulsar tecla
            break;
            case sf::Event::KeyReleased:
                controles2(event);//Soltar tecla
              break;
          }


        procesar_logica();   
          */
          while (Arachide::getInstance()->get_Window()->pollEvent(Arachide::getInstance()->event) ){

          switch(Arachide::getInstance()->event.type){

            //Si se recibe el evento de cerrar la ventana la cierro
            case sf::Event::Closed:
             Arachide::getInstance()->get_Window()->close();
              break;
                  //Verifico si se pulsa alguna tecla de movimiento
            case sf::Event::KeyPressed:    
                  Arachide::getInstance()->controles(Arachide::getInstance()->event,NULL);//pulsar tecla
            break;
            case sf::Event::KeyReleased:
                Arachide::getInstance()->controles2(Arachide::getInstance()->event);//Soltar tecla
              break;
          }


       Arachide::getInstance()-> procesar_logica();   


   
      float j1x =pos_jugador.x, j1y=pos_jugador.y;

      if(Arachide::getInstance()->getObjetos().size() > 0){ //Si hay objetos
        int cont = 0,objx, objy;
        Objeto * obj;
        bool cantidadobjetomaximo = false; //Ej ya tienes maximo de vida etc no puedes coger objeto
         Arma * armaRecoger;
        Vida * vida;
        while(cont < Arachide::getInstance()->getObjetos().size()){ //Recorrer objetos sala
          obj = Arachide::getInstance()->getObjetos()[cont];
          objx = obj->get_posicion().x , objy = obj->get_posicion().y;
          //Empezar a comparar jugador con objeto
                  
        
              if(rect.getGlobalBounds().intersects(obj->get_SpriteRect().getGlobalBounds())){
                 // std::cout << " X/Y de j1 es " << j1x <<"/"<<j1y<< " X/Y de obj es "<< objx <<"/" << objy <<std::endl;
                if(obj->getEstadoObjeto()){ //Si es para recoger
                
                  if(dynamic_cast<Moneda*>(obj)){ //Si es moneda
                    nummonedas++;
                    std::cout << " y tienes " << nummonedas << " monedas." << std::endl;
                  }
                  else if(dynamic_cast<Vida*>(obj)){ //Si es vida
                    vida = dynamic_cast<Vida*>(obj);
                    cantidadobjetomaximo = sumar_Vidas(vida->get_tipoVida());
                  }
                  else if(dynamic_cast<Arma*>(obj)){ //Si es arma
                     
                      armaRecoger = dynamic_cast<Arma*>(obj);
                      this->armaGigante = armaRecoger;
                      
                      std::cout << " Has cogido un arma de tipo " << this->armaGigante->get_tipoArma() <<endl;
                  }
                  
                  else if(!dynamic_cast<Cofre*>(obj)){ //Si es objeto
                      std::cout << " Has cogido un objeto" << std::endl;
                  }
                  if(!cantidadobjetomaximo){ //Puedes recoger este objeto si no tienes su maximo,osea de vida
                     obj->setEstadoObjeto();
                    Arachide::getInstance()->eraseObjetosRecoger(obj);
                    //Por si acaso:
                    delete obj; //posicion memoria libre
                    obj = NULL; //ponerla a null
                  
                    
                  }
                  cantidadobjetomaximo = false; //Se reinicia
                }
                
                else{ //Para interactuar
                  if(Arachide::getInstance()->event.type == sf::Event::KeyPressed){ //Interactuar con alguna tecla
                   if(Arachide::getInstance()->event.key.code==sf::Keyboard::E){ //Para evitar que avance doble
                    
                        //Arachide::getInstance()->controles(Arachide::getInstance()->event,obj);
                         // abrir_Cofre(obj);
                        Arachide::getInstance()->controles(Arachide::getInstance()->event,obj);
                            
                          
                         
                        




                   }
                  }
                }
                
              }
       
          cont++;
        }
      }
    //}
    }
}


void Jugador::abrir_Cofre(Objeto* obj){

      if(dynamic_cast<Cofre*>(obj)){ //Si es cofre
       //Downcast objeto a cofre para pasar estado a 
          Cofre *cofre = dynamic_cast<Cofre*>(obj);
          std::cout << cofre->getEstadoCofre() << std::endl;
          if(cofre->getEstadoCofre()){ //SI NO esta abierto
            std::cout << " Has abierto un cofre!" << std::endl;
            cofre->set_sprite((sf::IntRect(1 * 32, 0*32, 32, 32)));
            cofre->setEstadoCofre();
          }else{ //Si lo has abierto interactuas de nuevo para coger posible contenido
            std::cout << "El cofre está abierto " << std::endl;
            //std::cout << cofre->getContenido()->getEstadoObjeto() << std::endl;
            if(cofre->getContenido()==NULL){ //Si ha alcanzado el numero maximo vidas no se borra
              std::cout << "Ayuwoki" <<std::endl;
            }
            if(!(asignarContenido(cofre->getContenido())) ){ //Si no ha llegado al maximo de vidas
              delete cofre->getContenido();
              cofre->setContenido(); //ponerla a null
            }
          }
        }
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


//Para probar quitar vida tecla 1 quita media vida y tecla 2 quita una vida entera
void Jugador::quitar_Vida(int cant){

  if(numvidas-cant <= 0 ){
    numvidas=0;
    cout<<"Has muerto"<<endl;
  }else{
    numvidas=numvidas-cant;
  cout<<"Has perdido: "<<(float)cant/2<<" vidas"<<endl;
  }
  
}


RectangleShape Jugador::get_rec_jugador(){
  return rect;
}

//Posicionar vidas en el hud
void Jugador::set_posicionVida(Vector2f posicion){
  pos_vida=posicion;
  sprite_vida->setPosition(posicion);
}

//Vidas del hud
Sprite Jugador::get_SpriteVida(){
  return *sprite_vida;
}


void Jugador::cambiaSpriteVida(){
    //Si es de un tipo u otro
    switch(numvidas){ //No puede ser float ya que switch es con enum o enteros
      case 0:
        this->set_spriteVida(IntRect(0 * 96, 0*32, 96,32));
        break;
      case 1:
        this->set_spriteVida(IntRect(1 * 96, 0*32, 96,32));
        break;
      case 2:
        this->set_spriteVida(IntRect(0 * 96, 1*32, 96,32));
        break;
      case 3:
        this->set_spriteVida(IntRect(1 * 96, 1* 32, 96,32));
        break;
      case 4:
        this->set_spriteVida(IntRect(0 * 96, 2* 32, 96,32));
        break;
      case 5:
        this->set_spriteVida(IntRect(1 * 96, 2* 32,96,32));
        break;
      case 6:
        this->set_spriteVida(IntRect(0 * 96, 3*32, 96,32));
        break;
    }
    //set posicion no hace falta
}

void Jugador::set_spriteVida(IntRect rect){
   sprite_vida->setTextureRect(rect);
}


void Jugador::render_jugador(){
  Arachide::getInstance()->get_Window()->draw(get_rec_jugador());
    Arachide::getInstance()->get_Window()->draw(get_Sprite());
  cambiaSpriteVida();//cambiar el sprite antes de dibujar
   this->cambiaSpriteArma();
   Arachide::getInstance()->get_Window()->draw(get_SpriteVida());
  //Pintar moneda
   texto.setString(std::to_string(nummonedas));
   Arachide::getInstance()->get_Window()->draw(this->get_SpriteMoneda());
   Arachide::getInstance()->get_Window()->draw(texto);

    Arachide::getInstance()->get_Window()->draw(this->get_SpriteArma());
    
    int cont = 0;
  if(Arachide::getInstance()->getObjetos().size() > 0){ //Si hay objetos recoger suelo o interac
    while(cont < Arachide::getInstance()->getObjetos().size()){ //Recorrer objetos sala
      Arachide::getInstance()->get_Window()->draw(Arachide::getInstance()->getObjetos()[cont]->get_SpriteRect());
     Arachide::getInstance()->get_Window()->draw(Arachide::getInstance()->getObjetos()[cont]->get_Sprite());
      cont++;
    }
  }


if(atacando){
      Arachide::getInstance()->get_Window()->draw(cubo);
      Arachide::getInstance()->timeAttack= Arachide::getInstance()->relojico3.getElapsedTime().asSeconds();
      if(Arachide::getInstance()->timeAttack > 1){
        atacando=false;
        Arachide::getInstance()->relojico3.restart();
      }
}
}


int Jugador::get_Monedas(){
  return nummonedas;
}

Sprite Jugador::get_SpriteMoneda(){
  return *sprite_moneda;
}

 void Jugador::set_posicionMoneda(Vector2f posicion){
   pos_moneda=posicion;
  sprite_moneda->setPosition(posicion);
 }

 void Jugador::monedasPorVida(){
   if(get_Monedas()>2){ //Num monedas x vida
      if(!sumar_Vidas(true)){ //Si no has alcanzao en numero maximo
          
          nummonedas-=3;
          std::cout << "Has hecho el tradeo!Ahora tienes " << get_Monedas() <<" monedas " <<std::endl;
      }
    }
    else{
      std::cout << "No es posible el tradeo!Ya que tienes " << get_Monedas() <<" monedas " <<std::endl;
    }
 }



 bool Jugador::asignarContenido(Objeto * obj){

  //Para borrarlo aqui tendrias que hacer singleton , ya que no se borra el objeto ya que no apunta a nada
  bool vida = false;
  if(obj ==NULL){
    std::cout <<"Oh no! Estaba vacío" << std::endl;
  }
  else if(dynamic_cast<Moneda*>(obj)){
      nummonedas++;
      std::cout <<"Tenía 1 moneda!"<< " y tienes " << get_Monedas() << " monedas." << std::endl;
      
    }
  else if(dynamic_cast<Arma*>(obj)){
      armaGigante = dynamic_cast<Arma*>(obj);
      std::cout <<"Tenía 1 arma de tipo " << armaGigante->get_tipoArma() << std::endl;
      
  }
  else if(dynamic_cast<Vida*>(obj)){
      Vida * vidar = dynamic_cast<Vida*>(obj);
      if(sumar_Vidas(vidar)){ //Si has alcanzado la vida maxima
        vida = true;
       
      }
  }
  return vida;
}
void Jugador::set_posicionArma( Vector2f posicion){
  pos_arma=posicion;
  sprite_arma->setPosition(posicion);
}


void Jugador::cambiaSpriteArma(){
    //Si es de un tipo u otro
    if(armaGigante->get_tipoArma()==0){
      this->set_spriteArma(IntRect(32, 128, 24,24));
     
    }
    else if(armaGigante->get_tipoArma()==1){
      this->set_spriteArma(IntRect(56, 128, 24,24));
      
    }
    else if(armaGigante->get_tipoArma()==2){ //Solo llegara aqui cuando pierda arma etc
      this->set_spriteArma(IntRect(80, 128, 24, 24));
     
    }
    //set posicion no hace falta
}

Sprite Jugador::get_SpriteArma(){
  return *sprite_arma;
}


void Jugador::set_spriteArma(IntRect rect){
   sprite_arma->setTextureRect(rect);
}