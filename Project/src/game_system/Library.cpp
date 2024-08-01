
#include "game_systems.hpp"

bool
madeZone(Zone* z, std::string* paths, ZoneAreaType* bit, int count)
{
    if(z == nullptr || paths == nullptr || bit == nullptr || count <= 0)
    {
        return false;
    }
    else
    {
        // 读取图片，设置Zone大小
        IMAGE img;
        loadimage(&img, paths[0].c_str());

        int w = img.getwidth();
        int h = img.getheight();

        z->Shape_reset(w, h);
        unsigned int* zongbuffer = z->Shape_buffer();
        int           l          = z->Shape_long();

        for(int i = 0; i < count; i++)
        {
            loadimage(&img, paths[i].c_str());
            int* imgbuffer = (int*)GetImageBuffer(&img);

            for(int j = 0; j < l; j++)
            {
                if(imgbuffer[j] & 0x00ffffff)
                {
                    zongbuffer[j] |= (0x1 << bit[i]);
                }
            }
        }

        return true;
    }
}

bool
loadshape(Shape* shape, std::string path)
{
    if(path.empty() || shape == nullptr)
    {
        return false;
    }
    else
    {
        IMAGE img;
        loadimage(&img, path.c_str(), 0, 0, true);
        shape->Shape_reset((int*)GetImageBuffer(&img), img.getwidth(), img.getheight());
        return true;
    }
}

Library::Library()
{
    Say("Start to load static resource.");
    InitMat();
    Say("Static resource loaded.");
}

Library::~Library()
{
}

void
Library::LibZone(Zone* z)
{
    // 初始化zone
    std::string  paths[20] = {MATPATH "/area_main.png", MATPATH "/area_wall.png", MATPATH "/area_main.png"};
    ZoneAreaType bit[20]   = {zone_area_main, zone_area_wall, zone_area_relative};

    madeZone(z, paths, bit, 3);
}

void
Library::InitMat()
{
    lib_mat_path[shape_area_main]        = "/area_main.png";
    lib_mat_path[shape_area_wall]        = "/area_wall.png";
    lib_mat_path[shape_img_world_ground] = "/skin_main.png";
    lib_mat_path[shape_img_wall_01]      = "/skin_wall_01.png";
    lib_mat_path[shape_img_wall_02]      = "/skin_wall_02.png";
    lib_mat_path[shape_img_skin_sakana]  = "/skin_sakana.png";
    lib_mat_path[shape_img_skin_ikacyan] = "/skin_ikacyan.png";
    lib_mat_path[shape_hitbox16]         = "/hitbox/hitbox16.png";
    lib_mat_path[shape_hitbox_sakana]    = "/hitbox/hitbox_sakana.png";
    lib_mat_path[shape_hitbox_ikayan]    = "/hitbox/hitbox_ikacyan.png";

    for(int i = 0; i < MATMAX; i++)
    {
        if(lib_mat_path[i].empty())
        {
            break;
        }
        else
        {
            loadshape(&lib_mat[i], MATPATH + lib_mat_path[i]);
            Say("Load " + lib_mat_path[i] + " success.");
            continue;
        }
    }
}

Shape*
Library::LibMat(LibraryMatType t)
{
    return &lib_mat[t];
}
