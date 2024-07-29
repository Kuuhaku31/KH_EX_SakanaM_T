
#include "GraphInterface.hpp"

// 获取输入
short GraphInterface::GetInput()
{
    mouseDX = 0;
    mouseDY = 0;
    mouse_V = false;

    while (peekmessage(&msg))
    {
        switch (msg.message)
        {
        case 0x100:
            switch (msg.vkcode)
            {
            case 0x57:
                key_W = true;
                break;
            case 0x53:
                key_S = true;
                break;
            case 0x41:
                key_A = true;
                break;
            case 0x44:
                key_D = true;
                break;

            case 0x49:
                key_I = true;
                break;
            case 0x4B:
                key_K = true;
                break;
            case 0x4A:
                key_J = true;
                break;
            case 0x4C:
                key_L = true;
                break;

            case 0x51:
                key_Q = true;
                break;
            case 0x45:
                key_E = true;
                break;
            case 0x52:
                key_R = true;
                break;
            case 0x46:
                key_F = true;
                break;

            case 0x26:
                arr_U = true;
                break;
            case 0x28:
                arr_D = true;
                break;
            case 0x25:
                arr_L = true;
                break;
            case 0x27:
                arr_R = true;
                break;

            case 0x20:
                space = true;
                break;
            case 0x10:
                shift = true;
                break;
            case 0x1B:
                esc__ = true;
                break;
            case 0x0D:
                enter = true;
                break;
            }
            break;

        case 0x101:
            switch (msg.vkcode)
            {
            case 0x57:
                key_W = false;
                break;
            case 0x53:
                key_S = false;
                break;
            case 0x41:
                key_A = false;
                break;
            case 0x44:
                key_D = false;
                break;

            case 0x49:
                key_I = false;
                break;
            case 0x4B:
                key_K = false;
                break;
            case 0x4A:
                key_J = false;
                break;
            case 0x4C:
                key_L = false;
                break;

            case 0x51:
                key_Q = false;
                break;
            case 0x45:
                key_E = false;
                break;
            case 0x52:
                key_R = false;
                break;
            case 0x46:
                key_F = false;
                break;

            case 0x26:
                arr_U = false;
                break;
            case 0x28:
                arr_D = false;
                break;
            case 0x25:
                arr_L = false;
                break;
            case 0x27:
                arr_R = false;
                break;

            case 0x20:
                space = false;
                break;
            case 0x10:
                shift = false;
                break;
            case 0x1B:
                esc__ = false;
                break;
            case 0x0D:
                enter = false;
                break;
            }
            break;

        case 0x200:
            mouseDX = msg.x - mouse_X;
            mouseDY = msg.y - mouse_Y;
            mouse_X = msg.x;
            mouse_Y = msg.y;
            mouse_V = true;
            break;
        case 0x201:
            mouse_L = true;
            break;
        case 0x202:
            mouse_L = false;
            break;
        case 0x204:
            mouse_R = true;
            break;
        case 0x205:
            mouse_R = false;
            break;
        case 0x207:
            mouse_M = true;
            break;
        case 0x208:
            mouse_M = false;
            break;
        case 0x20a:
            mouse_W = msg.wheel;
            break;
        default:
            break;
        }
    }
    return 0;
}

int GraphInterface::Key_W() { return key_W; }
int GraphInterface::Key_S() { return key_S; }
int GraphInterface::Key_A() { return key_A; }
int GraphInterface::Key_D() { return key_D; }

int GraphInterface::Key_I() { return key_I; }
int GraphInterface::Key_K() { return key_K; }
int GraphInterface::Key_J() { return key_J; }
int GraphInterface::Key_L() { return key_L; }

int GraphInterface::Key_Q() { return key_Q; }
int GraphInterface::Key_E() { return key_E; }
int GraphInterface::Key_R() { return key_R; }
int GraphInterface::Key_F() { return key_F; }

int GraphInterface::Arr_U() { return arr_U; }
int GraphInterface::Arr_D() { return arr_D; }
int GraphInterface::Arr_L() { return arr_L; }
int GraphInterface::Arr_R() { return arr_R; }

int GraphInterface::Space() { return space; }
int GraphInterface::Shift() { return shift; }
int GraphInterface::Esc__() { return esc__; }
int GraphInterface::Enter() { return enter; }

int GraphInterface::Mouse_X() { return mouse_X; }
int GraphInterface::Mouse_Y() { return mouse_Y; }
int GraphInterface::MouseDX() { return mouseDX; }
int GraphInterface::MouseDY() { return mouseDY; }
int GraphInterface::Mouse_V() { return mouse_V; }
int GraphInterface::Mouse_L() { return mouse_L; }
int GraphInterface::Mouse_R() { return mouse_R; }
int GraphInterface::Mouse_M() { return mouse_M; }
int GraphInterface::Mouse_W() { return mouse_W; }
