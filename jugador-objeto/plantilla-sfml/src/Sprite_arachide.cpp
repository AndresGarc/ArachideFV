#include "../include/Sprite_arachide.h"

using namespace std;
Sprite_arachide::Sprite_arachide(){

}


void Sprite_arachide::set_sprite(int spr_clase, int cant_x1, int cant_y1, Vector2i fr_a){
    cant_x=cant_x1;
    cant_y=cant_y1;
    spr_Actual=spr_clase;
    textura_jugador=new Texture();
    String path ="sprites/"+ to_string(spr_clase)+".png";
    textura_jugador->loadFromFile(path);
    sprite_jugador=new Sprite(*textura_jugador);

    frame_size=Vector2f(textura_jugador->getSize().x / cant_x1, textura_jugador->getSize().y/cant_y1);
    frame_n=fr_a;

    seleccionar_frame();
}


Vector2f Sprite_arachide::get_frame_size(){
    return frame_size;
}

void Sprite_arachide::seleccionar_frame(){

    //IntRect rectangulo(frame_n.x * frame_size.x, frame_n.y * frame_size.y,frame_size.x,frame_size.y);
    if(frame_n.y==2){
         IntRect rectangulo(0* textura_jugador->getSize().x/2, frame_n.y * frame_size.y,textura_jugador->getSize().x/2,frame_size.y);
         sprite_jugador->setTextureRect(rectangulo);

    }else{
       
        //cout<<"Hola"<<endl;
        IntRect rectangulo(frame_n.x * frame_size.x, frame_n.y * frame_size.y,frame_size.x,frame_size.y);
         
        sprite_jugador->setTextureRect(rectangulo);
    }
    
}

void Sprite_arachide::set_frame_x(int frame){
    frame_n.x=frame;

    seleccionar_frame();
    
}
void Sprite_arachide::set_frame_y(int frame){
    frame_n.y=frame;
    
    seleccionar_frame();
}

void Sprite_arachide::animar_frame(){

if(frame_n.y==2){ //si ataca con el latigo
     if(frame_n.x != 0){
        frame_n.x +=1;
        
    }else{
        frame_n.x=0;//reset
    }
}else{
    if(frame_n.x != cant_x-1){
        frame_n.x +=1;
        
    }else{
        frame_n.x=0;//reset
    }
}
    seleccionar_frame();
    
}

void Sprite_arachide::set_texture(String cadena){
   textura_jugador->loadFromFile(cadena);
}
