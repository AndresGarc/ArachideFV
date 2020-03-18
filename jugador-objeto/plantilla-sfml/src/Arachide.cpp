#include "../include/Arachide.h"
#include "../include/config.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h>

using namespace std;
using namespace sf;



//SINGLETON
Arachide* Arachide::pinstance=0;

Arachide* Arachide::getInstance(){
	if(pinstance==0){
		pinstance = new Arachide;
	}
	return pinstance;
}

Arachide::Arachide(){
  kVel=5;
//iniciar();
}

void Arachide::iniciar(){
  inicializacion();
  //jugar incluye bucle del juego, procesamiento teclas, update y render
  jugar();
   //Fase update
    //updateArachide();

    //Fase renderizado
    //renderArachide();
}
 
 void Arachide::inicializacion(){
        //Creamos una ventana
      window = new RenderWindow(sf::VideoMode(640, 480), "P0. Fundamentos de los Videojuegos. DCCIA");

      //creamos jugador
      j1=new Jugador(2,4,2,Vector2i(0,0));

      //creamos vida
      Vida * vida = new Vida(4,480,300,true);
      objetos.push_back(vida);
      Vida * vida1 = new Vida(4,240,240,true);
      objetos.push_back(vida1);
      Vida * vida2 = new Vida(4,120,240,true);
      objetos.push_back(vida2);
       Vida * vida3 = new Vida(4,50,240,true);
      objetos.push_back(vida3);
         Vida * vida4 = new Vida(3,50,350,true);//media vida
      objetos.push_back(vida4);


      //creamos Moneda
      
  Moneda * moneda = new Moneda(100,140,true);
   objetos.push_back(moneda);
  Moneda *moneda2 = new Moneda(140,140,true);
  objetos.push_back(moneda2);
  Moneda *moneda3 = new Moneda(180,140,true);
  objetos.push_back(moneda3);
  Moneda *moneda4 = new Moneda(220,140,true); 
  objetos.push_back(moneda4);

    //creaamos COfre
  Cofre * cofre = new Cofre(6,60,340,false);
  objetos.push_back(cofre);

  //Creamos Arma
  Arma *bate = new Arma(0,260,240,true),
  *latigo = new Arma(1,350,200,true),
  *puno = new Arma(2,400,200,true);
   objetos.push_back(bate);
    objetos.push_back(latigo);
     objetos.push_back(puno);


    //VAriables gravity
    groundHeight=300;
    gravitySpedd=0.5;

    //ALtura jugador
    altura_personaje=0;

  //velocidad juego
    fps=60;
    reloj1 =new Clock();
    cronometro1=new Time();     
   
 }

void Arachide::jugar(){

  //Bucle del juego
  while (window->isOpen()){
    //Bucle de obtención de eventos
  Event event;
    
    *cronometro1 = reloj1->getElapsedTime();
    if(cronometro1->asSeconds()>1/fps){

      


    //Fase update
    updateArachide();

    //Fase renderizado
    renderArachide();

  }
  }
  
}


void Arachide::updateArachide(){

  timeAnim=relojico.getElapsedTime().asSeconds();
  timeAnim2=relojico2.getElapsedTime().asSeconds();



     if(j1->caminando){
       if(timeAnim>=0.1){
        j1->animar_jugador();     
        relojico.restart();
       }           
     }

     //recoger objetos
    j1->updateSFMLEvents();

  
  //salto gravedad
  if(j1->saltando==true && j1->get_posicion().y < altura_personaje - 200){
    
      j1->saltando=false;
      j1->caminando=false;
  }
   
   
  if(j1->get_posicion().y < groundHeight && j1->saltando==false){
    j1->set_translacion(Vector2f(0,gravitySpedd));
    
  }   

  if(timeAnim2>=0.005){
    j1->update();
    relojico2.restart();

  }
  
  if(j1->atacando){
          j1->atacar();
  }

}



void Arachide::renderArachide(){
  window->clear();

    //Render jugador: sprite jugador, sprite HUD, sprite Objeto vida 
    j1->render_jugador();
    window->display();
    reloj1->restart();

}

