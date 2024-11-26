// Not_afraid
// 2024/11/25

#include "orthographicCamera.h"

OrthographicCamera::OrthographicCamera(float l, float r, float t, float b, float n, float f)
    : mLeft(l)
    , mRight(r)
    , mTop(t)
    , mBottom(b)
    , mNear(n)
    , mFar(f) {

}

OrthographicCamera::~OrthographicCamera() {

}

glm::mat4 OrthographicCamera::getProjectionMatrix() {
    return glm::ortho(mLeft, mRight, mBottom, mTop, mNear, mFar);
}