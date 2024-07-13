
#include "Renderer.hpp"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::To_IMAGE(IMAGE *img)
{
    img->Resize(shape_wide, shape_high);
    DWORD *b = GetImageBuffer(img);
    for (int i = 0; i < shape_long; i++)
    {
        b[i] = shape_buffer[i];
    }
}

void Renderer::Reset_skin(IMAGE *img)
{
    Shape_reset((unsigned int *)GetImageBuffer(img), img->getwidth(), img->getheight());
}