void Arachide::controles(Event event,Objeto*obj){
switch (event.key.code) {
        case sf::Keyboard::Space:
            teclas_j1[4] =true;       
         
          break;
           case sf::Keyboard::G:
              j1->monedasPorVida();
           break;  

           case sf::Keyboard::E:
                j1->abrir_Cofre(obj);
           break;

                 

        
        //Mapeo del cursor
         case sf::Keyboard::B:
         j1->arma =bate;
         j1->set_texture_jugador("sprites/jugadorBate.png");          
         
          break;
          //quitar vida
          case sf::Keyboard:: Numpad1:
            j1->quitar_Vida(1); //quitar media vida
          break;
            case sf::Keyboard::Numpad2:
            j1->quitar_Vida(2); //quitar vida entera
          break;
           case sf::Keyboard::V:
            cout<<"Numero de vidas actuales: "<<(float)j1->numvidas/2<<endl; //quitar vida entera
          break;
            case sf::Keyboard::L:
         j1->arma=latigo;
         j1->set_texture_jugador("sprites/latigoBlanco.png");  
                 
         
          break;


           case sf::Keyboard::N:
         j1->arma=normal;
         j1->set_texture_jugador("sprites/2.png");          
         
          break;


        case sf::Keyboard::Right:
         
          teclas_j1[1]=true; 
         
         
          break;

        case sf::Keyboard::Left:

          teclas_j1[0]=true; 
        
          

          break;

        case sf::Keyboard::Up:
        teclas_j1[2]=true; 
               


          break;

        case sf::Keyboard::Down:
         teclas_j1[3]=true; 
          break;

        //Tecla ESC para salir
        case sf::Keyboard::Escape:
         // window.close();
          break;

        //Cualquier tecla desconocida se imprime por pantalla su código
        default:
          std::cout << event.key.code << std::endl;
          break;
        }
}





void Arachide::controles2(Event event){
switch (event.key.code) {

         case sf::Keyboard::Space:
            teclas_j1[4] =false;       
         
          break;
        //Mapeo del cursor
        case sf::Keyboard::Right:     
         
       
          teclas_j1[1]=false;
          break;

        case sf::Keyboard::Left:
          teclas_j1[0]=false;
          
          break;

        case sf::Keyboard::Up:       
       
          teclas_j1[2]=false; 
          altura_personaje=0;
        

          break;

        case sf::Keyboard::Down:
        
         teclas_j1[3]=false; 
       
          break;

        //Tecla ESC para salir
        case sf::Keyboard::Escape:
         // window.close();
          break;

        //Cualquier tecla desconocida se imprime por pantalla su código
        default:
          std::cout << event.key.code << std::endl;
          break;
        }
}


void Arachide::procesar_logica(){

  j1->caminando=false;//El jugador no esta caminando
  j1->saltando=false;//El jugador no esta saltando


  //Comprobar teclas

if (teclas_j1[0]){ //izquierda

  j1->caminando=true;//el jugador 1 esta caminando

  if(teclas_j1[2]){//izquierda arriba
    j1->saltando=true;
    j1->direccion=izq_arriba;
    if(altura_personaje==0){
        altura_personaje=j1->get_posicion().y;
        cout<<altura_personaje<<endl;
    }

  }else if(teclas_j1[3]){//izquierda abajo

    j1->direccion=izq_abajo;

  }else{
    j1->direccion=izquierda;
  }


}else if(teclas_j1[1]){//derecha

      j1->caminando=true;

  if(teclas_j1[2]){
    j1->saltando=true;
      j1->direccion=der_arriba;

      if(altura_personaje==0){
        altura_personaje=j1->get_posicion().y;
        cout<<altura_personaje<<endl;
    }
  }else if(teclas_j1[3]){
      j1->direccion=der_abajo;

  }else{
    j1->direccion=derecha;
  }

}else if(teclas_j1[2]){//arriba
     j1->saltando=true;
    j1->caminando=true;

  j1->direccion=arriba;

  if(altura_personaje==0){
    altura_personaje=j1->get_posicion().y;
    cout<<altura_personaje<<endl;
  }
    

}else if(teclas_j1[3] ){//abajo

  j1->caminando=true;
  j1->direccion=abajo;

  
}

if(teclas_j1[4]){
  j1->atacando=true;
}



//Update de los jugadores

//j1->update();

}



RenderWindow* Arachide::get_Window(){
  return window;
}

Event Arachide::get_event(){
  return event;
}

vector<Objeto*> Arachide::getObjetos(){
  return objetos;
}

void Arachide::eraseObjetosRecoger(Objeto * o){
  objetos.erase(std::remove(objetos.begin(), objetos.end(), o), objetos.end());
  
}