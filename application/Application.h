// Not_afraid
// 2024/11/21

#ifndef LEARNOPENGL_APPLICATION_H
#define LEARNOPENGL_APPLICATION_H

#include <iostream>
#include <functional>

#define app Application::getInstance()

class GLFWwindow;

using ResizeCallback = std::function<void(int, int)>;
using KeyBoardCallback = std::function<void(int key, int action, int mods)>;
using MouseCallback = std::function<void(int, int, int)>;
using CursorCallback = std::function<void(double, double)>;

class Application {
public:
    ~Application();

    static Application* getInstance();

    bool init(const int& width=800, const int& height=600);

    bool update();

    void destroy();

    uint32_t getWidth() const {
        std::cout << "hello" << std::endl;
        return mWidth;
    }

    uint32_t getHeight() const {
        return mHeight;
    }

    void getCursorPosition(double* x, double* y);

    void setResizeCallback(ResizeCallback callback) {
        mResizeCallback = callback;
    }

    void setKeyBoardCallback(KeyBoardCallback callback) {
        mKeyBoardCallback = callback;
    }

    void setMouseCallback(MouseCallback callback) {
        mMouseCallback = callback;
    }

    void setCursorCallback(CursorCallback callback) {
        mCursorCallback = callback;
    }

private:
    static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseCallback(GLFWwindow* window, int botton, int action, int mods);
    static void cursorCallback(GLFWwindow* window, double xpos, double ypos);

private:
    static Application* mInstance;

    uint32_t mWidth{0};
    uint32_t mHeight{0};
    GLFWwindow* mWindow{nullptr};

    ResizeCallback mResizeCallback{nullptr};
    KeyBoardCallback mKeyBoardCallback{nullptr};
    MouseCallback  mMouseCallback{nullptr};
    CursorCallback mCursorCallback{nullptr};

    Application();
};


#endif //LEARNOPENGL_APPLICATION_H
