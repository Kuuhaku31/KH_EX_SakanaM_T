
#include "Library.hpp"

Zone *new_ZoneMade(std::string *paths, int *bit, int count)
{
    IMAGE *img = new IMAGE;
    loadimage(img, paths[0].c_str());

    int w = img->getwidth(), h = img->getheight();

    Zone *z = new Zone(w, h);
    int *zongbuffer = z->Shape_buffer();
    int l = z->Shape_long();

    for (int i = 0; i < count; i++)
    {
        loadimage(img, paths[i].c_str(), 0, 0, true);
        int *imgbuffer = (int *)GetImageBuffer(img);

        for (int j = 0; j < l; j++)
        {
            if (imgbuffer[j] & 0x00ffffff)
            {
                zongbuffer[j] |= (0x1 << bit[i]);
            }
        }
    }

    delete img;

    return z;
}

inline bool loadshape(Shape *shape, std::string path)
{
    if (path.empty())
    {
        return false;
    }
    else
    {
        IMAGE img;
        loadimage(&img, path.c_str(), 0, 0, true);
        shape->Shape_reset((int *)GetImageBuffer(&img), img.getwidth(), img.getheight());
        return true;
    }
}

Library::Library()
{
}

Library::~Library()
{
}

void Library::InitMat()
{
    lib_mat_path[shape_area_main] = "/area_main.png";
    lib_mat_path[shape_area_wall] = "/area_wall.png";
    lib_mat_path[shape_img_world_ground] = "/skin_main.png";
    lib_mat_path[shape_img_wall_01] = "/skin_wall_01.png";
    lib_mat_path[shape_img_wall_02] = "/skin_wall_02.png";
    lib_mat_path[shape_img_skin_sakana] = "/skin_sakana.png";
    lib_mat_path[shape_img_skin_ikacyann] = "/skin_ikacyann.png";
    lib_mat_path[shape_hitbox16] = "/hitbox16.png";

    for (int i = 0; i < MATMAX; i++)
    {
        if (loadshape(&lib_mat[i], MATPATH + lib_mat_path[i]))
        {
            continue;
        }
        else
        {
            break;
        }
    }
    Say("Library: Load shape over.");
}

Shape *Library::LibMat(LibraryMatType t)
{
    return &lib_mat[t];
}
