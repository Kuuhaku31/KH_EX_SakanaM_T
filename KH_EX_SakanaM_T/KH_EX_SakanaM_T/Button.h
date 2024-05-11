
#pragma once

#include "Position.h"
#include "Renderer.h"

class Button : public Position
{
public:
    Button() { init(); }
    Button(int x, int y) : Position(x, y) { init(); }
    ~Button() {}

    Renderer* Get_renderer() { return &main_renderer; }

private:
    Renderer main_renderer;

    void
    init()
    {
        main_renderer.Set_position(this);
     
        IMAGE img = init_skin();
        main_renderer.Reset_skin(&img);

        main_renderer.Align();
    }

    IMAGE
    init_skin()
    {
        int w = 40, h = 30;
        int l = w * h;
        IMAGE img(w, h);
        SetWorkingImage(&img);
        DWORD* img_buffer = GetImageBuffer(&img);

        for(int i = 0; i < l; i++)
        {
            img_buffer[i] = 0x88000088;
        }

        SetWorkingImage();

        return img;
    }

};
