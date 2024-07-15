
#pragma once

#include "Library.hpp"
#include "Camera.hpp"

#include "GraphInterface.hpp"

#define KEY_W graphInterface->Key_W()
#define KEY_S graphInterface->Key_S()
#define KEY_A graphInterface->Key_A()
#define KEY_D graphInterface->Key_D()

#define KEY_I graphInterface->Key_I()
#define KEY_K graphInterface->Key_K()
#define KEY_J graphInterface->Key_J()
#define KEY_L graphInterface->Key_L()

#define KEY_Q graphInterface->Key_Q()
#define KEY_E graphInterface->Key_E()
#define KEY_R graphInterface->Key_R()
#define KEY_F graphInterface->Key_F()

#define ARR_U graphInterface->Arr_U()
#define ARR_D graphInterface->Arr_D()
#define ARR_L graphInterface->Arr_L()
#define ARR_R graphInterface->Arr_R()

#define SPACE graphInterface->Space()
#define SHIFT graphInterface->Shift()
#define ESC__ graphInterface->Esc__()
#define ENTER graphInterface->Enter()

#define MOUSE_X graphInterface->Mouse_X()
#define MOUSE_Y graphInterface->Mouse_Y()
#define MOUSE_DX graphInterface->MouseDX()
#define MOUSE_DY graphInterface->MouseDY()
#define MOUSE_V graphInterface->Mouse_V()
#define MOUSE_L graphInterface->Mouse_L()
#define MOUSE_R graphInterface->Mouse_R()
#define MOUSE_M graphInterface->Mouse_M()
#define MOUSE_W graphInterface->Mouse_W()

// 游戏类
class Game
{
public:
	Game(MessageSystem *, GraphInterface *, Library *);
	~Game();

	// 更新,需要每次循环调用
	short Update();

private:
	// ^
	MessageSystem *messageSystem;
	GraphInterface *graphInterface;
	Library *library;

	Position main_origin;
	Area main_world;

	Camera *main_camera;
	Position *objects[10];
	Area *areas[10];

	Point sakana_move_vector;
	Point camera_move_vector;
};
