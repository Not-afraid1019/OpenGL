// Not_afraid
// 2024/11/25

#ifndef LEARNOPENGL_CAMERACONTROL_H
#define LEARNOPENGL_CAMERACONTROL_H

#include "../../glframework/core.h"
#include "camera.h"
#include <map>

class CameraControl {
public:
    CameraControl();
    ~CameraControl();

    virtual void update();
    virtual void OnMouse(int button, int action, int xpos, int ypos);
    virtual void OnCursor(double xpos, double ypos);
    virtual void OnKey(int key, int action, int mods);

    void setCamera(Camera* camera) { mCamera = camera; }
    void setSensitivity(float s) { mSensitivity = s; }

private:
    bool mLeftMouseDown = false;
    bool mRightMouseDown = false;
    bool mMiddleMouseDown = false;
    float mCurrentX = 0.0f, mCurrentY = 0.0f;
    std::map<int, bool> mKeyMap;
    float mSensitivity = 0.1f;
    Camera* mCamera = nullptr;
};


#endif //LEARNOPENGL_CAMERACONTROL_H
