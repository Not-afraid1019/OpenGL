#include <iostream>
#include "glframework/core.h"
#include "glframework/shader.h"
#include "wrapper/checkError.h"
#include "application/Application.h"
#include "glframework/texture.h"

#include "application/camera/perspectiveCamera.h"
#include "application/camera/cameraControl.h"

using namespace std;

PerspectiveCamera* camera = nullptr;
CameraControl* cameraControl = nullptr;

void OnResize(int width, int height) {
    GL_CALL(glViewport(0, 0, width, height));
}

void OnKey(int key, int action, int mods) {
    cameraControl->OnKey(key, action, mods);
}

void OnMouse(int botton, int action, int mods) {
    double x, y;
    app->getCursorPosition(&x, &y);
    cameraControl->OnMouse(botton, action, x, y);
}

void OnCursor(double xpos, double ypos) {
    cameraControl->OnCursor(xpos, ypos);
}

GLuint prepareVAO(std::shared_ptr<Shader> shader) {
    // 1.准备positions
    float positions[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
    };

    float colors[] = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f,
    };

    float uvs[] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,
    };

    unsigned int indices[] = {
            0, 1, 2,
            2, 1, 3
    };

    // 2.VBO创建
    GLuint posVbo, colorVbo, uvVbo;
    glGenBuffers(1, &posVbo);
    glBindBuffer(GL_ARRAY_BUFFER, posVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glGenBuffers(1, &colorVbo);
    glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    glGenBuffers(1, &uvVbo);
    glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

    // 3.EBO创建
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 动态获取位置
    GLuint posLocation = glGetAttribLocation(shader->getProgram(), "aPos");
    GLuint colorLocation = glGetAttribLocation(shader->getProgram(), "aColor");

    // 4.VAO创建
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // 5.绑定vbo、ebo，加入属性描述信息
    // 加入位置属性描述信息
    glBindBuffer(GL_ARRAY_BUFFER, posVbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

    // 加入颜色属性描述信息
    glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);

    // 加入ebo到当前的vao当中
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBindVertexArray(0);

    return vao;
}

shared_ptr<Shader> prepareShader() {
    shared_ptr<Shader> shader = std::make_shared<Shader>("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
    return shader;
}

glm::mat4 doRotateTransform() {
    glm::mat4 transform(1.0);
    transform = glm::rotate(glm::mat4(1.0f), 45.0f, glm::vec3(0.0, 0.0, 1.0));
    return transform;
}

glm::mat4 prepareCamera() {
    camera = new PerspectiveCamera(60.0f,
                                   (float)app->getWidth() / (float)app->getHeight(),
                                   0.1f,
                                   100.0f);

    cameraControl = new CameraControl();
    cameraControl->setCamera(camera);

    // lookAt:生成一个viewMatrix
    // eye：当前摄像机所在的位置
    // center：当前摄像机看向的那个点
    // up：穹顶向量
    glm::mat4 camera = glm::lookAt(glm::vec3(3.0f, 0.0f, 1.0f),glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    return camera;
}

glm::mat4 prepareOrtho() {
    auto orthoMatrix = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, 2.0f, -2.0f);
    return orthoMatrix;
}

glm::mat4 preparePerspective() {
    // fovy:y轴方向的视张角
    // aspect:近平面的横纵百分比
    // near:近平面距离
    // far:远平面距离
    auto perspectiveMatrix = glm::perspective(glm::radians(60.0f), (float)app->getWidth() / (float)app->getHeight(), 0.1f, 100.0f);
    return perspectiveMatrix;
}

glm::mat4 doTranslationTransform() {
    glm::mat4 transform(1.0);
    transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.5, 0.0, 0.0));
    return transform;
}

void render(shared_ptr<Shader> shader, GLuint vao, glm::mat4& transform, glm::mat4& viewMatrix, glm::mat4& projMatrix) {
    // 执行opengl画布清理操作
    glClear(GL_COLOR_BUFFER_BIT);

    // 绑定当前的program
    shader->start();

    shader->setFloat("time", glfwGetTime());
//    shader->setFloat("time", 0.8);

    shader->setInt("sampler", 0);
    shader->setMatrix4x4("transform", transform);
    shader->setMatrix4x4("viewMatrix", viewMatrix);
    shader->setMatrix4x4("projMatrix", projMatrix);
//    shader->setInt("landSampler", 1);
//    shader->setInt("noiseSampler", 2);

    // 绑定当前的vao
    GL_CALL(glBindVertexArray(vao));

    // 发出绘制指令
    GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0));
    glBindVertexArray(0);
    shader->stop();
}

int main() {

    if (!app->init(800, 600)) {
        return -1;
    }

    app->setResizeCallback(OnResize);
    app->setKeyBoardCallback(OnKey);
    app->setMouseCallback(OnMouse);
    app->setCursorCallback(OnCursor);

    // 设置opengl视口以及清理颜色
    GL_CALL(glViewport(0, 0, 800, 600));
    GL_CALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));

    shared_ptr<Shader> shader = prepareShader();
    GLuint vao = prepareVAO(shader);
    Texture* grassTexture = new Texture("assets/textures/goku.jpg", 0);
    glm::mat4 transform = doRotateTransform();
    glm::mat4 viewMatrix = prepareCamera();
    glm::mat4 projMatrix = preparePerspective();

    while (app->update()) {
        cameraControl->update();
        render(shader, vao, transform, viewMatrix, projMatrix);

    }

    // 退出程序前做相关清理
    app->destroy();
    delete grassTexture;

    return 0;
}