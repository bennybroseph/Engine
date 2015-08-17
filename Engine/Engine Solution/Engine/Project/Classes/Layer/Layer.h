#ifndef LAYER_INCLUDED
#define LAYER_INCLUDED


#include "../Sprite/Sprite_Class.h"

class Layer_Class
{
public:
    Layer_Class(std::string,std::string);
    Layer_Class();
    ~Layer_Class();

    void Animate(int,int,int,int);
    void Load_Textures(std::string);

    Sprite_Class* Water;
    Sprite_Class* Flower;

    struct Tilemap_Struct
    {
        int row,collum;
    };

    Tilemap_Struct Tilemap[COLLUM][ROW];

    GLSurface Tiles;
};

#endif // LAYER_INCLUDED
