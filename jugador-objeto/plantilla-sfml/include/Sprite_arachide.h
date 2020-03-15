#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Sprite_arachide{
    public:
        Sprite_arachide();
        Texture * textura_jugador;
        Sprite  * sprite_jugador;
        void set_sprite(int rect,int cant_x, int cant_y, Vector2i  fr_a);
        int cant_x;
        int cant_y;
        int spr_Actual;
        Vector2f frame_size;
        Vector2i frame_n; //frame actual
        void seleccionar_frame();//modifica el frame por otro
        void set_frame_x(int frame);//carga el frame por si fue cambiado
        void set_frame_y(int frame);
        void animar_frame();
        void set_texture(String cadena);
       Vector2f get_frame_size();
    private:
};