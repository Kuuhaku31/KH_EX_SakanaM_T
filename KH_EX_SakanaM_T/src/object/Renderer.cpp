
#include "Renderer.hpp"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Reset_skin(IMAGE *img)
{
    Shape_reset((unsigned int *)GetImageBuffer(img), img->getwidth(), img->getheight());
}