#include "Layer.h"

Layer_Class::Layer_Class(){}
Layer_Class::Layer_Class(std::string tilemap_file,std::string image_file)
{
	FILE* tilemap; 
	fopen_s(&tilemap, tilemap_file.c_str(), "r");

    for(int i=0;i<COLLUM;i++)
    {
        for(int f=0;f<ROW;f++)
        {
			fscanf_s(tilemap, "%d:%d  ", &Tilemap[i][f].row, &Tilemap[i][f].collum);
        }
        fscanf_s(tilemap,"\n");
    }
    fclose(tilemap);

    Load_Textures(image_file);
}

void Layer_Class::Load_Textures(std::string image_file)
{
    Tiles = Graphics::Load_Image(image_file.c_str());
    Water = new Sprite_Class("Images/Water.png",0,3,0,0,16,320);
    Flower = new Sprite_Class("Images/Flower.png",0,3,0,0,16,32,320);
}

void Layer_Class::Animate(int i_start,int f_start,int i_end,int f_end)
{
    Water->Animate("Reverse");
    Flower->Animate();
    for(short i=i_start;i<i_end;i++)
    {
        for(short f=f_start;f<f_end;f++)
        {
            if(Tilemap[i][f].collum == 4){Water->Move(f*16,i*16);Water->Draw();}
            if(Tilemap[i][f].collum == 2){Flower->Move(f*16,i*16);Flower->Draw();}
        }
    }
}
