// Not_afraid
// 2024/11/25

#include "cameraControl.h"
#include <iostream>

CameraControl::CameraControl() {

}

CameraControl::~CameraControl() {

}

void CameraControl::OnMouse(int button, int action, int xpos, int ypos) {
    bool pressed = action == GLFW_PRESS;

    if (pressed) {
        mCurrentX = xpos;
        mCurrentY = ypos;
    }

    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            mLeftMouseDown = pressed;
            break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            mRightMouseDown = pressed;
            break;
        case GLFW_MOUSE_BUTTON_MIDDLE:
            mMiddleMouseDown = pressed;
            break;
    }
}

void CameraControl::OnCursor(double xpos, double ypos) {
}

void CameraControl::OnKey(int key, int action, int mods) {
    if (action == GLFW_REPEAT) {
        return;
    }

    bool pressed = action == GLFW_PRESS;

    mKeyMap[key] = pressed;
}

void CameraControl::update() {
    std::cout << "update" << std::endl;
}