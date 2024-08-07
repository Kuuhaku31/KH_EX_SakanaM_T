
#include "base.hpp"

// mat路径
#define MATPATH "D:/Project/VS Code/KH_EX_SakanaM_T/mat/"
#define MATMAX 1000

// 制作Zone，返回是否成功
// 传入Zone指针，图片路径数组，位数组，图片数量
bool madeZone(Zone*, std::string*, int*, int);

// 根据地址导入图片，返回是否成功
bool loadshape(Shape*, std::string);

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

class Library
{
    friend class GameFactory;

public:
    Library();
    ~Library();

    // 获取Zone
    void LibZone(Zone*, int*, int);

    // 初始化所有静态资源
    void InitMat();

    // 获取资源
    Shape* LibMat(LibraryMatType);

private:
    std::string lib_mat_path[MATMAX];
    Shape       lib_mat[MATMAX];
};