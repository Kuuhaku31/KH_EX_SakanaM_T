
#include "base.hpp"
#include <filesystem>
#include <graphics.h>
#include <vector>


// mat路径
#define MATPATH "D:/Project/VS Code/KH_EX_SakanaM_T/mat/"
#define MATMAX 1000


// 用于在控制台打印消息
void Say(std::string str, int txtCode = WIN_COLOR_WHITE, int bakcgroudCode = KHCOLOR_BLACK);

bool conversion_IMAGE_Area(IMAGE* img, Shape* area);
bool conversion_IMAGE_Area(Shape* area, IMAGE* img);

enum LibraryMatType
{
    shape_area_main,
    shape_area_wall,

    shape_img_world_ground,
    shape_img_wall_01,
    shape_img_wall_02,

    shape_img_skin_sakana,
    shape_img_skin_ikacyan,
    shape_img_skin_bullet,

    shape_hitbox16,
    shape_hitbox_sakana,
    shape_hitbox_ikayan
};

// 动画资源枚举
enum LibraryAnimationType
{
    ani_sakana_swim,
    ani_sakana_die,
    ani_ikacyan_swim,
    ani_ikacyan_die,
    ani_bullet_fly,
    ani_bullet_explode
};

class Library
{
    friend class GameFactory;

public:
    Library();
    ~Library();


    // 初始化所有静态资源
    void InitMat();

    // 获取资源
    Shape*         LibMat(LibraryMatType);
    AnimationList* LibAnimation(LibraryAnimationType);

private:
    std::string   lib_mat_path[MATMAX];
    Shape         lib_mat[MATMAX];
    AnimationList lib_animation[MATMAX];

    // 加载动画资源
    // 传入动画资源列表，资源路径文件夹
    void loadAnimation(AnimationList*, std::string);
};
