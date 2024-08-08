
#include "library.hpp"


// 用于在控制台打印消息
void
Say(std::string str, int txtCode, int bakcgroudCode)
{
    // 设置控制台文字颜色
    int    code           = txtCode + (bakcgroudCode << 4);
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsoleOutput, code);
    std::cout << std::endl
              << str;
    SetConsoleTextAttribute(hConsoleOutput, WIN_COLOR_WHITE);
}


static bool
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

// 实现IMAGE类和Shape类的互相转化
bool
conversion_IMAGE_Area(IMAGE* img, Shape* area)
{
    if(img == nullptr || area == nullptr)
    {
        return false;
    }
    else
    {
        int  w     = area->Shape_wide();
        int  h     = area->Shape_high();
        int  l     = area->Shape_long();
        int* areab = area->Shape_buffer();

        img->Resize(w, h);
        DWORD* imgb = GetImageBuffer(img);

        for(int i = 0; i < l; i++)
        {
            imgb[i] = areab[i];
        }

        return true;
    }
};

bool
conversion_IMAGE_Area(Shape* area, IMAGE* img)
{
    if(img == nullptr || area == nullptr)
    {
        return false;
    }
    else
    {
        int w = img->getwidth();
        int h = img->getheight();
        area->Shape_reset(w, h);
        int  l     = area->Shape_long();
        int* areab = area->Shape_buffer();

        DWORD* imgb = GetImageBuffer(img);

        for(int i = 0; i < l; i++)
        {
            areab[i] = imgb[i];
        }

        return true;
    }
};


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
Library::InitMat()
{
    lib_mat_path[shape_area_main]        = "/area_main.png";
    lib_mat_path[shape_area_wall]        = "/area_wall.png";
    lib_mat_path[shape_img_world_ground] = "/skin_main.png";
    lib_mat_path[shape_img_wall_01]      = "/skin_wall_01.png";
    lib_mat_path[shape_img_wall_02]      = "/skin_wall_02.png";
    lib_mat_path[shape_img_skin_sakana]  = "/skin_sakana.png";
    lib_mat_path[shape_img_skin_ikacyan] = "/skin_ikacyan.png";
    lib_mat_path[shape_img_skin_bullet]  = "/skin_bullet.png";
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

    loadAnimation(&lib_animation[ani_sakana_swim], "D:/Project/VS Code/KH_EX_SakanaM_T/mat/ani/ikacyan/swim");
    loadAnimation(&lib_animation[ani_sakana_die], "D:/Project/VS Code/KH_EX_SakanaM_T/mat/ani/ikacyan/die");
    loadAnimation(&lib_animation[ani_ikacyan_swim], "D:/Project/VS Code/KH_EX_SakanaM_T/mat/ani/ikacyan/swim");
    loadAnimation(&lib_animation[ani_ikacyan_die], "D:/Project/VS Code/KH_EX_SakanaM_T/mat/ani/ikacyan/die");
    loadAnimation(&lib_animation[ani_bullet_fly], "D:/Project/VS Code/KH_EX_SakanaM_T/mat/ani/bullet/fly");
    loadAnimation(&lib_animation[ani_bullet_explode], "D:/Project/VS Code/KH_EX_SakanaM_T/mat/ani/bullet/explode");
}

Shape*
Library::LibMat(LibraryMatType t)
{
    return &lib_mat[t];
}

AnimationList*
Library::LibAnimation(LibraryAnimationType t)
{
    return &lib_animation[t];
}

void
Library::loadAnimation(AnimationList* ani, std::string path)
{
    // 读取文件夹下所有png文件地址
    std::vector<std::string> files;
    for(auto& p : std::filesystem::directory_iterator(path))
    {
        if(p.path().extension() == ".png")
        {
            files.push_back(p.path().string());
        }
    }

    // 排序
    std::sort(files.begin(), files.end());

    int count = files.size();
    ani->free();
    ani->frame_count = count;
    ani->frames      = new Shape[count];

    // 读取图片
    for(int i = 0; i < count; i++)
    {
        loadshape(&ani->frames[i], files[i]);
    }
}
