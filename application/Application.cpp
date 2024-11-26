// Not_afraid
// 2024/11/21

#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../wrapper/checkError.h"

Application* Application::mInstance = nullptr;
Application* Application::getInstance() {
    if (mInstance == nullptr) {
        mInstance = new Application();
    }

    return mInstance;
}

Application::Application() {

}

Application::~Application() {

}

bool Application::init(const int& width, const int& height) {
    mWidth = width;
    mHeight = height;
    // ��ʼ��GLFW��������
    glfwInit();
    // ����OpenGL���汾�ţ��ΰ汾��
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    // ����OpenGL���ú���ģʽ����������Ⱦģʽ��
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // �����������
    mWindow = glfwCreateWindow(mWidth, mHeight, "OpenGLStudy", nullptr, nullptr);
    if (mWindow == nullptr) {
        return false;
    }
    // ���õ�ǰ�������ΪOpenGL�Ļ�����̨
    glfwMakeContextCurrent(mWindow);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glfwSetFramebufferSizeCallback(mWindow, frameBufferSizeCallback);

    // this���ǵ�ǰȫ��Ψһ��Application����
    glfwSetWindowUserPointer(mWindow, this);

    // ������Ӧ
    glfwSetKeyCallback(mWindow, keyCallback);

    // ������¼�
    glfwSetMouseButtonCallback(mWindow, mouseCallback);

    // ����ƶ��¼�
    glfwSetCursorPosCallback(mWindow, cursorCallback);

    return true;
}

bool Application::update() {
    if (glfwWindowShouldClose(mWindow)) {
        return false;
    }
    // ���ղ��ַ�������Ϣ
    // �����Ϣ�����Ƿ�����Ҫ�������ꡢ���̵���Ϣ
    // ����еĻ��ͽ���Ϣ����������ն���
    GL_CALL(glfwPollEvents());

    // �л�˫����
    GL_CALL(glfwSwapBuffers(mWindow));

    return true;
}

void Application::destroy() {
    // �˳�����ǰ���������
    glfwTerminate();
}

void Application::frameBufferSizeCallback(GLFWwindow *window, int width, int height) {
    auto* self = (Application*)glfwGetWindowUserPointer(window);
    if (self->mResizeCallback != nullptr) {
        self->mResizeCallback(width, height);
    }
//    if (app->mResizeCallback != nullptr) {
//        app->mResizeCallback(width, height);
//    }
}

void Application::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    auto* self = (Application*)glfwGetWindowUserPointer(window);
    if (self->mKeyBoardCallback != nullptr) {
        self->mKeyBoardCallback(key, action, mods);
    }
}

void Application::mouseCallback(GLFWwindow *window, int botton, int action, int mods) {
    auto* self = (Application*)glfwGetWindowUserPointer(window);
    if (self->mMouseCallback != nullptr) {
        self->mMouseCallback(botton, action, mods);
    }
}

void Application::cursorCallback(GLFWwindow *window, double xpos, double ypos) {
    auto* self = (Application*)glfwGetWindowUserPointer(window);
    if (self->mCursorCallback != nullptr) {
        self->mCursorCallback(xpos, ypos);
    }
}

void Application::getCursorPosition(double* x, double* y) {
    glfwGetCursorPos(mWindow, x, y);
}